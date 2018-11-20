/*
Merge sort

*/

#include <cctype>
#include <fstream>
#include <iostream>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

//void *merge (int *array, int n, int m, int len);
void merge (int array[], int left, int mid, int right, int &copies);
void mergesort(int array[], int left, int right, int &copies);
int main (int check, char *yeah[])
{

int n;
int m;
int num;
int len;
int i;
int r;
int j;
int modnum = 10;
int count =0;
int copies =0;
j=0;
srand(time(NULL));

/*if (check == 1)
{
cout << "Error missing argument" << endl;;
return 0;
}

if (check > 2)
{
cout << "Error to many arguments" << endl;
return 0;
}

num=atoi(yeah[1]);
*/
num = 10;
if (num == 0)
{
cout << "Error invalid argument" << endl;
return 0;
}

int array[num];
for (i=0; i < num; i++)
{
	r = rand() % modnum;
	array[i] = r;
	++count;
	cout <<array[i] << " ";
}
cout << endl;;

mergesort(array, 0, count-1, copies);

for (j=0; j < num; ++j)
{
	cout << array[j] << " ";
}
cout << endl;
cout << "Number of copies = " << copies << endl;
}
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
int i; //index for array a
int j; //index for array b
int k;
int Llist[n1];
int Rlist[n2];

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
