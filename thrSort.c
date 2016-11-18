/**
 * thrSort.c
 * Purpose: Merge Sorts an array through multiple threads, array of randome no. is generated and passed to the function
 *
 * @author Harshit Anand
 * Date: 18.11.2016
 */
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <stdlib.h>

/**
 * sturucture used to pass arguments to threads
 */
typedef struct{
  	int p;
  	int r;
  	int k;
  	int *arr;
}pass;

/**
 * Merges two sorted arrays
 *
 * @param starting index, dividing index, end index, pointer to the array
 */
void merge(int p,int q,int r,int *arr)
{
	int n1 = q-p+1,n2 = r-q,i,j,k;
	int L[n1+1],R[n2+1];
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	for (i=0;i<n1;i++)
		L[i] = arr[p+i];
	for (i=0;i<n2;i++)
		R[i] = arr[q+1+i];
	i=0;
	j=0;
	for (k=p;k<=r;k++)
	{
		if(L[i]<R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
	}
}
/**
 * Merge Sorts an array
 * @param starting index, ending index, pointer to the array
 */
void merge_sort(int p,int r,int *arr)
{
	if(p < r)
	{
		int q = (p+r)/2;
		merge_sort(p, q, arr);
		merge_sort(q+1,r,arr);
		merge(p,q,r,arr);
	}
}

/**
 * thread that calls merge sort
 * @param pointer to pass structure
 *
 */
void *sort(void *a)
{
	pass q = *((pass*) a);
  	int i;
	//printf("\n %d %d %d ",q.p,q.r,q.k);
  	if((q.p +q.k)< q.r)
    	{
	    	merge_sort(q.p,q.p+q.k-1,q.arr);

    	}
  	else
    	{
	    	merge_sort(q.p,(q.r-q.p)-1,q.arr);
    	}
}
/**
 *merges an array returned by threads
 * @param starting index, ending index, length of single array, pointer to the array
 */
void merge_final(int p,int r,int k,int *arr)
{
	int i,j=0,l=-1,ptrs[(r-p+1)/k+1],buff=INT_MAX,buffI=0;
  	int dList[(r-p+1)/k+1][k+1];
	for(i=0;i<(r-p+1);i++)
    	{
		if(i%k == 0)
	    	{
		    	dList[l][j] = INT_MAX;
	      		l++;
		    	ptrs[l]=0;
		    	j=0;
	    	}
	    	dList[l][j] = arr[i];
	    	j++;
	}
  	dList[l][j] = INT_MAX;

	for(i=0;i<(r-p+1);i++)
    	{
		for(j=0;j<=l;j++)
	    	{
	         	if (dList[j][ptrs[j]]<buff)
		    	{
				buff = dList[j][ptrs[j]];
				buffI = j;
			}
	    	}
	    arr[i] = buff;
	    ptrs[buffI]++;
	    buff = INT_MAX;
	}

}
int main(int argC,char *arg[])
{
	int size,i,k;
  	clock_t begin = clock();
	if (argC == 1)
	{
		printf("\nEnter the size of array");
		scanf("%d",&size);
	}
	else
	{
		size = atoi(arg[1]);
	}
	int arr[size];
	printf("\n%d \n",size);
	for(i=0;i<size;i++)
	{
		arr[i] = rand();
		printf("%d  ",arr[i]);
	}
  	k = size/4;
    	pthread_t thread[size/k+1];
  	pass argu[size/k+1];
  	for(i=0;i<size/k+1;i++)
    	{
	    	argu[i].p = 0 + i*k;argu[i].r = size;argu[i].k = k;argu[i].arr = arr;
      		pthread_create(&thread[i],NULL,sort,&argu[i]);
    	}
  	for(i=0;i<size/k+1;i++)
    	{
      		pthread_join(thread[i],NULL);
    	}
  	merge_final(0,size-1,k,arr);
  /**	printf("\n Array after merging is: \n");
  	for(i=0;i<size;i++)
	{
		printf(" %d ",arr[i]);
	}**/
  	clock_t end = clock();
  	printf("\nElapsed: %f seconds\n", (double)(begin - end) / CLOCKS_PER_SEC);
  	printf("\n");
	return 0;
}
