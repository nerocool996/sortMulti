/**
 * thrSort.c
 * Purpose: Merge Sorts an array through multiple threads, array of randome no. is generated and passed to the function
 *
 * @author Harshit Anand
 * Date: 18.11.2016
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
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

int main(int argC,char *arg[])
{
	int size,i,k=20;
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
  	merge_sort(0,size-1,arr);
  	printf("\n Array after merge sort is: \n");
  	for(i=0;i<size;i++)
	{
		printf(" %d ",arr[i]);
	}
  	clock_t end = clock();
  	printf("\nElapsed: %f seconds\n", (double)(begin - end) / CLOCKS_PER_SEC);
  	printf("\n");
	return 0;
}
