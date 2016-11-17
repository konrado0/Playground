/*
 * Heap.h
 *
 *  Created on: Nov 16, 2016
 *      Author: konrad
 */

#ifndef HEAP_H_
#define HEAP_H_

class Heap {
public:
	static void Sort(std::vector<int>& array);

	Heap(std::vector<int>& array, size_t heap_size = 0);

	int Size(){ return heap_size; }
	int Max(){ return array[0]; }
	int ExtractMax();
	void IncreaseKey(size_t index, int value);
	void Insert(int value);
	void Delete(size_t index);


private:
	void MaxHeapify(size_t i);
	void BuildHeap();

	size_t Left(size_t i){ return ((i+1) << 1) -1; }
	size_t Right(size_t i){ return (i+1) << 1; }
	size_t Parent(size_t i){ return i == 0 ? 0 : ((i+1) >> 1) - 1; }

	std::vector<int>& array;
	size_t heap_size;
};

#endif /* HEAP_H_ */
