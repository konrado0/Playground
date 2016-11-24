/*
 * quick_sort.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: konrad
 */

#include "stdafx.h"

using namespace std;

size_t Partition(vector<int>& array, size_t l, size_t r)
{
	size_t partition = l;

	for(size_t j = l; j<r; j++) {
		if(array[j] <= array[r]) {
			if(partition != j)
				swap(array[j], array[partition]);
			partition++;
		}
	}

	swap(array[partition], array[r]);
	return partition;
}

inline size_t RandomizedPartition(vector<int>& array, size_t l, size_t r)
{
	swap(array[l+ rand() % (r-l)], array[r]);
	return Partition(array, l, r);
}


void QuickSort(vector<int>& array, size_t l, size_t r)
{
	if(r==l) return;
	size_t q = RandomizedPartition(array, l, r);
	if(q>l) QuickSort(array, l, q-1);
	if(q<r-1) QuickSort(array, q+1, r);
}

inline void QuickSort(vector<int>& array)
{
	return QuickSort(array, 0, array.size()-1);
}

int RandomizeSelect(vector<int>& array, size_t k)
{
	size_t l=0, r=array.size()-1;
	--k;
	while(l<r) {
		size_t partition = RandomizedPartition(array, l, r);
		if(k==partition)
			return array[partition];
		if(k<partition)
			r=partition-1;
		else
			l=partition+1;
	}
	return array[l];
}

void TestQuickSort()
{
	std::vector<int> v4 = { 13, 3, 25, 20, -3, 16, 23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	PrintVector(v4);
	QuickSort(v4);
	PrintVector(v4);

	std::vector<int> v5 = { -1, -4, 66, 77, 123, -67, 13, 3, 25, 20, -3, 16, 23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	PrintVector(v5);
	cout << "11th: " << RandomizeSelect(v5, 11) << endl;
	QuickSort(v5);
	PrintVector(v5);
}
