#pragma once
#include <iostream>
#include <math.h>
using namespace std;
template <typename T>
class MaxHeap
{
	int arraySize;
	int maxHeight;
	int noOfNodes;
	T* data;
	int findMaximum(int i)				//returns index of greatest child
	{
		int left = i * 2 + 1, right = i * 2 + 2;
		if (left >= noOfNodes)				//no left child so no right child either
			return -1;
		else if (right >= noOfNodes)		//no right child so only left child
			return left;
		else                                //both left & right child so return the large one
			return data[left] > data[right] ? left : right;
	}
	void swap(T& val1, T& val2)
	{
		T val3 = val1;
		val1 = val2;
		val2 = val3;
	}
public:
	MaxHeap(int h)
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
	~MaxHeap()
	{
		if (data)
		{
			delete[]data;
			data = nullptr;
			arraySize = maxHeight = noOfNodes = 0;
		}
	}
	T getMax()
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
		while (cur >= 1 && data[cur] > data[(cur - 1) / 2])       //if current value is greater tham its parent, swap
		{
			swap(data[cur], data[(cur - 1) / 2]);
			cur = (cur - 1) / 2;
		}
	}
	T deleteMax()
	{
		if (noOfNodes == 0)
			exit(0);
		T max = data[0];
		data[0] = data[--noOfNodes];
		int cur = 0;
		int maxChild;
		while (cur < noOfNodes)
		{
			maxChild = findMaximum(cur);
			if (maxChild == -1)
				return max;
			else if (data[cur] < data[maxChild])
			{
				swap(data[cur], data[maxChild]);
				cur = maxChild;
			}
			else		//if data arrangement is correct at one node, it'll be correct on all nodes below so so need to check
				return max;
		}
		return max;
	}
	void printHeap()
	{
		for (int i = 0; i < noOfNodes; i++)
			cout << data[i] << " ";
		cout << endl;
	}
};

