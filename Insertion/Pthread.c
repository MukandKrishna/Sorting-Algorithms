#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define SIZE 100
int n1[SIZE];
int n2[SIZE];
struct timeval Stop2,start2;
typedef struct dim{
	int start;
	int end;
}limit;

typedef struct joined{
int Start;
int mid;
int End;
}join;


int binary_search(int move,int start,int end)
{
	if (end<=start)
	{
        	if(move > n1[end])
		{
			return (end + 1);
		} 
		else
		{
			return end;
		}
	}
 
    	int mid = (start + end) / 2;
 
    	if(move == n1[mid])
	{
        	return mid + 1;
	}
 
    	if(move > n1[mid])
	{
        	return binary_search(move,mid + 1, end);
	}
    	return binary_search(move, start,mid - 1);
}


void* merge(void *args) {
   
    struct joined *params = (struct joined*) args;
    int begin = params->Start,
        mid = params->mid,
        end = params->End;


    int i = begin, j = mid, tpos = begin;

    while (i < mid && j <= end)
    {
        if (n1[i] < n1[j])
            n2[tpos++] = n1[i++];
        else
            n2[tpos++] = n1[j++];
    }

    
    while (i <mid)
        n2[tpos++] = n1[i++];

    
    while (j <= end)
        n2[tpos++] = n1[j++];
    return NULL;
}

void* insertion(void *l)
{
	limit *l1= (limit*)l;
	int i=l1->start;
	i++;
	int j,k,move;
	while(i<=l1->end)
	{
		j=i-1;
		move=n1[i];
		k=binary_search(move,l1->start,j);
		while(j>=k)					
		{
			n1[j+1]=n1[j];
			j--;
		}
		n1[j+1]=move;
		i++; 
	}
	for(int i=l1->start;i<l1->end;i++)
	{
		printf("%d ",n1[i]);
	}
	printf("\n\n\n");
	return NULL;
}


void fillarray(int size) {
    int i;
    srand(time(NULL));
    for (i=0; i<size; i++)
        n1[i] = rand() % 100;
}

void print_array(int list[], int size) {
    int i;
    for (i=0; i<size-1; i++)
        printf("%d, ", list[i]);
    printf("%d\n", list[i]);
}


void file_create(double start,double stop)
{
	FILE *ptr;
	ptr=fopen("PTHREAD_Insertion.txt","a+");
	if(ptr==NULL)
	{
		printf("Unable to Open File");
		exit(1);
	}
	else
	{
		double total= (double)(stop-start);
		fprintf(ptr,"Time Taken(Burst Time): %lf\n",total);
		fprintf(ptr,"Time Taken(Clock Time): %lu\n",(Stop2.tv_sec-start2.tv_sec)*1000000+Stop2.tv_usec-start2.tv_usec);	
	}
	fclose(ptr);
}

int main()
{
	fillarray(SIZE);
	pthread_t t1,t2;
	limit l1,l2;
	l1.start=0;
	l1.end=SIZE/2;
	l2.start=l1.end+1;
	l2.end=SIZE-1;
	join j1;
	j1.Start=l1.start;
	j1.mid=l2.start;
	j1.End=l2.end;
	
	pthread_t m1;
	
	double Start1=clock();
	gettimeofday(&start2,NULL);
	
	pthread_create(&t1,NULL,insertion,&l1);
		
	pthread_create(&t2,NULL,insertion,&l2);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_create(&m1,NULL,merge,&j1);
		
	pthread_join(m1,NULL);
	gettimeofday(&Stop2,NULL);	
	double stop1=clock();
	
	print_array(n2,SIZE);
	file_create(Start1,stop1);
	return 0;
}
