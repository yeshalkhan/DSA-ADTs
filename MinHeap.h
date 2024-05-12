#pragma once
#include <iostream>
#include <math.h>
using namespace std;
template <typename T>
class MinHeap
{
	T* data;
	int arraySize;
	int maxHeight;
	int noOfNodes;
	int findMinimum(int i)				//returns index of smallest child
	{
		int left = i * 2 + 1, right = i * 2 + 2;
		if (left >= noOfNodes)				//no left child so no right child either
			return -1;
		else if (right >= noOfNodes)		//no right child so only left child
			return left;
		else                                //both left & right child so return the small one
			return data[left] < data[right] ? left : right;
	}
	void swap(T &val1, T &val2)
	{
		T val3 = val1;
		val1 = val2;
		val2 = val3;
	}
public:
	MinHeap(int h)
	{
		if (h <= 0)
		{
			data = nullptr;
			arraySize = maxHeight = noOfNodes = 0;
			return;
		}
		maxHeight = h;
		arraySize = pow(2, maxHeight) - 1;
		noOfNodes = 0;
		data = new T[arraySize];
	}
	~MinHeap()
	{
		if (data)
		{
			delete []data;
			data = nullptr;
			arraySize = maxHeight = noOfNodes = 0;
		}
	}
	T getMin()
	{
		if (noOfNodes == 0)
			exit(0);
		return data[0];
	}
	void insert(T val)
	{
		if (noOfNodes == arraySize)
			return;
		data[noOfNodes++] = val;
		int cur = noOfNodes - 1;
		while (cur >= 1 && data[cur] < data[(cur - 1) / 2])        //if current value is smaller than its parent, swap
		{
			swap(data[cur], data[(cur - 1) / 2]);
			cur = (cur - 1) / 2;
		}
	}
	T deleteMin()
	{
		if (noOfNodes == 0)
			exit(0);
		T min = data[0];
		data[0] = data[--noOfNodes];
		int cur = 0;
		int minChild;
		while (cur < noOfNodes)
		{
			minChild = findMinimum(cur);
			if (minChild == -1)
				return min;
			else if (data[cur] > data[minChild])
			{
				swap(data[cur], data[minChild]);
				cur = minChild;
			}
			else		//if data arrangement is correct at one node, it'll be correct on all nodes below so so need to check
				return min;
		}
		return min;
	}
	void printHeap()
	{
		for (int i = 0; i < noOfNodes; i++)
			cout << data[i] << " ";
		cout << endl;
	}
};

