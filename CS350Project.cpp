
#include "pch.h" //visual studios includes it's own header file to be compiled
#include <iostream>
#include <chrono>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include <algorithm> //C++ default sort function for base comparison and shuffle
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cctype>
#include <random>       // std::default_random_engine

using namespace std;
using namespace std::chrono;

void swap(long* x, long* y)
{
	long temp = *x;
	*x = *y;
	*y = temp;
}

//PsuedoCode used from https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
//Was having trouble choosing random pivot because choosing random pivot in the hoare partition caused the code to never end after the array size became larger then 10
/*partition(arr[], lo, hi)
pivot = arr[lo]
i = lo - 1  // Initialize left index
j = hi + 1  // Initialize right index

// Find a value in left side greater
// than pivot
do
i = i + 1
while arr[i]  pivot

if i >= j then
return j

swap arr[i] with arr[j]

partition_r(arr[], lo, hi)
r = Random number from lo to hi
Swap arr[r] and arr[lo]
return partition(arr, lo, hi)

quicksort(arr[], lo, hi)
if lo < hi
	p = partition_r(arr, lo, hi)
	quicksort(arr, p, hi)
	quicksort(arr, p + 1, hi)
*/

long Hoarepartition(long A[], long low,  long high, long &numswap)
{
//	long random = rand() % high;//random pivot causes stack overflow at lower numbers even at size 10 or placed in hoare partition
//	long pivot = A[random];// Actually random pivot because of the swap in randompivot function
	//long random = rand() % high;
	//long pivot = A[random]; //Gets caught in a loop and doesn't seem to end when importing a random pivot into the function after array size 10
	// can also stackoverflow at size 10
	
	long pivot = A[(low + high) / 2]; //chose this pivot because even at lower numbers using rand above either causes a loop that seems to never end or a stack overflow
	long y = low - 1;
	long z = high + 1;
	while (true)
	{
		do
		{
			y = y + 1;
		} while (A[y] < pivot);
		
		do
		{
			z = z - 1;
		} while (A[z] > pivot);

		if (y >= z)
		{
			return z;
		}
		numswap++;
		swap(A[y], A[z]);
	}
}

long randompivot(long A[], long low, long high, long &numswaps)
{
	long random = rand() % high;//random pivot causes stack overflow at lower numbers even at size 10 or placed in hoare partition
	swap(A[random], A[low]); //chooses a random pivot and sets as the new low
	return Hoarepartition(A, low, high, numswaps);
}
void Quicksort(long *A, long low, long high, long &numswap)
{
	if(low < high)
	{
//		long partitionindex = randompivot(A, low, high, numswap);
		int partitionindex = Hoarepartition(A, low, high, numswap);
		Quicksort(A, low, partitionindex, numswap);
		Quicksort(A, partitionindex + 1, high, numswap);

	}

}

void merge(long array[], long left, long mid,  long right,  long &copies)
{
	long n1 = mid - left + 1;
	long n2 = right - mid;
	long i; //index for array Left array
	long j; //index for array Right array
	long k;

	long *Llist = new long[n1];  //Left array
	long *Rlist = new long[n2];  //Right array
	for (i = 0; i < n1; ++i)
		Llist[i] = array[left + i];
	for (j = 0; j < n2; ++j)
		Rlist[j] = array[mid + 1 + j];
	i = 0;
	j = 0;
	k = left;
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
	delete[] Llist;
	delete[] Rlist;
}

void mergesort(long array[], long left, long right, long &copies)
{
	if (left < right)
	{
		long mid = left + (right - left) / 2;
		mergesort(array, left, mid, copies);
		mergesort(array, mid + 1, right, copies);
		merge(array, left, mid, right, copies);
	}
}

long arraychecker(long array1[], long array2[],  long size) //array1 is compared to array2 where array 2 is default sort oracle test
{
	int fail = 0;
	for (int i = 0; i < size && fail == 0; i++)
	{
		if (array1[i] != array2[i])
		{
			fail = 1;
		}
	}
	if (fail == 0)
	{
		return 0; // Passed

	}
	if (fail == 1)
	{
		return 1; // Failed

	}
}

void myranshuffle( long *array0, long *array1,  long *array2,  long *array3, long size)
{
	for (long i = 0; i < size; i++)
	{
		long r = rand() % (size);
		swap(array0[i], array0[r]);
		swap(array1[i],array1[r]);
		swap(array2[i], array2[r]);
		swap(array3[i], array3[r]);
	}
}

void resetArray(long *array0, long *array1, long size) //array0 default array to set back to
{
	for (long i = 0; i < size; i++)
	{
		array1[i] = array0[i];
	}
}

