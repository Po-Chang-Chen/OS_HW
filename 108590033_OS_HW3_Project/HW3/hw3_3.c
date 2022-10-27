#include<stdio.h>
#include<stdlib.h>
#include<time.h> 

//Write a program that implements the FIFO and LRU page-replacement algorithms presented in this chapter.
//First, generate a random pagereference string where page numbers range from 0 to 9.
//Apply the random page-reference string to each algorithm, and record the number of page faults incurred by each algorithm.
//Implement the replacement algorithms so that the number of page frames can vary from 1 to 7.
//Assume that demand paging is used.

void printfunction(int a[], int frame_number);
void optimal(int string[20],int n,int size)
{
    //Creating array for block storage
    int frames[n];
    //Initializing each block with -1
    for (int i=0;i<n;i++)
        frames[i]=-1;

    //Index to insert element
    int index=-1;

    //Counters
    int page_miss=0;
    int page_hits=0;

    //Pointer to indicate initially frames filled or not
    int full=0;

    //Traversing each symbol in fifo
    for (int i=0;i<size;i++)
    {
        int symbol=string[i];
        int flag=0;

        for(int j=0;j<n;j++)
        {
            if (symbol==frames[j])
            {
                flag=1;
                break;
            }
        }

        if (flag==1)
        {
            printf("\nSymbol: %d  Frame: ",symbol);
            for (int j=0;j<n;j++)
                printf("%d ",frames[j]);
            page_hits+=1;
        }
        else
        {
            //Frames are still empty
            if (full==0)
            {
                index=(index+1)%n;
                frames[index]=symbol;
                page_miss+=1;
                printf("\nSymbol: %d  Frame: ",symbol);
                for (int j=0;j<n;j++)
                    printf("%d ",frames[j]);

                //Frames filled or not
                if (i==n-1)
                    full=1;
            }

            //Frames are full, now we can apply optimal page replacement
            else
            {
                //First find the index to replace with
                int pos=-1;
                int index=-1;

                //Traversing each symbol and checking their optimal possibility
                for(int j=0;j<n;j++)
                {
                    //Whether symbol in frame found or not in future cached frame
                    int found=0;
                    for (int k=i+1;k<size;k++)
                    {
                        //If symbol exists in cached string
                        if (frames[j]==string[k])
                        {
                            found=1;
                            if (pos<k)
                            {
                                pos=k;
                                index=j;
                            }
                            break;
                        } 
                    }
                    //Symbol does not exist in cached frame
                    if (found==0)
                    {
                        pos=size;
                        index=j;
                    }
                }

                //Now assign symbol in lru position
                frames[index]=symbol;

                printf("\nSymbol: %d  Frame: ",symbol);
                for (int j=0;j<n;j++)
                    printf("%d ",frames[j]);
            }
        }
    }
    printf("\nOPTA page faults: %d",page_miss);
}

int main()
{
	//先寫死 
//	int page_string[12]={4,3,2,1,4,3,5,4,3,2,1,5};
	int page_string[20];
	srand(time(NULL));
//	int random;
	int i;
	for(i=0;i<20;i++)
	{
		page_string[i]=rand()%10;	
	}
	printf("page reference string is :\n");
	printfunction(page_string, 20);

	int pages_frame;
	
	printf("please enter page frameNumber : ");
	scanf("%d", &pages_frame);
	printf("\n");
	
	int frame[pages_frame];
	for(i=0;i<pages_frame;i++)
	{
		frame[i] = -1;
	}
	
	// FIFO
	int fifo_fault = 0;
	int fifo_order = 0;
	int turn = 0;  //number of page input
	while(turn<20)
	{
		for(i=0;i<pages_frame;i++)
		{
			if(page_string[turn]==frame[i])
			{
				break;
			}
			if(i==(pages_frame-1))
			{
				fifo_fault++;
				frame[fifo_order]=page_string[turn];
				fifo_order++;
			}	
		}
		printfunction(frame, pages_frame);
	
//		fifo_order++;
		turn++;
		
		if(fifo_order==pages_frame)
		{
			fifo_order=0;
		}
	}
	
	printf("\nFIFO page fault = %d\n\n", fifo_fault);
//==================================================================//
	// LRU
	// 標 LRU 代表 LRU參數
	
	int frame_LRU[pages_frame];
	for(i=0;i<pages_frame;i++)
	{
		frame_LRU[i] = -1;
	}
	
	int LRU_fault = 0;
	int turn_LRU = 0;  //number of page input
	int write_position = 0; //插入值的地方 
	
	int k;
	//   最近放進來的  會放在 index write_position 
	while(turn_LRU<20)
	{
		for(i=0;i<pages_frame;i++)
		{
			if(page_string[turn_LRU]==frame_LRU[i])
			{
				write_position--;
				for(k=i;k<write_position;k++)
				{
					frame_LRU[k]=frame_LRU[k+1];
				}
				frame_LRU[write_position]=page_string[turn_LRU];
				write_position++;
				break;
			}
			
			if(i==(pages_frame-1))
			{
				LRU_fault++;
				if(write_position!=pages_frame)
				{
					frame_LRU[write_position]=page_string[turn_LRU];
					write_position++;
				}
				else
				{
					for(k=0;k<(pages_frame-1);k++)
					{
						frame_LRU[k]=frame_LRU[k+1];
					}
					frame_LRU[pages_frame-1]=page_string[turn_LRU];
				}
			}
		}
		printfunction(frame_LRU, pages_frame);
		turn_LRU++;
	}
	 
	printf("\nLRU page fault = %d\n", LRU_fault);
        int size=sizeof(page_string)/sizeof(int);
        optimal(page_string,pages_frame,size);
	
	return 0;  
}

void printfunction(int a[], int frame_number)
{
	int t;
	for(t=0;t<frame_number;t++)
	{
		printf("%d ", a[t]);
	}
	printf("\n");
} 
