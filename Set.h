//#pragma once
//#include <iostream>
//#include <string>
//using namespace std;
//
//template <typename T>
//class Set
//{
// T* data;
// int capacity;
// int noOfElements;
// void resize(int newCapacity);
//public:
// Set()
// {
// capacity = noOfElements = 0;
// data = new T[capacity];
// for (int i = 0; i < capacity; i++)
// data[i] = 0;
// }
// Set(const Set<T>& ref)
// {
// capacity = ref.capacity;
// noOfElements = ref.noOfElements;
// data = new T[ref.capacity];
// for (int i = 0; i < noOfElements; i++)
// data[i] = ref.data[i];
// }
// Set<T>& operator=(const Set<T>& ref)
// {
// capacity = ref.capacity;
// noOfElements = ref.noOfElements;
// data = new T[ref.capacity];
// for (int i = 0; i < noOfElements; i++)
// data[i] = ref.data[i];
// return *this;
// }
// bool insert(T element)
// {
// for (int i = 0; i < noOfElements; i++)
// {
// if (data[i] == element)
// return false;
// }
// if (noOfElements >= capacity)
// resize(capacity+10);
// data[noOfElements] = element;
// noOfElements++;
// return true;
// }
// bool remove(T element);
// void print() const
// {
// for (int i = 0; i < noOfElements; i++)
// cout << data[i] << " ";
// cout << endl;
// }
// int getCardinality() const
// {
// return noOfElements;
// }
// bool isMember(T val) const
// {
// for (int i = 0; i < noOfElements; i++)
// {
// if (data[i] == val)
// return true;
// }
// return false;
// }
// Set<T> calcUnion(const Set<T>& rhs)
// {
// int common = 0;
// for (int i = 0; i < capacity; i++)
// {
// for (int k = 0; k < rhs.capacity; k++)
// {
// if (data[i] == rhs.data[k])
// common++;
// }
// }
// Set temp(capacity + (rhs.capacity - common));
// for (int i = 0; i < capacity; i++)
// temp.data[i] = data[i];
// int J = 0;
// int tempIndex = capacity;
// temp.noOfElements = capacity;
// for (int i = capacity; i < rhs.capacity + capacity; i++)
// {
// bool flag = true;
// for (int k = 0; k < Intersection(rhs).capacity; k++)
// {
// flag = true;
// if (rhs.data[J] == Intersection(rhs).data[k])
// {
// flag = false; J++; break;
// }
// }
// if (flag == true)
// { temp.data[tempIndex++] = rhs.data[J++]; temp.noOfElements++; }
// }
// return temp;
// }
// Set Intersection(const Set& rhs) // returns the intersection of two given sets.
// {
// int j = 0;
// for (int i = 0; i < capacity; i++)
// {
// for (int k = 0; k < rhs.capacity; k++)
// {
// if (data[i] == rhs.data[k])
// {
// j++; break;
// }
// }
// }
// Set temp(j);
// j = 0;
// for (int i = 0; i < capacity; i++)
// {
// for (int k = 0; k < rhs.capacity; k++)
// {
// if (data[i] == rhs.data[k])
// {
// temp.data[j++] = data[i]; break;
// }
// }
// }
// temp.noOfElements = j + 1;
// for (int i = 0; i < temp.capacity - 1; i++)
// {
// for (int k = i + 1; k < temp.capacity; k++)
// {
// if (temp.data[i] == temp.data[k])
// {
// temp.data[k] = temp.data[k + 1];
// k++; temp.capacity--; temp.noOfElements--; break;
// }
// }
// }
// return temp;
// }
// bool isSubset(const Set<T>& rhs)
// {
// Set temp1 = *this;
// Set temp2 = rhs;
// for (int i = 0; i < temp1.noOfElements - 1; i++)
// {
// for (int k = i + 1; k < temp1.noOfElements; k++)
// {
// if (temp1.data[i] > temp1.data[k])
// {
// T val = temp1.data[i];
// temp1.data[i] = temp1.data[k];
// temp1.data[k] = val;
// }
// }
// }
// for (int i = 0; i < temp2.noOfElements - 1; i++)
// {
// for (int k = i + 1; k < temp2.noOfElements; k++)
// {
// if (temp2.data[i] > temp2.data[k])
// {
// T val = temp2.data[i];
// temp2.data[i] = temp2.data[k];
// temp2.data[k] = val;
// }
// }
// }
// for (int i = 0; i < temp1.noOfElements; i++)
// {
// for (int k = 0; k < temp2.noOfElements; k++)
// {
// if (temp1.data[i] == temp2.data[k])
// {
// if (temp2.noOfElements == 1)
// return true;
// else
// {
// int count = 1;
// int val = i;
// int val2 = k;
// for (int j = 1; j < temp2.noOfElements; j++)
// {
// if (temp2.data[val2 + 1] == temp1.data[val + 1])
// {
// count++; val++; val2++;
// }
// }
// if (count == temp2.capacity)
// return true;
// }
// }
// }
// }
// return false;
// }
// ~Set()
// {
// if (data)
// {
// delete[]data;
// data = NULL;
// }
// }
//};
//template <typename T>
//void Set<T>::resize(int newCapacity)
//{
// T* temp = new T[newCapacity];
// for (int i = 0; i < capacity; i++)
// temp[i] = data[i];
// capacity = newCapacity;
// delete[]data;
// data = temp;
//}
//template <typename T>
//bool Set<T>::remove(T element)
//{
// bool flag = false;
// for (int i = 0; i < noOfElements; i++)
// {
// if (data[i] == element)
// {
// data[i] = data[i + 1];
// noOfElements--;
// flag = true;
// }
// }
// return flag;
//}