int main()
{
	srand(1543096165); //Repeatable Results with a set seed
//	srand(time(NULL));
//	unsigned int timer = time(NULL);
//	cout << timer << endl;
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	//int num = 0;
	int count = 0;
	long size = 10; // sizeof array need to hard code this
	long numswap = 0;
	int fail = 0;
	long copies = 0;
	//num = sizeofarray;
	ofstream mergeTime;
	mergeTime.open("mergesortTime.txt");
	ofstream quickTime;
	quickTime.open("quickTime.txt");
	ofstream Unsorted;
	Unsorted.open("random.txt");
	
	long *array0 = new long[size]; //default array to reset to
	long *array1 = new long[size]; //visual studios doesn't like declared array[variable] quicksory array
	long *array2 = new long[size]; //default sort array
	long *array3 = new long[size]; //mergesort array

	for (long i = 0; i < size; i++) //initialize array
	{
		array0[i] = i;
		array1[i] = i;
		array2[i] = i;
		array3[i] = i;
	}
	myranshuffle(array0, array1, array2, array3, size); //randomizes array for same random data

 //check if the arrays are created correctly which they are
/*	int results0 = arraychecker(array0, array2, size);
	if (results0 == 0)
	{
		cout << "PASS" << endl;
	}
	if (results0 == 1)
	{
		cout << "FAIL" << endl;
	}

	int results1 = arraychecker(array3, array2, size);
	if(results1 == 0)
	{
		cout << "PASS" << endl;
	}
	if (results1 == 1)
	{
		cout << "FAIL" << endl;
	}
	int results2 = arraychecker(array1, array2, size);
	if(results2 == 0)
	{
		cout << "PASS" << endl;
	}
	if (results2 == 1)
	{
		cout << "FAIL" << endl;
	}
*/

	auto start3 = std::chrono::high_resolution_clock::now(); //start timer
	sort(array2, array2 + size);
	auto stop3 = std::chrono::high_resolution_clock::now(); //end timer
	auto duration3 = duration_cast<microseconds>(stop3 - start3); //timer in micro seconds
	cout << "Basic C++ sort time: " << duration3.count() << " microseconds" << endl;
	
	mergeTime << "Execution Time(microseconds)" << "\t" << "Number of Copies" << "\t" << "PASS/FAIL" << endl; 
	for (int i = 0; i < 30; i++) //warming the cache tested
	{
		mergesort(array3, 0, size - 1, copies);
		copies = 0;
		resetArray(array0, array3, size);
	}
	for (int i = 0; i < 20; i++)
	{
		auto start = std::chrono::high_resolution_clock::now(); //start timer
		mergesort(array3, 0, size - 1, copies);
		auto stop = std::chrono::high_resolution_clock::now(); //end timer
		auto duration = duration_cast<microseconds>(stop - start); //timer in micro seconds
		//array3[0] = 77777; // to cause mergeresult to fail to test PASS FAIL write to text
	//	auto start2 = std::chrono::high_resolution_clock::now(); //start timer
	//	sort(array2, array2 + size);
		//	auto stop2 = std::chrono::high_resolution_clock::now(); //end timer
		//	auto duration2 = duration_cast<microseconds>(stop2 - start2); //timer in micro seconds
		//	cout << duration2.count() << endl;
		//	auto start3 = std::chrono::high_resolution_clock::now(); //start timer
		int mergeresults = arraychecker(array3, array2, size);
		//	auto stop3 = std::chrono::high_resolution_clock::now(); //end timer
		//	auto duration3 = duration_cast<microseconds>(stop3 - start3); //timer in micro seconds
		//	cout << duration3.count() << endl;
		mergeTime << duration.count() << "\t" << copies << "\t";
		if (mergeresults == 0)
		{
			mergeTime << "PASS" << endl;
		}
		if (mergeresults == 1)
		{
			mergeTime << "FAIL" << endl;
		}
		copies = 0;
		resetArray(array0, array3, size);
		/* test to see if the array reset proprerly. PASSED for all
		int results0 = arraychecker(array0, array3, size);
		if (results0 == 0)
		{
			cout << "PASS" << endl;
		}
		if (results0 == 1)
		{
			cout << "FAIL" << endl;
		}
		/// */
	}

	
	quickTime << "Execution Time(microseconds)" << "\t" << "Number of swaps" << "\t" << "PASS/FAIL" << endl;
	auto start2 = std::chrono::high_resolution_clock::now(); //start timer
	Quicksort(array1, 0, size-1, numswap);
	auto stop2 = std::chrono::high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2); //timer in micro seconds
	int Quickresults = arraychecker(array1, array2, size); // checks if the array is correct by comparing to basic sort
	quickTime << duration2.count() << "\t" << numswap << "\t";
	if (Quickresults == 0)
	{
		quickTime << "PASS" << endl;
	}
	if (Quickresults == 1)
	{
		quickTime << "FAIL" << endl;
	}
	

	delete[] array1;
	delete[] array2;
	delete[] array3;
	return 0;

}

