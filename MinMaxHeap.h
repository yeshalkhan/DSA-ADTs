#pragma once
#include <iostream>
#include "MinHeap.h"
using namespace std;
template <typename T>
void downHeap(int i, T* arr, int size)
{
	T minChild, temp;
	int left, right;
	while (i < size)
	{
		left = i * 2 + 1, right = i * 2 + 2;
		if (left >= size)			//no children
			return;
		else if (right < size)	    //both right & left children
			minChild = arr[right] < arr[left] ? right : left;
		else                        //only left child
			minChild = left;
		if (arr[i] > arr[minChild])
		{
			swap(arr[i], arr[minChild]);
			i = minChild;
		}
		else
			return;
	}
}
template <typename T>
void buildMinHeap(T* arr, int size)
{
	if (size <= 0)
		return;
	for (int i = (size + 1) / 2; i >= 0; i--)
		downHeap(i, arr, size);
}
template <typename T>
void heapSort(T* arr, int size)
{
	//Descending
	MinHeap<T> temp(log2(size) + 1);
	for (int i = 0; i < size; i++)			//make a heap from given array
		temp.insert(arr[i]);
	T* result = new T[size];
	for (int i = size - 1; i >= 0; i--)		//store the smallest value ar last, 2nd smallest at 2nd last in the result array
		result[i] = temp.deleteMin();
	for (int i = 0; i < size; i++)			//copy result array to original array
		arr[i] = result[i];
	if (result)								//delete extra array
	{
		delete[] result;
		result = nullptr;
	}
}