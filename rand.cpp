#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;


int main()
{
	srand(time(NULL));
	for (int i =0; i < 20; ++i)
	cout << (rand() & 10 ) + 1 << endl;
}
