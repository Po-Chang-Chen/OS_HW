#include <pthread.h>		//Create POSIX threads.
#include <time.h>			//Wait for a random time.
#include <unistd.h>			//Thread calls sleep for specified number of seconds.
#include <semaphore.h>		//To create semaphores
#include <stdlib.h>
#include <stdio.h>			//Input Output

pthread_t *Students;		//N threads running as Students.
pthread_t TA;				//Separate Thread for TA.

int ChairsCount = 0;
int CurrentIndex = 0;

//Declaration of Semaphores and Mutex Lock.
sem_t TA_Sleep;
sem_t Student_Sem;
sem_t ChairsSem[3];
pthread_mutex_t ChairAccess;

//Declared Functions
void *TA_Activity();
void *Student_Activity(void *threadID);

int main(int argc, char* argv[])
{
	int number_of_students;		//a variable taken from the user to create student threads.	Default is 5 student threads.
	int id;
	srand(time(NULL));

	//Initializing Mutex Lock and Semaphores.
	sem_init(&TA_Sleep, 0, 0);
	sem_init(&Student_Sem, 0, 0);
	for(id = 0; id < 3; ++id)			//Chairs array of 3 semaphores.
		sem_init(&ChairsSem[id], 0, 0);

	pthread_mutex_init(&ChairAccess, NULL);

	if(argc<2)
	{
		printf("未指定學生人數。 使用默認 (5) 個學生。\n");
		number_of_students = 5;
	}
	else
	{
		printf("以指定學生人數。 使用默認 %d 個學生。\n", number_of_students);
		number_of_students = atoi(argv[1]);
	}

	//Allocate memory for Students
	Students = (pthread_t*) malloc(sizeof(pthread_t)*number_of_students);

	//Creating TA thread and N Student threads.
	pthread_create(&TA, NULL, TA_Activity, NULL);
	for(id = 0; id < number_of_students; id++)
		pthread_create(&Students[id], NULL, Student_Activity,(void*) (long)id);

	//Waiting for TA thread and N Student threads.
	pthread_join(TA, NULL);
	for(id = 0; id < number_of_students; id++)
		pthread_join(Students[id], NULL);

	//Free allocated memory
	free(Students);
	return 0;
}

void *TA_Activity()
{
	while(1)
	{
		sem_wait(&TA_Sleep);		//TA is currently sleeping.
		printf("~~~~~~~~~~~~~~~~~~~~~TA被學生叫醒.~~~~~~~~~~~~~~~~~~~~~\n");

		while(1)
		{
			// lock
			pthread_mutex_lock(&ChairAccess);
			if(ChairsCount == 0)
			{
				//if chairs are empty, break the loop.
				pthread_mutex_unlock(&ChairAccess);
				break;
			}
			//TA gets next student on chair.
			sem_post(&ChairsSem[CurrentIndex]);
			ChairsCount--;
			printf("學生離開了他/她的椅子。 剩餘 %d 椅子 \n", 3 - ChairsCount);
			CurrentIndex = (CurrentIndex + 1) % 3;
			pthread_mutex_unlock(&ChairAccess);
			// unlock

			printf("TA目前正在幫助學生。\n");
			sleep(5);
			sem_post(&Student_Sem);
			usleep(1000);
		}
	}
}

void *Student_Activity(void *threadID)
{
	int ProgrammingTime;

	while(1)
	{
		printf("學生 %ld 正在做編程作業。\n", (long)threadID);
		ProgrammingTime = rand() % 10 + 1;
		sleep(ProgrammingTime);		//Sleep for a random time period.

		printf("學生 %ld 需要TA的幫助。\n", (long)threadID);

		pthread_mutex_lock(&ChairAccess);
		int count = ChairsCount;
		pthread_mutex_unlock(&ChairAccess);

		if(count < 3)		//Student tried to sit on a chair.
		{
			if(count == 0)		//If student sits on first empty chair, wake up the TA.
				sem_post(&TA_Sleep);
			else
				printf("學生 %ld 坐在椅子上等TA說完。 \n", (long)threadID);

			// lock
			pthread_mutex_lock(&ChairAccess);
			int index = (CurrentIndex + ChairsCount) % 3;
			ChairsCount++;
			printf("學生坐在椅子上。剩下的椅子: %d\n", 3 - ChairsCount);
			pthread_mutex_unlock(&ChairAccess);
			// unlock

			sem_wait(&ChairsSem[index]);		//Student leaves his/her chair.
			printf("學生 %ld 正在尋求助教的幫助。 \n", (long)threadID);
			sem_wait(&Student_Sem);		//Student waits to go next.
			printf("學生 %ld left TA room.\n",(long)threadID);
		}
		else
			printf("學生 %ld 將在另一個時間返回。\n", (long)threadID);
			//If student didn't find any chair to sit on.
	}
}
