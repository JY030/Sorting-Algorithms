#include <iostream>
#include <chrono>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <algorithm> //C++ default sort function for base comparison


using namespace std;
using namespace std::chrono;

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


int Hoarepartition(int A[], int low, int high, int &numswap)
{
//	srand(time(NULL)); //if put in the program will blow stack
	int random = rand() % high; //random pivot
	int pivot = A[random];
	int y = low - 1;
	int z = high + 1;
	while (true)
	{
		do 
		{
			z = z - 1;
		} 
		while (A[z] > pivot);

		do
		{
			y = y + 1;
		} 
		while (A[y] < pivot);

		if (y >= z)
		{
			return z;
		}
		else
		{
			numswap++;
			swap(&A[y], &A[z]);
		}
	}
}


void Quicksort(int *A, int low, int high, int &numswap)
{
	if(low < high)
	{
		int partitionindex = Hoarepartition(A, low, high, numswap);
		Quicksort(A, low, partitionindex, numswap);
		Quicksort(A, partitionindex+1, high, numswap);
	}

}
int main()
{
	srand(time(NULL));
	int num = 0;
	int count = 0;
	int sizeofarray= 10; //temporary sizeof array
	int numswap = 0;
	int fail = 0;
	num = sizeofarray;
	int *array1 = new int[num];
	int *array2 = new int[num];
	for (int i = 0; i < num; i++)
	{
		int r = rand() % num;
		array1[i] = r;
		array2[i] = r;
		cout << array1[i] << " ";
	}
	Quicksort(array1, 0, num-1, numswap);
	cout << endl;
	for (int i = 0; i < num; i++)
	{
		cout << array1[i] << " ";
	}
	
	cout << endl;
	
	sort(array2, array2+num);
	for (int i = 0; i < num; i++)
	{
		cout << array2[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < sizeofarray; i++)
	{
		if (array1[i] != array2[i])
		{
			fail = 1;
		}
	}
	if (fail == 0)
	{
		cout << numswap << " PASS";

	}
	if (fail == 1)
	{
		cout <<  "Fail";

	}


	delete[] array1;
	delete[] array2;
	return 0;

}

