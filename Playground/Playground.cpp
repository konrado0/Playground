// Playground.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

void PrintVector(std::vector<int> array)
{
	for(size_t i=0; i<array.size(); ++i)
		cout << array[i] << " ";
	cout << endl;
}

void TestMaxSubarray();
void TestHeap();

int main()
{
	TestHeap();
	cout << "Hello world!" << endl;
	return 0;
}

