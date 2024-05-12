#pragma once
#include <iostream>
#include <string>
using namespace std;

template <class T>
class GenericArray
{
	T* data;
	int capacity;
	bool isValidIndex(int index) const
	{
		return index >= 0 && index < capacity;
	}
public:
	GenericArray()
	{
		capacity = 0;
		data = nullptr;
	}
	GenericArray(int size) : GenericArray()
	{
		if (size <= 0)
			return;
		capacity = size;
		data = new T[capacity];
	}
	GenericArray(initializer_list<T> l) : GenericArray()
	{
		capacity = l.size();
		if (capacity <= 0)
		{
			data = nullptr;
			return;
		}
		data = new T[capacity];
		int i = 0;
		for (auto val : l)
			data[i++] = val;
	}
	~GenericArray()
	{
		if (data)
		{
			delete[]data;
			data = nullptr;
		}
		capacity = 0;
	}
	void resize(int newCapacity)
	{
		if (newCapacity <= 0)
		{
			this->~GenericArray();
			return;
		}
		T* ptr = new T[newCapacity];
		if (capacity > 0)
		{
			int size = newCapacity < capacity ? newCapacity : capacity;
			for (int i = 0; i < size; i++)
				ptr[i] = data[i];
		}
		this->~GenericArray();
		capacity = newCapacity;
		data = ptr;
	}
	T& operator[](int i)
	{
		if (isValidIndex(i))
			return data[i];
		exit(0);
	}
	T& operator[](int i) const
	{
		if (isValidIndex(i))
			return data[i];
		exit(0);
	}
	GenericArray<T>& operator=(const GenericArray<T> & ref)
	{
		if (this == &ref)
			return *this;
		this->~GenericArray();
		if (ref.data == nullptr)
		{
			data = nullptr;
			capacity = 0;
			return *this;
		}
		data = new T[ref.capacity];
		capacity = ref.capacity;
		for (int i = 0; i < capacity; i++)
			data[i] = ref.data[i];
		return *this;
	}
	GenericArray(const GenericArray<T> & ref)
	{
		if (ref.data == nullptr)
		{
			data = nullptr;
			capacity = 0;
			return;
		}
		capacity = ref.capacity;
		data = new T[capacity];
		for (int i = 0; i < capacity; i++)
			data[i] = ref.data[i];
	}
	int getCapacity() const
	{
		return capacity;
	}
};
