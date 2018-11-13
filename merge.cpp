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
void *merge (int *a, int *b);
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
cout <<array[i] << " ";
}
cout << endl;;

n=num/2;
m=0;
len=num;
int a[n];
int b[n];

for (i=0; i < n; i++)
{
a[i]=array[i];
}

for (i=n; i < num; i++)
{
b[j]=array[i];
j++;
}

//merge(array, n, m, len);
return merge(a, b);


}


//-----------------------------------------------------------------------------
//len = length of array
//n = half of length
//m = 0
//
//
//void *merge(int *array, int n, int m, int len)
int *merge(int *a, int *b)
{
int num = 10;
int n = num/2;
int i =0; //index for array a
int j =0; //index for array b
int c[num];

while (i != n && j != n)
{
	if (a[i] > b[j])
	{
		c[num] = b[j];
		++j;
		--num;
	}
	else
	{
		c[num] = a[i];
		++i;
		--num;
	}

}
while (i != n)
{
	c[num] = a[i];
	++i;
	--num;
}
while (j != n)
{
	c[num] = b[j];
	++j;
	--num;
}
for (int k =0; k < 10; ++k)
{
	cout << c[k] << " ";
}
cout << endl;
return c;


}
