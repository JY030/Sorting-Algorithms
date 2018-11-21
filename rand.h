#include <cctype>
#include <fstream>
#include <iostream>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

void merge(int array[], int left, int mid, int right, int &copies);
void mergesort(int array[], int left, int right, int &copies);
