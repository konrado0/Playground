/*
 * Heap.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: konrad
 */

#include "stdafx.h"

void PrintVector(std::vector<int> array);

Heap::Heap(std::vector<int>& array, size_t heap_size) : array(array), heap_size(heap_size)
{
	if(heap_size == 0)
		this->heap_size = array.size();
	BuildHeap();
}

void Heap::MaxHeapify(size_t i)
{
	size_t l, r, largest = i;
	while(i < heap_size / 2) {
		r = Right(i);
		l = Left(i);
		if(l <heap_size && array[largest] < array[l])
			largest = l;
		if(r <heap_size && array[largest] < array[r])
			largest = r;
		if(i == largest)
			break;

		std::swap(array[i], array[largest]);
		i = largest;
	}
}

void Heap::BuildHeap()
{
	for(int i=heap_size/2-1; i>=0; i--)
		MaxHeapify(i);
}


void TestHeap()
{
	std::vector<int> v4 = { 13, 3, 25, 20, -3, 16, 23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	Heap h4(v4);

	std::vector<int> v5 = { -1, -4, 66, 77, 123, -67, 13, 3, 25, 20, -3, 16, 23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	Heap h5(v5);
	PrintVector(v5);
}
