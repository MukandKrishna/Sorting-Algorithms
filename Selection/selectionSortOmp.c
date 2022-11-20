#include <stdio.h>
#include <time.h>
#include <wait.h>
#include<sys/wait.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/time.h>

struct timeval stop, start;
clock_t ticks;    
int linearSearch(int* A, int n, int tos);
void selectionSort(int* A, int n);
void swap(int* a, int* b);
void display(int* arr, int n);
int main(){

	time_t t;
    int number, iter =0, find;
	srand((unsigned) time(&t));	

	printf("\nEnter the Size of the Array: ");	
    scanf("%d", &number);
    int *Arr = (int *)malloc( number * sizeof(int));

    for(; iter<number; iter++){
        printf("\nElement No. %d: ", iter + 1);
	//scanf("%d", &Arr[iter]);
	Arr[iter] = rand() % 100;    
	printf("%d", Arr[iter]);
	}


    
    //time(&start);
    
	double bstart = clock();
	gettimeofday(&start, NULL);
	selectionSort(Arr, number);
    //time(&stop);
	gettimeofday(&stop, NULL);
	double bstop = clock();    
	display(Arr, number);
	FILE* fp;
	fp = fopen("Timings.txt", "a");
    	fprintf(fp, "OpenMP Burst Time: %lf\n",difftime(bstop,bstart));
	fprintf(fp, "OpenMP Execution Time: %lu\n\n\n",(stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);	
	fclose(fp);       
	//printf("\nTIME: %lf ",difftime(stop,start));
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

void selectionSort(int* A, int n)
{
    #pragma omp parallel for num_threads(2)
    for(int startpos =0; startpos < n-1; startpos++){
        int maxpos = startpos;
        for(int i=startpos +1; i< n; ++i){
            if(A[i] < A[maxpos]){
                maxpos = i;
            }
        }
	if(maxpos != startpos)
        	swap(&A[startpos], &A[maxpos]);
    }
    #pragma barrier
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

