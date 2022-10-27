#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
typedef struct{
  int arr_len;
} arg;
int total_points=0;
int point_in_circle=0;
double *points;
pthread_mutex_t mutex;
void *count(void *argv){
        arg* args=argv;
        int arr_len=(*args).arr_len;
	pthread_mutex_lock(&mutex);
	for(int i=0;i<arr_len;i++){
	        double x=(double)rand()/RAND_MAX;
		double y=(double)rand()/RAND_MAX;
	if((x*x)+(y*y)<=1){
		point_in_circle++;
       }
       }
       pthread_mutex_unlock(&mutex);
       return NULL;
}
int main(){
void* v_argv;
arg* argv =malloc(sizeof(arg));
int num=2;
pthread_t thread[num];
srand(time(NULL));

while(total_points<=0)
{
    scanf("%d",&total_points);
}
(*argv).arr_len=total_points;
v_argv=(void*)(argv);
pthread_mutex_init(&mutex,0);
for(int i=0;i<num;i++){
pthread_create(&thread[i],NULL,&count,v_argv);}
for(int i=0;i<num;i++){
pthread_join(thread[i],NULL); }
double point=4.0*point_in_circle;   
double pi=point/(total_points*num);
printf("%f",pi);
free(argv);
pthread_mutex_destroy(&mutex);


}
