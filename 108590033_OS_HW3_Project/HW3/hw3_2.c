#include <stdio.h>
#include <stdlib.h>


#define PAGE_SIZE 4096




int main(int argc, char *argv[]){
    unsigned int virtualAddress,page_Number,offset;
    if(argc<2){
        printf("Enter the Virtualaddress: ");
        return -1;
    }
    virtualAddress = atoi(argv[1]);
    page_Number = virtualAddress / PAGE_SIZE;
    offset = virtualAddress % PAGE_SIZE;
    printf("The address %u contains:\nPage number = %u\noffset =%u\n", virtualAddress, page_Number, offset);
    
    return 0;
}