#pragma once
#include <iostream>
#include <string>
#include "GenericArray.h"
using namespace std;
template <typename T>
class Set
{
	GenericArray<T> set;
	int noOfElements;
public:
	Set()
	{
		noOfElements = 0;
	}
	Set(int n, GenericArray<T>& arr) 
	{
		noOfElements = n;
		set = arr;
	}
	/*Set(const Set<T>& ref)
	{
		noOfElements = ref.noOfElements;
		set(&ref);
	}*/
	Set<T>& operator=(const Set<T>& ref)
	{
		noOfElements = ref.noOfElements;
		set = ref.set;
		return *this;
	}
	T& operator[](int i)
	{
		return set.data[i];
	}
	bool insert(T element)
	{
		for (int i = 0; i < noOfElements; i++)
		{
		 if (set[i] == element)
		  return false;
		}
		if (noOfElements >= set.getCapacity())
			set.resize(noOfElements + 100);
		set[noOfElements] = element;
		noOfElements++;
		return true;
	}
	bool remove(T element)
	{
		bool flag = false;
		for (int i = 0; i < noOfElements; i++)
		{
			if (set[i] == element)
			{
				if (i + 1 == noOfElements) noOfElements--;
				else
				{
					for (int k = i; k < noOfElements; k++)
					{
						set[k] = set[k + 1];
						noOfElements--;
						
					}
				}
				flag = true;
				break;
			}
		}
		return flag;
	}
	void print() const
	{
		for (int i = 0; i < noOfElements; i++)
		 cout << set[i] << " ";
		cout << endl;
	}
	int getCardinality() const
	{
		return noOfElements;
	}
	bool isMember(T val) const
	{
		for (int i = 0; i < noOfElements; i++)
		{
			if (set[i] == val)
				return true;
		}
		return false;
	}
	Set<T> calcUnion(const Set<T> & rhs)
	{
		int common = 0;
		for (int i = 0; i < set.getCapacity(); i++)
		{
			for (int k = 0; k < rhs.set.getCapacity(); k++)
			{
				if (set[i] == rhs.set[k])
					common++;
			}
		}
		GenericArray<char> array1(set.getCapacity() + (rhs.set.getCapacity() - common));
		Set temp(0,array1);
		for (int i = 0; i < set.getCapacity(); i++)
			temp.set[i] = set[i];
		int J = 0;
		int tempIndex = set.getCapacity();
		temp.noOfElements = set.getCapacity();
		for (int i = set.getCapacity(); i < rhs.set.getCapacity() + set.getCapacity(); i++)
		{
			bool flag = true;
			for (int k = 0; k < Intersection(rhs).set.getCapacity(); k++)
			{
				flag = true;
				if (rhs.set[J] == Intersection(rhs).set[k])
				{
					flag = false; J++; break;
				}
			}
			if (flag == true)
			{
				temp.set[tempIndex++] = rhs.set[J++]; temp.noOfElements++;
			}
		}
		return temp;
	}
	Set Intersection(const Set<T> & rhs) // returns the intersection of two given sets.
	{
		int j = 0;
		for (int i = 0; i < set.getCapacity(); i++)
		{
			for (int k = 0; k < rhs.set.getCapacity(); k++)
			{
				if (set[i] == rhs.set[k])
				{
					j++; break;
				}
			}
		}
		GenericArray<char> array1(j);
		Set temp(0, array1);
		j = 0;
		for (int i = 0; i < set.getCapacity(); i++)
		{
			for (int k = 0; k < rhs.set.getCapacity(); k++)
			{
				if (set[i] == rhs.set[k])
				{
					temp.set[j++] = set[i]; break;
				}
			}
		}
		temp.noOfElements = j + 1;
		for (int i = 0; i < temp.set.getCapacity() - 1; i++)
		{
			for (int k = i + 1; k < temp.set.getCapacity(); k++)
			{
				if (temp.set[i] == temp.set[k])
				{
					temp.set[k] = temp.set[k + 1];
					k++;  temp.noOfElements--; break;
				}
			}
		}
		return temp;
	}
	bool isSubset(const Set<T> & rhs)
	{
		Set temp1; temp1 = *this;
		Set temp2; temp2 = rhs;
		for (int i = 0; i < temp1.noOfElements - 1; i++)
		{
			for (int k = i + 1; k < temp1.noOfElements; k++)
			{
				if (temp1.set[i] > temp1.set[k])
				{
					T val = temp1.set[i];
					temp1.set[i] = temp1.set[k];
					temp1.set[k] = val;
				}
			}
		}
		for (int i = 0; i < temp2.noOfElements - 1; i++)
		{
			for (int k = i + 1; k < temp2.noOfElements; k++)
			{
				if (temp2.set[i] > temp2.set[k])
				{
					T val = temp2.set[i];
					temp2.set[i] = temp2.set[k];
					temp2.set[k] = val;
				}
			}
		}
		for (int i = 0; i < temp1.noOfElements; i++)
		{
			for (int k = 0; k < temp2.noOfElements; k++)
			{
				if (temp1.set[i] == temp2.set[k])
				{
					if (temp2.noOfElements == 1)
						return true;
					else
					{
						int count = 1;
						int val = i;
						int val2 = k;
						for (int j = 1; j < temp2.noOfElements; j++)
						{
							if (temp2.set[val2 + 1] == temp1.set[val + 1])
							{
								count++; val++; val2++;
							}
						}
						if (count == temp2.set.getCapacity())
							return true;
					}
				}
			}
		}
		return false;
	}
	~Set()
	{
		

	}
};