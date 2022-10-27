#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
  pid_t pid;

  // 建立一個變數
  int x=0;
  scanf("%d",&x);
  pid = fork();
  if(pid==0){
  while(x!=1){

    if(x%2==0){
        x=x/2;}
    else{
        x=3*x+1;}
      printf("%d\n",x);
  }
}
else{
    wait();
}

  return 0;
}
