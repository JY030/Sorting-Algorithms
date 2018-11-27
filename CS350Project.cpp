
//#include "pch.h" //visual studios includes it's own header file to be compiled
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

//PsuedoCode Random pivot was used from https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
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
r = Random number from lo to hi of current stack
Swap arr[r] and arr[lo]
return partition(arr, lo, hi)

quicksort(arr[], lo, hi)
if lo < hi
	p = partition_r(arr, lo, hi)
	quicksort(arr, p, hi)
	quicksort(arr, p + 1, hi)
*/

long Hoarepartition(long A[], long low, long high, long &numswap)
{
	long random = low + rand() % (high - low); // random pivot Taken from https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
//	long random = rand() % high;//old random pivot code causes stack overflow at lower numbers even at size 50 or placed in hoare partition
	//long random = rand() % high;
	long pivot = A[random];
	//	long pivot = A[(low + high) / 2]; //old choice of pivot because even at lower numbers using rand above either causes a loop that seems to never end or a stack overflow
	long y = low - 1;
	long z = high + 1;
	while (true)
	{
		do
		{
			z = z - 1;
		} while (A[z] > pivot);

		do
		{
			y = y + 1;
		} while (A[y] < pivot);

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


void Quicksort(long *A, long low, long high, long &numswap)
{
	if (low < high)
	{
		long partitionindex = Hoarepartition(A, low, high, numswap);
		Quicksort(A, low, partitionindex, numswap);
		Quicksort(A, partitionindex + 1, high, numswap);

	}

}

void merge(long array[], long left, long mid, long right, long &copies)
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

long arraychecker(long array1[], long array2[], long size) //array1 is compared to array2 where array 2 is default sort oracle test
{
	int fail = 0;
	for (int i = 0; i < size; i++)
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

void myranshuffle(long *array0, long *array1, long *array2, long *array3, long size)
{
	for (long i = 0; i < size; i++)
	{
		long r = rand() % (size);
		swap(array0[i], array0[r]);
		swap(array1[i], array1[r]);
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
	auto start0 = std::chrono::high_resolution_clock::now(); //start timer

	srand(1543096165); //Repeatable Results with a set seed taken at a cetain time
//	srand(time(NULL));
//	unsigned int timer = time(NULL);
//	cout << timer << endl;
	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	//int num = 0;
	int count = 0;
	long size = 100; // sizeof array need to hard code this starting size should be 100
	long numswap = 0;
	int fail = 0;
	long copies = 0;
	int n, o;
	int flag = 0;
	double loop;
	long double mean = 0;
	long double iqr = 0;
	long double Q1 = 0;
	long double Q3 = 0;
	long double Q3start = 0;
	long run = 20; // data size 
	//num = sizeofarray;
	ofstream mergeTime;
	mergeTime.open("mergesortTime.txt");
	ofstream quickTime;
	quickTime.open("quickTime.txt");
	ofstream averagemerge;
	averagemerge.open("averagemerge.txt");
	ofstream averagequick;
	averagequick.open("averagequick.txt");

	//	ofstream Unsorted;
	//	Unsorted.open("random.txt"); dont't need this was for testing purposes for seeing the random array
	long mergesortTime[size]; //mergesort averages
	long quicksortTime[size]; //Quicksort averages
	

	for (int a = 1; a < 7; a++) // a = 6 for 1 million, 7 for 10 million data
	{
		cout << "Testing for Array Size: " << size << endl;
		long *array0 = new long[size];//default array to reset to make sure to never manipulate
		long *array1 = new long[size]; //visual studios doesn't like declared array[variable] quicksory array
		long *array2 = new long[size]; //default sort array
		long *array3 = new long[size]; //mergesort array


		cout << "Setting Random Array for Array Size:" << size << endl;
		for (long i = 0; i < size; i++) //initialize array
		{
			array0[i] = i;
			array1[i] = i;
			array2[i] = i;
			array3[i] = i;
		}
		myranshuffle(array0, array1, array2, array3, size); //randomizes array for same random data
		cout << "Finished Setting up Random Array for Array Size:" << size << endl;
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
	   //*/

	   //	auto start3 = std::chrono::high_resolution_clock::now(); //start timer
		cout << "Creating Test Oracle for Array Size:" << size << endl;
		sort(array2, array2 + size);
		cout << "Finished Creating Test Oracle" << endl;
		//	auto stop3 = std::chrono::high_resolution_clock::now(); //end timer
		//	auto duration3 = duration_cast<microseconds>(stop3 - start3); //timer in micro seconds
		//	cout << "Basic C++ sort time: " << duration3.count() << " microseconds" << endl;
		cout << "Starting Mergesort Test for Array Size: " << size << endl;
		mergeTime << "Array Size:" << "\t" << size << endl;
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
				mergesortTime[i] = duration.count();
			}
			if (mergeresults == 1)
			{
				mergeTime << "FAIL" << endl;
			}
			copies = 0;
			resetArray(array0, array3, size); //array0 is the unsorted array that is never changed
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
		*/
		}

		cout << "Finished Mergesort Test for Array Size: " << size << endl;
		cout << "Starting Quickesort Test for Array Size: " << size << endl;
		for (int i = 0; i < 30; i++) //warming the cache tested
		{
			Quicksort(array1, 0, size - 1, numswap);
			numswap = 0;
			resetArray(array0, array1, size);
		}

		quickTime << "Array Size:" << "\t" << size << endl;
		quickTime << "Execution Time(microseconds)" << "\t" << "Number of swaps" << "\t" << "PASS/FAIL" << endl;
		for (int i = 0; i < 20; i++)
		{
			auto start2 = std::chrono::high_resolution_clock::now(); //start timer
			Quicksort(array1, 0, size - 1, numswap);
			auto stop2 = std::chrono::high_resolution_clock::now();
			auto duration2 = duration_cast<microseconds>(stop2 - start2); //timer in micro seconds
			int Quickresults = arraychecker(array1, array2, size); // checks if the array is correct by comparing to basic sort
			quickTime << duration2.count() << "\t" << numswap << "\t";
			if (Quickresults == 0)
			{
				quickTime << "PASS" << endl;
				quicksortTime[i] = duration2.count();
			}
			if (Quickresults == 1)
			{
				quickTime << "FAIL" << endl;
			}
			numswap = 0;
			resetArray(array0, array1, size);
		}
		cout << "Finished Quicksort Test for Array Size: " << size << endl;

		mergesort(mergesortTime, 0, run - 1, copies); //sorts the data measurements for mergesort from least to greatest
	/*	for (int i = 0; i < run; ++i)
		{
			cout << mergesortTime[i] << " ";
		}
		cout << endl;
*/
		mergesort(quicksortTime, 0, run - 1, copies); //sorts the data measurements for quicksort from least to greatest
/*		for (int i = 0; i < run; ++i)
		{
			cout << quicksortTime[i] << " ";
		}
		cout << endl;
*/
		while (flag == 0)
		{
			for (int i = 0; i < run; ++i)
				mean = mean + mergesortTime[i];
			mean = mean / run;
			iqr = run / 4;
			Q3start = ceil(iqr * 3);
			for (n = 1; n < ceil(iqr); ++n)
			{
				Q1 = Q1 + mergesortTime[n];
			}
			Q1 = Q1 / n;
			for (o = 1; o < Q3start; ++o)
			{
				Q3 = Q3 + mergesortTime[o];
			}
			Q3 = Q3 / o;
			iqr = Q3 - Q1;
			loop = 1.5 * iqr;
			if (mergesortTime[run - 1] - mean > loop)
			{
				mergesortTime[run] = 0;
				--run;
			}
			else
				flag = 1;
		}

		flag = 0;
		Q1 = 0;
		Q3 = 0;
		mean = 0;

		while (flag == 0)
		{
			for (int i = 0; i < run; ++i)
				mean = mean + quicksortTime[i];
			mean = mean / run;
			iqr = run / 4;
			Q3start = ceil(iqr * 3);
			for (n = 1; n < ceil(iqr); ++n)
			{
				Q1 = Q1 + quicksortTime[n];
			}
			Q1 = Q1 / n;
			for (o = 1; o < Q3start; ++o)
			{
				Q3 = Q3 + quicksortTime[o];
			}
			Q3 = Q3 / o;
			iqr = Q3 - Q1;
			loop = 1.5 * iqr;
			if (quicksortTime[run - 1] - mean > loop)
			{
				quicksortTime[run] = 0;
				--run;
			}
			else
				flag = 1;
		}
		
		averagemerge << "Array Size:" << "\t" << size << endl;
		averagequick << "Array Size:" << "\t" << size << endl;
		averagemerge << "Execution Time(microseconds) & Removed Outliers" << endl;
		averagequick << "Execution Time(microseconds) & Removed Outliers" << endl;
		
		for (int i = 0; i < run; ++i)
		{
			averagemerge << mergesortTime[i];
			averagemerge << endl;
			averagequick << quicksortTime[i];
			averagequick << endl;
		}
		averagemerge << endl;
		averagequick << endl;

		delete[] array0;
		delete[] array1;
		delete[] array2;
		delete[] array3;
		mergeTime << endl;
		quickTime << endl;

		size = size * 10; //increase array size by power of 10
	}
	auto stop0 = std::chrono::high_resolution_clock::now(); //end timer
	auto duration0 = duration_cast<seconds>(stop0 - start0); //timer in micro seconds
	cout << endl;
	cout << "The Program took " << duration0.count() << " Seconds to complete" << endl;
	return 0;

}

