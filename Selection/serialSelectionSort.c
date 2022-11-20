#include <stdio.h>
#include <time.h>
#include <wait.h>
#include<sys/wait.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/time.h>
clock_t ticks;
struct timeval stop, start;
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
	Arr[iter] = rand() % 100;    
	//scanf("%d", &Arr[iter]);
	printf("%d", Arr[iter]);
	}

    
	double bstart = clock();
	gettimeofday(&start, NULL);
	selectionSort(Arr, number);
	gettimeofday(&stop, NULL);
	double bstop = clock();    
	display(Arr, number);
	FILE* fp;
	fp = fopen("Timings.txt", "a");
    	fprintf(fp, "Serial Burst Time: %lf\n",difftime(bstop,bstart));
	fprintf(fp, "Serial Execution Time: %lu\n\n\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);	
	fclose(fp);    
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

}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

