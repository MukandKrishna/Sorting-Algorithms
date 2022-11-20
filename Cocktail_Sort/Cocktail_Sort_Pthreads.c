#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
#include<pthread.h>
struct array
{
	int *ptr;
	long int size;
	
}Array,Final_Array;
struct Time
{
	double Start,End;
}Execution;
struct timeval stop, start;
void* Cocktail_Sort_Down(void *args )
{
	int start=(Array.size/2+1);
	int end=Array.size-1;
	int i;
	while(start<end)
	{
		for(i=start;i<end;i++)
		{
			if(Array.ptr[i]>Array.ptr[i+1])
			{
				int temp=Array.ptr[i];
				Array.ptr[i]=Array.ptr[i+1];
				Array.ptr[i+1]=temp;
			}
		
		}
		for(i=end-1;i>start;i--)
		{
			if(Array.ptr[i]<Array.ptr[i-1])
			{
				int temp=Array.ptr[i];
				Array.ptr[i]=Array.ptr[i-1];
				Array.ptr[i-1]=temp;
			}
			
		}
		
		start++;
		end--;

	}
	pthread_exit(0);
}
void* Cocktail_Sort_Up(void *args)
{
	int start=0;
	int end=Array.size/2;
	int i;
	while(start<end)
	{
		for(i=start;i<end;i++)
		{
			if(Array.ptr[i]>Array.ptr[i+1])
			{
				int temp=Array.ptr[i];
				Array.ptr[i]=Array.ptr[i+1];
				Array.ptr[i+1]=temp;
			}
		
		}
		for(i=end-1;i>start;i--)
		{
			if(Array.ptr[i]<Array.ptr[i-1])
			{
				int temp=Array.ptr[i];
				Array.ptr[i]=Array.ptr[i-1];
				Array.ptr[i-1]=temp;
			}
			
		}
		start++;
		end--;
		
	}	
	

	pthread_exit(0);
}
void* merge(void *args)
{
	Final_Array.size=Array.size;
	Final_Array.ptr=(int *) calloc(Final_Array.size,sizeof(int));
	int i=0,j=Array.size/2+1,k=0;
	
	for(;i<(Array.size/2+1);k++)
	{
		if(Array.ptr[i]<Array.ptr[j] || j>=Array.size)
		{
			Final_Array.ptr[k]=Array.ptr[i];
			i++;
		}
		else
		{
			if(j<Array.size)
			{
				Final_Array.ptr[k]=Array.ptr[j];
				j++;		
			}
			
		}
	}
	while(j<Array.size)
	{
		Final_Array.ptr[k]=Array.ptr[j];
		j++;
		k++;		
		
	}

}
void* Filling(void *args)
{
	FILE *ptr;
	ptr=fopen("Project_Times.txt","a+");
	if(ptr==NULL)
	{
		printf("Unable to Open File");
		exit(1);
	}
	else
	{
		double total= (double)(Execution.End-Execution.Start)/(double)CLOCKS_PER_SEC;
		double Total=(double)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
		fprintf(ptr,"Burst Time Taken By Multithreaded_Cocktail_Sort is %lf\n",total);
		fprintf(ptr,"Time Taken By Multithreaded_Cocktail_Sort is %lf\n",Total);
	}
	fclose(ptr);
	pthread_exit(0);
	
}
int main(void)
{
	srand(time(NULL));
	printf("Enter The Size of Array: ");
	scanf("%ld",&Array.size);
	Array.ptr=(int *) calloc(Array.size,sizeof(int));
	printf("Enter The Elements Array\n");
	for(int i=0;i<Array.size;i++)	
	{
		*(Array.ptr+i)=rand()%Array.size;
	}
	pthread_t threads[2];
	Execution.Start=clock();
	gettimeofday(&start, NULL);	
	pthread_create(&threads[0],NULL,Cocktail_Sort_Up,NULL);
	pthread_create(&threads[1],NULL,Cocktail_Sort_Down,NULL);
	for(int i=0;i<2;i++)
	{
		pthread_join(threads[i],NULL);
	}
	pthread_create(&threads[0],NULL,merge,NULL);
	pthread_join(threads[0],NULL);
	gettimeofday(&stop, NULL);
	Execution.End=clock();		
	pthread_create(&threads[1],NULL,Filling,NULL);
	printf("Sorted Array: ");
	for(int i=0;i<Array.size;i++)
	{
		printf("%d ",(Final_Array.ptr[i]));
	}
	printf("\n");
	pthread_join(threads[1],NULL);
}
