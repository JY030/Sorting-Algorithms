#include "rand.h"

int main()
{
	int size = 1000;  //Size of the array that needs to be sorted
	int copies = 0; //Number of copies the Merge sort makes
	int testing = 0; //Variable for runing the program before saving the output
	int run = 5;  //Number of times to run the sorting program
	int array[size];
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
			array[l] = (rand());
		}
		mergesort(array, 0, size-1, testing);
	}
	for(int m =0; m < run; ++m)
	{
		for (int i =0; i < size; ++i)  //creating array to sort
		{
			array[i] = (rand());
			mergeUnsort << array[i] << "	";

		}
		mergeUnsort << endl << endl;
		auto start = std::chrono::high_resolution_clock::now(); //start timer
		mergesort(array, 0, size-1, copies);
		auto stop = std::chrono::high_resolution_clock::now(); //end timer
		auto duration = duration_cast<microseconds>(stop - start); //timer in micro seconds
		mergeTime << "Time it took = " << duration.count() << " micro seconds" << endl;
	
		for(int j =0; j < size; ++j)  //print sorted array
			mergeSort << array[j] << "	";
		mergeSort << endl << endl;
		mergeCopy << "Number of copies = " << copies << endl;  // Number of copies from merge sort
	}
}
