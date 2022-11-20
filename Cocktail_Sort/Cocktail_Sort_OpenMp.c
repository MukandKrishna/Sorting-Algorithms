#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<stdlib.h>
#include<omp.h>
void Cocktail_Sort(int *A,int size)
{
	int start=0,end=size-1;
	int swap=1;
	int counter=0;
	while(counter!=size/2+1)
	{
		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section	
			{
				#pragma omp parallel for shared(A,swap,start)  
					for(int i=start;i<size/2;i+=2)  
					{
					
						if( *(A+i)>*(A+(i+1)))
						{
							int temp=*(A+i);
							*(A+i)=*(A+(i+1));
							*(A+(i+1))=temp;
							swap=1;
						}
					
					}
					
			}				
			#pragma omp section
			{
				#pragma omp parallel for shared(A,swap)	
					for(int j=end;j>(size/2 +1);j-=2)
					{
					
						if(*(A+j)<*(A+(j-1)))
						{
							int temp=*(A+j);
							*(A+(j))=*(A+(j-1));
							*(A+(j-1))=temp;
							swap=1;
						}
					}
			}
		}
			
			(start==0)?start++:start--;
			(end==size-1)?end--:end++;
			counter++;		
	
	}
} 
int* merge(int *P,int n)
{
	int *FP=(int *) calloc(n,sizeof(int));
	int i=0,j=n/2+1,k=0;
	for(;i<=n/2;k++)
	{
		if(P[i]<P[j] || j>=n)
		{
			FP[k]=P[i];
			i++;
		}
		else
		{
			if(j<n)
			{
				FP[k]=P[j];
				j++;
			}
		}
	}
	while(j<n)
	{
		FP[k]=P[j];
		j++;
		k++;		
	}
	return FP;
}
void Filling(double Start,double End,double Total)
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
		double total= (double)(End-Start)/(double)CLOCKS_PER_SEC;
		fprintf(ptr,"Burst Time Taken By OpenMp_Cocktail_Sort is %lf\n",total);
		fprintf(ptr,"Time Taken By OpenMp_Cocktail_Sort is %lf\n",Total);

	}
	fclose(ptr);
	
}
int main(void)
{
	srand(time(NULL));
	int n;
	struct timeval stop, start;
	printf("Enter The Size of Array: ");
	scanf("%d",&n);
	int *ptr=(int *) calloc(n,sizeof(int));
	printf("Enter The Elements Array\n");
	for(int i=0;i<n;i++)	
	{
		*(ptr+i)=rand()%n;
	}	
	double Start=clock();
	gettimeofday(&start, NULL);	
	Cocktail_Sort(ptr,n);
	int *fp=merge(ptr,n);
	gettimeofday(&stop, NULL);
	double End=clock();
	printf("Sorted Array: ");
	for(int i=0;i<n;i++)
	{
		printf("%d ",(fp[i]));
	}
	printf("\n");
	double Total=(double)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
	Filling(Start,End,Total);
}
