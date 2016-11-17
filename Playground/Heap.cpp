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

void Heap::Sort(std::vector<int>& array) {
	Heap heap(array);

	while(heap.heap_size>1) {
		std::swap(array[heap.heap_size - 1], array[0]);
		heap.heap_size--;
		heap.MaxHeapify(0);
	}
}

int Heap::ExtractMax()
{
	if(heap_size == 0)
		throw std::underflow_error("No items in the heap");
	int max = array[0];
	heap_size--;
	if(heap_size > 0) {
		array[0] = array[heap_size];
		MaxHeapify(0);
	}
	return max;
}

void Heap::IncreaseKey(size_t index, int value)
{
	if(index >= heap_size)
		throw std::overflow_error("No such high index in a heap");
	if(value < array[index])
		throw std::range_error("New value smaller then previous one");
	size_t parent = Parent(index);
	while(parent != index && array[parent] < value) {
		array[index] = array[parent];
		index = parent;
		parent = Parent(index);
	}
	array[index]=value;
}

void Heap::Insert(int value)
{
	if(heap_size < array.size())
		array[heap_size] = value;
	else
		array.push_back(value-1);
	heap_size++;
	IncreaseKey(heap_size-1, value);
}

void Heap::Delete(size_t index) {
	heap_size--;
	array[index] = array[heap_size];
	MaxHeapify(index);
}

void Heap::BuildHeap()
{
	for(int i=heap_size/2-1; i>=0; i--)
		MaxHeapify(i);
}


void TestHeap()
{
	std::vector<int> v4 = { 13, 3, 25, 20, -3, 16, 23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	Heap heap(v4);
//	PrintVector(v4);
	for(size_t i=v4.size(); i>0; --i) {
//		heap.ExtractMax();
		PrintVector(v4);
//		heap.IncreaseKey(12, 5);
		heap.Delete(1);
		heap.Insert(i*2);
//		PrintVector(v4);
	}

	std::vector<int> v5 = { -1, -4, 66, 77, 123, -67, 13, 3, 25, 20, -3, 16, 23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	Heap::Sort(v5);
	PrintVector(v5);
}
