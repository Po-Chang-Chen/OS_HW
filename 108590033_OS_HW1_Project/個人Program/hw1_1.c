#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char *argv[]){
FILE *in,*out;
int co;

in = fopen(argv[1],"r");
out =fopen(argv[2],"w");
co=getc(in);
while(co !=EOF){
    putc(co,out);
    co=getc(in);
}
fclose(in);
fclose(out);
return 0;



}
