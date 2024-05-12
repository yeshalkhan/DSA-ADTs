#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Queue
{
	int rear; 
	int front; 
	int noOfElements;
	int capacity;
	T* data;
	void reSize(int newSize)
	{
		T* temp = new T[newSize];
		int index = front;
		for (int i = 0; i < noOfElements; i++)
		{
			temp[i] = data[index];
			index = (index + 1) % capacity;
		}
		int tempRear = noOfElements;
		this->~Queue();
		data = temp;
		capacity = newSize;
		front = 0;
		rear = tempRear;
		noOfElements = tempRear;
	}
public:
	Queue()
	{
		rear = front = noOfElements = capacity = 0;
		data = nullptr;
	}
	~Queue()
	{
		if (!data)
			return;
		delete[]data;
		data = nullptr;
		capacity = front = rear = noOfElements = 0;
	}
	Queue(const Queue<T>& ref)
	{
		if (ref.data == nullptr)
		{
			data = nullptr;
			capacity = front = rear = noOfElements = 0;
			return;
		}
		capacity = ref.capacity;
		noOfElements = ref.noOfElements;
		front = ref.front;
		rear = ref.rear;
		data = new T[ref.capacity];
		int index = ref.front;
		for (int i = 0; i < noOfElements; i++)
		{
			data[index] = ref.data[index];
			index = (index + 1) % capacity;
		}
	}
	Queue<T>& operator=(const Queue<T>& ref)
	{
		if (&ref == this)
			return *this;
		this->~Queue();
		if (ref.data == nullptr)
		{
			data = nullptr;
			capacity = front = rear = noOfElements = 0;
			return *this;
		}
		capacity = ref.capacity;
		noOfElements = ref.noOfElements;
		front = ref.front;
		rear = ref.rear;
		data = new T[ref.capacity];
		int index = ref.front;
		for (int i = 0; i < ref.noOfElements; i++)
		{
			data[index] = ref.data[index];
			index = (index + 1) % capacity;
		}
		return *this;
	}
	void enQueue(T val)
	{
		if (isFull())
			reSize(capacity == 0 ? 1 : capacity * 2);
		data[rear] = val;
		rear = (rear + 1) % capacity;
		noOfElements++;
	}
	T deQueue()
	{
		if (isEmpty())
			exit(0);
		T val = data[front];
		front = (front + 1) % capacity;
		noOfElements--;
		if (noOfElements > 0 && noOfElements == capacity / 4)
			reSize(capacity / 2);
		return val;
	}
	T getElementAtFront() const
	{
		if (isEmpty())
			exit(0);
		return data[front];
	}
	bool isEmpty() const
	{
		return noOfElements == 0;
	}
	bool isFull() const
	{
		return noOfElements == capacity;
	}
	int getNoOfElements() const
	{
		return noOfElements;
	}
	int getCapacity() const
	{
		return capacity;
	}
};

