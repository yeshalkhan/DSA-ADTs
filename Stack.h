#pragma once
#include <iostream>
using namespace std;
template <typename T>
class Stack
{
	T* data;
	int top;
	int capacity;
	void reSize(int);
public:
	Stack();
	Stack(const Stack<T>&);
	Stack<T>& operator=(const Stack<T>&);
	~Stack();
	void push(T);
	T pop();
	T stackTop();
	bool isFull();
	bool isEmpty();
	int getCapacity();
	int getNumberOfElements();
};

template <typename T>
Stack<T>::Stack()
{
	capacity = top = 0;
	data = nullptr;
}
template <typename T>
Stack<T>::~Stack()
{
	if (!data)
		return;
	capacity = top = 0;
	delete[]data;
	data = nullptr;
}
template <typename T>
Stack<T>::Stack(const Stack<T>& ref)
{
	if (ref.data == nullptr)
	{
		data = nullptr;
		capacity = top = 0;
		return;
	}
	top = ref.top;
	capacity = ref.capacity;
	data = new T[capacity];
	for (int i = 0; i < ref.top; i++)
		data[i] = ref.data[i];
}
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& ref)
{
	if (this == &ref)
	{
		return *this;
	}
	this->~Stack();
	if (ref.data == nullptr)
	{
		data = nullptr;
		top = capacity = 0;
		return *this;
	}
	top = ref.top;
	capacity = ref.capacity;
	data = new T[capacity];
	for (int i = 0; i < ref.top; i++)
		data[i] = ref.data[i];
	return *this;
}
template <typename T>
void Stack<T>::reSize(int newSize)
{
	T* temp = new T[newSize];
	for (int i = 0; i < top; i++)
		temp[i] = data[i];
	int tempTop = top;
	this->~Stack();
	top = tempTop;
	capacity = newSize;
	data = temp;
}
template <typename T>
void Stack<T>::push(T val)
{
	if (isFull())
		reSize(capacity == 0 ? 1 : capacity * 2);
	data[top++] = val;
}
template <typename T>
T Stack<T>::pop()
{
	if (isEmpty())
		exit(0);
	if (top > 0 && top == capacity / 4)
		reSize(capacity / 2);
	return data[--top];
}
template <typename T>
T Stack<T>::stackTop()
{
	if (isEmpty())
		exit(0);
	return data[top - 1];
}
template <typename T>
bool Stack<T>::isEmpty()
{
	return top == 0;
}
template <typename T>
bool Stack<T>::isFull()
{
	return top == capacity;
}
template <typename T>
int Stack<T>::getCapacity()
{
	return capacity;
}
template <typename T>
int Stack<T>::getNumberOfElements()
{
	return top;
}