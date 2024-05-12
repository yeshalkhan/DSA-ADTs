#pragma once
#include <iostream>
using namespace std;
template <typename T>
class NDArray
{
	T* data;
	int noOfDimensions;
	int* sizeOfDimensions;
	int* startingIndex;
	int getSizeOfData() const
	{
		int result = 1;
		for (int i = 0; i < noOfDimensions; i++)
			result *= sizeOfDimensions[i];
		return result;
	}
	bool isValidDimension(int i) const
	{
		return i >= 0 && i < noOfDimensions;
	}
public:
	NDArray(const initializer_list<int> sizeD = {}, const initializer_list<int> startI = {})
	{
		if (sizeD.size() <= 0)
		{
			noOfDimensions = 0;
			sizeOfDimensions = startingIndex = data = nullptr;
			return;
		}
		if (sizeD.size() < startI.size())
			return;
		noOfDimensions = sizeD.size();
		sizeOfDimensions = new int[noOfDimensions];
		startingIndex = new int[noOfDimensions];
		int size = 1;
		for (int val : sizeD)
			size *= val;
		data = new T[size];
		int i = 0;
		for (int val : sizeD)
			sizeOfDimensions[i++] = val;
		if (startI.size() <= 0)
		{
			for (int i = 0; i < noOfDimensions; i++)
				startingIndex[i] = 0;
			return;
		}
		i = 0;
		for (int val : startI)
			startingIndex[i++] = val;
		while (i < noOfDimensions)
			startingIndex[i++] = 0;
	}
	~NDArray()
	{
		noOfDimensions = 0;
		if (data)
		{
			delete[]data;
			data = nullptr;
		}
		if (startingIndex)
		{
			delete[]startingIndex;
			startingIndex = nullptr;
		}
		if (sizeOfDimensions)
		{
			delete[]sizeOfDimensions;
			sizeOfDimensions = nullptr;
		}
	}
	NDArray(const NDArray<T>& ref)
	{
		if (ref.data == nullptr)
		{
			noOfDimensions = 0;
			sizeOfDimensions = startingIndex = data = nullptr;
			return;
		}
		noOfDimensions = ref.noOfDimensions;
		sizeOfDimensions = new int[noOfDimensions];
		for (int i = 0; i < noOfDimensions; i++)
			sizeOfDimensions[i] = ref.sizeOfDimensions[i];
		startingIndex = new int[noOfDimensions];
		for (int i = 0; i < noOfDimensions; i++)
			startingIndex[i] = ref.startingIndex[i];
		int sizeOfData = ref.getSizeOfData();
		data = new T[sizeOfData];
		for (int i = 0; i < sizeOfData; i++)
			data[i] = ref.data[i];
	}
	NDArray<T>& operator=(const NDArray<T>& ref)
	{
		if (this = &ref)
			return *this;
		this->~NDArray();
		if (ref.data == nullptr)
		{
			noOfDimensions = 0;
			sizeOfDimensions = startingIndex = data = nullptr;
			return *this;
		}
		noOfDimensions = ref.noOfDimensions;
		sizeOfDimensions = new int[noOfDimensions];
		for (int i = 0; i < noOfDimensions; i++)
			sizeOfDimensions[i] = ref.sizeOfDimensions[i];
		startingIndex = new int[noOfDimensions];
		for (int i = 0; i < noOfDimensions; i++)
			startingIndex[i] = ref.startingIndex[i];
		int sizeOfData = ref.getSizeOfData();
		data = new T[sizeOfData];
		for (int i = 0; i < sizeOfData; i++)
			data[i] = ref.data[i];
		return *this;
	}
	int getNumberOfDimensions() const
	{
		return noOfDimensions;
	}
	int getDimensionSize(const int d) const
	{
		if (isValidDimension(d))
			return sizeOfDimensions[d];
		exit(0);
	}
	int getDimensionLowerIndex(const int d) const
	{
		if (isValidDimension(d))
			return startingIndex[d];
		exit(0);
	}
	int getDimensionHigherIndex(const int d) const
	{
		if (isValidDimension(d))
			return startingIndex[d] + (sizeOfDimensions[d] - 1);
		exit(0);
	}
	bool isIndexBoundsValid(const initializer_list<int>& list)
	{
		if (list.size() != noOfDimensions)
			exit(0);
		int i = 0;
		for (int val : list)
		{
			if (!(val >= getDimensionLowerIndex(i) && val <= getDimensionHigherIndex(i)))
				return false;
			i++;
		}
		return true;
	}
	int getRowMajorIndexMapping(const initializer_list<int>& list) const
	{
		if (list.size() != noOfDimensions)
			exit(0);
		/*if (!(isIndexBoundsValid(list)))
			exit(0);*/
		int val = 0, div = 1, index = 0;
		int mul = getSizeOfData();
		for (int i : list)
		{
			i = i - startingIndex[index];
			div *= sizeOfDimensions[index++];
			val += i * mul / div;
		}
		return val + 1;
	}
	T& operator()(const initializer_list<int>& list)
	{
		if (!isIndexBoundsValid(list))
			exit(0);
		return data[getRowMajorIndexMapping(list)];
	}
	T& operator()(const initializer_list<int>& list) const
	{
		if (!isIndexBoundsValid(list))
			exit(0);
		return data[getRowMajorIndexMapping(list)];
	}
};

