#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
int total_points=0;
int point_in_circle=0;
void *count(void *arg){
	for(int i=0;i<total_points;i++){
	        double x=(double)rand()/RAND_MAX;
		double y=(double)rand()/RAND_MAX;
	if((x*x)+(y*y)<=1){
		point_in_circle++;
       }
       }
       return NULL;
}
int main(){
pthread_t thread;
srand(time(NULL));
while(total_points<=0)
{
    scanf("%d",&total_points);
}

pthread_create(&thread,NULL,&count,NULL);
pthread_join(thread,NULL); 
double point=4.0*point_in_circle;   
double pi=point/total_points;
printf("%f",pi);


}
