#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int fbn; /* this data is shared by the thread(s) */
int i;
int n;
int n1,n2;
void *runner(void *param);
int main(int argc, char *argv[])
{ n=atoi(argv[1]);
pthread_t thread; /* the thread identifier */
pthread_attr_t attr; /* set of thread attributes */
/* set the default attributes of the thread */
pthread_attr_init(&attr);
/* create the thread */
pthread_create(&thread, &attr, runner, argv[1]);
/* wait for the thread to exit */
pthread_join(thread,NULL);
}

void *runner(void *param)
{
n1=1,n2=1;
int  n = atoi(param);
if(n==0){printf("0");}
else if(n==1){printf("0,1");}
else{
printf("0,");
printf("%d,",n1);
printf("%d,",n2);
for(int k=0;k<n-2;k++){
    fbn=n1+n2;
    n1=n2;
    n2=fbn;
    printf("%d,",fbn);

 }  

}

pthread_exit(0);}
