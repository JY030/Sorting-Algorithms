/*
Merge sort

*/
#include "rand.h"
//---------------------------------------------------------------------------
void mergesort(int array[], int left, int right, int &copies)
{
	if(left < right)
	{
		int mid = left+(right-left)/2;
		mergesort(array, left, mid, copies);
		mergesort(array, mid+1, right, copies);
		merge(array, left, mid, right, copies);
	}
}
//-----------------------------------------------------------------------------
void merge(int array[], int left, int mid, int right, int &copies)
{
int n1 = mid - left + 1;
int n2 = right - mid;
int i; //index for array Left array
int j; //index for array Right array
int k;
int Llist[n1];  //Left array
int Rlist[n2];  //Right array
	for (i=0; i < n1; ++i)
		Llist[i] = array[left + i];
	for (j=0; j < n2; ++j)
		Rlist[j] = array[mid + 1 + j];
i=0;
j=0;
k=left;
	while (i < n1 && j < n2)
	{
		if (Llist[i] <= Rlist[j])
		{
			array[k] = Llist[i];
			++i;
			++copies;
		}
		else
		{
			array[k] = Rlist[j];
			++j;
			++copies;
		}
		++k;
	}
	while (i < n1)
	{
		array[k] = Llist[i];
		++i;
		++k;
		++copies;
	}
	while (j < n2)
	{
		array[k] = Rlist[j];
		++j;
		++k;
		++copies;
	}
}
