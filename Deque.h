#pragma once
#include <iostream>
using namespace std;
template <class T>
class Deque
{
	int tail;
	int head;
	int capacity;
	int noOfElements;
	T* data;
	void reSize(int newSize)
	{
		T* temp = new T[newSize];
		int index = head;
		for (int i = 0; i < noOfElements; i++)
		{
			temp[i] = data[index];
			index = (index + 1) % capacity;
		}
		int tempTail = noOfElements;
		int tempHead = 0;
		this->~Deque();
		data = temp;
		capacity = newSize;
		tail = tempTail;
		head = tempHead;
		noOfElements = tempTail;
	}
public:
	Deque()
	{
		tail = head = capacity = noOfElements = 0;
		data = nullptr;
	}
	~Deque()
	{
		if (!data)
			return;
		delete[]data;
		data = nullptr;
		tail = head = capacity = noOfElements = 0;
	}
	Deque(const Deque<T>& ref)
	{
		if (ref.data == nullptr)
		{
			data = nullptr;
			tail = head = capacity = noOfElements = 0;
			return;
		}
		data = new T[ref.capacity];
		capacity = ref.capacity;
		noOfElements = ref.noOfElements;
		tail = ref.tail;
		head = ref.head;
		int index = head;
		for (int i = 0; i < noOfElements; i++)
		{
			data[i] = ref.data[index];
			index = (index + 1) % capacity;
		}
	}
	Deque<T>& operator=(const Deque<T>& ref)
	{
		if (&ref == this)
			return *this;
		this->~Deque();
		if (ref.data == nullptr)
		{
			this->data = nullptr;
			tail = head = capacity = noOfElements = 0;
			return *this;
		}
		this->data = new T[ref.capacity];
		capacity = ref.capacity;
		noOfElements = ref.noOfElements;
		tail = ref.tail;
		head = ref.head;
		int index = head;
		for (int i = 0; i < noOfElements; i++)
		{
			this->data[i] = ref.data[index];
			index = (index + 1) % capacity;
		}
		return *this;
	}
	void insertAtTail(T val)       //same as enQueue
	{
		if (isFull())
			reSize(capacity == 0 ? 1 : capacity * 2);
		data[tail] = val;
		tail = (tail + 1) % capacity;			//to bring tail in the range of 0 -> capacity-1
		noOfElements++;
	}
	T deleteAtHead()       //same as deQueue
	{
		if (isEmpty())
			exit(0);
		T temp = data[head];
		head = (head + 1) % capacity;			//to bring front in the range of 0 -> capacity-1
		noOfElements--;
		if (noOfElements > 0 && noOfElements == capacity / 4)
			reSize(capacity / 2);
		return temp;
	}
	T deleteAtTail()		//gives pop() behavior
	{
		if (isEmpty())
			exit(0);
		tail = (tail - 1 + capacity) % capacity;			//to bring tail in the range of capacity-1 -> 0
		T temp = data[tail];
		noOfElements--;
		if (noOfElements > 0 && noOfElements == capacity / 4)
			reSize(capacity / 2);
		return temp;
	}
	void insertAtHead(T val)
	{
		if (isFull())
			reSize(capacity == 0 ? 1 : capacity * 2);
		head = (head - 1 + capacity) % capacity;
		data[head] = val;
		noOfElements++;
	}
	int getNoOfElements()
	{
		return noOfElements;
	}
	int getCapacity()
	{
		return capacity;
	}
	bool isFull()
	{
		return noOfElements == capacity;
	}
	bool isEmpty()
	{
		return noOfElements == 0;
	}
};

