#include <stdio.h>
#include <time.h>
#include <wait.h>
#include<sys/wait.h>
#include <stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
//time_t start, stop;
struct timeval stop, start;
clock_t ticks;    
int linearSearch(int* A, int n, int tos);
void* selectionSort();
void swap(int* a, int* b);
void* merge(void* args);
void display(int* arr, int n);
#define MAX_THREAD 2

struct sortingArgs{
	
	int *ptr;
	int size;
	int start, end;
}FinalArgs;
int main(){
    
	time_t t;

	srand((unsigned) time(&t));
    pthread_t threads[MAX_THREAD];
    int number, iter =0;

	struct sortingArgs Args;
	
	printf("\nEnter the Size of the Array: ");	
    scanf("%d", &number);
	Args.size = number;
	Args.start = 0;
	Args.end = number/2;	
	int Arr[number];
    	Args.ptr = (int *)calloc( Args.size, Args.size * sizeof(int));
	
	for(; iter<number; iter++){
		printf("\nElement No. %d: ", iter + 1);
		
		*(Args.ptr + iter) = rand() % 100;
		printf("%d", *(Args.ptr + iter));	
	}
    	
	double bstart = clock();
	gettimeofday(&start, NULL);
	
		
       		 
		pthread_create(&threads[0], NULL, selectionSort, &Args);	
		pthread_join(threads[0], NULL);	

		
		Args.start = number/2 + 1;
		Args.end = number;

		
		pthread_create(&threads[1], NULL, selectionSort, &Args);
		pthread_join(threads[1], NULL);	
		
		pthread_create(&threads[0], NULL, merge, &Args);
		pthread_join(threads[0], NULL);
		
	gettimeofday(&stop, NULL);
	double bstop = clock(); 	

	Args.ptr = FinalArgs.ptr;
	
    	   
	display(FinalArgs.ptr, number);
	FILE* fp;
	fp = fopen("Timings.txt", "a");
    	fprintf(fp, "Multi-threading Burst Time: %lf\n",difftime(bstop,bstart));
	fprintf(fp, "Multi-threading Execution Time: %lu\n\n\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);	
	fclose(fp);        
}


void* selectionSort(void* input)
{
 	struct sortingArgs *Arg = (struct sortingArgs*) input;

	int n = Arg->end;
	int s = Arg->start;
	
    for(int startpos = s; startpos < n-1; startpos++){
        int maxpos = startpos;
        for(int i=startpos +1; i< n; ++i){
		if(Arg->ptr[i] < Arg->ptr[maxpos])              
		  	maxpos = i;
            
        }
	if(maxpos != startpos)
        	swap(&Arg->ptr[startpos], &Arg->ptr[maxpos]);
	}

	pthread_exit(0);
}


void* merge(void* args)
{
	struct sortingArgs *Arg = (struct sortingArgs*) args;
	FinalArgs.size = Arg->size;

	FinalArgs.ptr = (int *)calloc( FinalArgs.size, FinalArgs.size * sizeof(int));
	int i = 0, j = Arg->size/2 + 1, k=0;
	
	for(; i <(Arg->size/2 + 1); k++)
	{
				
		if(Arg->ptr[i] < Arg->ptr[j] || j>= Arg->size)
		{
			FinalArgs.ptr[k] = Arg->ptr[i];
			i++;
		}
		else
		{
			if(j<Arg->size)
			{
				FinalArgs.ptr[k] = Arg->ptr[j];
				j++;
			}
		}	
	} 
	while(j < Arg->size)
	{
		FinalArgs.ptr[k] = Arg->ptr[j];
		k++;
		j++;
	}
	
//pthread_exit(0);
}
void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display(int* arr, int n){
    
    printf("\nARRAY: {");
    for(int i = 0; i<n; i++)
    {
        if(i != n - 1)
        {
            printf("%d, ", *(arr + i));        
        }
        else
            printf("%d}\n\n", *(arr + i));
    }
    
}

