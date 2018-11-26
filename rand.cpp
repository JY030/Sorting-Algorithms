#include "rand.h"

int main()
{
	int size = 1000;  //Size of the array that needs to be sorted
	int copies = 0; //Number of copies the Merge sort makes
	int testing = 0; //Variable for runing the program before saving the output
	int run = 20;  //Number of times to run the sorting program
	long double mean = 0;
	long double iqr = 0;
	long double Q1 = 0;
	long double Q3 = 0;
	long double Q3start = 0;
	int mergeArray[size];
	int quickArray[size];
	int sortTime[run];
	int n, o;
	int flag = 0;
	double loop;
	ofstream mergeUnsort;
	mergeUnsort.open("mergesortUnsorted.txt");
	ofstream mergeSort;
	mergeSort.open("mergesortSorted.txt");
	ofstream mergeTime;
	mergeTime.open("mergesortTime.txt");
	ofstream mergeCopy;
	mergeCopy.open("mergesortCopy.txt");
	srand(time(NULL));
	for(int k =0; k < 1000; ++k) //Run the program 1000 times before saving output
	{
		for(int l = 0; l < size; ++l)
		{
			mergeArray[l] = (rand());
			quickArray[l] = (rand());
		}
		mergesort(mergeArray, 0, size-1, testing);
	}
	for(int m =0; m < run; ++m)
	{
		for (int i =0; i < size; ++i)  //creating array to sort
		{
			mergeArray[i] = (rand());
			mergeUnsort << mergeArray[i] << "	";
			quickArray[i] = (rand());
		}
		mergeUnsort << endl << endl;
		auto start = std::chrono::high_resolution_clock::now(); //start timer
		mergesort(mergeArray, 0, size-1, copies);
		auto stop = std::chrono::high_resolution_clock::now(); //end timer
		auto duration = duration_cast<microseconds>(stop - start); //timer in micro seconds
		mergeTime << "Time it took = " << duration.count() << " micro seconds" << endl;
		sortTime[m] = duration.count();
		for(int j =0; j < size; ++j)  //print sorted array
			mergeSort << mergeArray[j] << "	";
		mergeSort << endl << endl;
		mergeCopy << "Number of copies = " << copies << endl;  // Number of copies from merge sort
	}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//removing outliers
	mergesort(sortTime, 0, run-1, copies);
	for(int i = 0; i < run; ++i)
	{
		cout << sortTime[i] << " ";
	}
	cout << endl;


	while(flag == 0)
	{
		for(int i = 0; i < run; ++i)
			mean = mean + sortTime[i];
		mean = mean / run;
		iqr = run / 4;
		Q3start = ceil(iqr * 3);
		for(n = 1; n < ceil(iqr); ++n)
		{
			Q1 = Q1 + sortTime[n];
		}
		Q1 = Q1 / n;
		for(o = 1; o < Q3start; ++o)
		{
			Q3 = Q3 + sortTime[o];
		}
		Q3 = Q3 / o;
		iqr = Q3 - Q1;
		loop = 1.5 * iqr;
		if(sortTime[run-1] - mean > loop)
		{
			sortTime[run] = 0;
			--run;
		}
		else
			flag = 1;
	}

	for(int i = 0; i < run; ++i)
		cout << sortTime[i] << " ";
	cout << endl;
}
