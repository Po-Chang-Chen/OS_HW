#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define North_num 7
#define South_num 7
sem_t north;
sem_t south;
pthread_mutex_t northPass = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t southPass = PTHREAD_MUTEX_INITIALIZER;

int northOnB =0;
int nWait = 0;
int southOnB = 0;
int sWait =0;
int GetRandTime(){
    return (rand()%5 + 1);
}
void *StB(void *num){
    int* index = (int*)num;
    sleep(GetRandTime());
    printf("[%d]'s Peoples from south want to pass the bridge...\n",*index);
    pthread_mutex_lock(&southPass);
    if(nWait>0 || northOnB>0){
      sWait++;
      sem_wait(&south);
      while(northOnB>0){
          sem_wait(&south);}
      sWait--;

    }
    southOnB++;
    if(nWait==0){
     sem_post(&south);}
    pthread_mutex_unlock(&southPass);
    printf("[%d]'s Peoples from south passing the bridge...\n",*index);
    sleep(GetRandTime());
    printf("[%d]'s Peoples from south leaving the bridge...\n",*index);
    pthread_mutex_lock(&southPass);
    southOnB--;
    if (southOnB == 0) {
        sem_post(&north);
        printf("The bridge has no peoples!\n");
    }
    pthread_mutex_unlock(&southPass);
    
    pthread_exit(0);
}
void *NtB(void *num){
    int* index = (int*)num;
    sleep(GetRandTime());
    printf("[%d]'s Peoples from north want to pass the bridge...\n",*index);
    pthread_mutex_lock(&northPass);
    if(sWait>0 || southOnB>0){
      nWait++;
      sem_wait(&north);
      while(southOnB>0){
          sem_wait(&north);}
      nWait--;

    }
    northOnB++;
    if(sWait==0){
     sem_post(&north);}
    pthread_mutex_unlock(&northPass);
    printf("[%d]'s Peoples from north passing the bridge...\n",*index);
    sleep(GetRandTime());
    printf("[%d]'s Peoples from north leaving the bridge...\n",*index);
    pthread_mutex_lock(&northPass);
    northOnB--;
    if (northOnB == 0) {
        sem_post(&south);
        printf("The bridge has no peoples!\n");
    }
    pthread_mutex_unlock(&northPass);
    
    pthread_exit(0);
}

int main(int argc,char* argv[]){


    srand(time(NULL));
    int index[7] = {0,1,2,3,4,5,6};
    sem_init(&north,0,1);
    sem_init(&south,0,1);
    pthread_t *northPeoples;
    pthread_t *southPeoples;
    northPeoples = (pthread_t *)malloc(North_num * sizeof(pthread_t));
    southPeoples = (pthread_t *)malloc(South_num * sizeof(pthread_t));
    for(int i=0;i<North_num;i++){
    pthread_create(&northPeoples[i],NULL,NtB,(void*)&index[i]);}
    for(int i=0;i<South_num;i++){
    pthread_create(&southPeoples[i],NULL,StB,(void*)&index[i]);}
    for(int i=0;i<North_num;i++){
    pthread_join(northPeoples[i],NULL); }
    for(int i=0;i<South_num;i++){
    pthread_join(southPeoples[i],NULL); }
    free(northPeoples);
    free(southPeoples);
    sem_destroy(&north);
    sem_destroy(&south);
    return 0;

}
