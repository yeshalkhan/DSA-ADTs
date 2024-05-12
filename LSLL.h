#pragma once
#include <iostream>
using namespace std;
template <typename T>
struct Node
{
	T info;
	Node<T>* next;
	Node()
	{
		next = nullptr;
	}
	Node(T val)
	{
		info = val;
		next = nullptr;
	}
};
template <typename T>
class LSLL
{
	Node<T>* head;
public:
	LSLL()
	{
		head = nullptr;
	}
	~LSLL()
	{
		while (head)
			removeAtHead();
		head = nullptr;
	}
	void insertAtHead(T val)
	{
		Node<T>* ptr = new Node<T>(val);
		ptr->next = head;       //if you write ptr->next = head->next, it will go to 2nd element because next 
								//of head is actually next of 1st element & head is address of 1st element
		head = ptr;
	}
	void insertAtTail(T val)
	{
		if (!head)
		{
			head = new Node<T>(val);
			return;
		}
		Node<T>* temp = head;
		while (temp->next != nullptr)
			temp = temp->next;
		temp->next = new Node<T>(val);
	}
	void insertAfter(T key, T val)
	{
		if (!head)
			return;
		Node<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == nullptr)        //key not found
				return;
			temp = temp->next;
		}
		Node<T>* ptr = new Node<T>(val);
		ptr->next = temp->next;
		temp->next = ptr;
	}
	void insertBefore(T key, T val)
	{
		if (!head)
			return;
		if (head->info == key)
		{
			insertAtHead(val);
			return;
		}
		Node<T>* previous = head;
		while (previous->next != nullptr && previous->next->info != key)
		{
			previous = previous->next;
		}
		if (previous->next == nullptr)       //key not found
			return;
		Node<T>* ptr = new Node<T>(val);
		ptr->next = previous->next;
		previous->next = ptr;
	}
	bool search(T key)
	{
		if (!head)
			return false;
		Node<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == nullptr)
				return false;
			temp = temp->next;
		}
		return true;
	}
	void printList()
	{
		if (!head)
			return;
		Node<T>* temp = head;
		cout << temp->info << " ";
		while (temp->next != nullptr)
		{
			cout << temp->next->info << " ";
			temp = temp->next;
		}
		cout << endl;
	}
	void remove(T key)
	{
		if (!head)
			return;
		if (head->info == key)
		{
			removeAtHead();
			return;
		}
		Node<T>* previous = head;
		while (previous->next != nullptr && previous->next->info != key)
		{
			previous = previous->next;
		}
		if (previous->next == nullptr)			//key not found
			return;
		Node<T>* temp = previous->next;
		previous->next = previous->next->next;
		delete temp;
	}
	void removeAtHead()
	{
		if (!head)
			return;
		Node<T>* temp = head;
		head = head->next;
		delete temp;		//deallocate memory
	}
	void removeAtTail()
	{
		if (!head)
			return;
		if (head->next == nullptr)		//if there's only 1 element
		{
			removeAtHead();
			return;
		}
		Node<T>* previous = head;
		while (previous->next->next != nullptr)
			previous = previous->next;
		Node<T>* temp = previous->next;
		previous->next = nullptr;
		delete temp;
	}
	void removeAfter(T key)
	{
		if (!head)
			return;
		Node<T>* previous = head;
		while (previous->info != key)
		{
			if (previous->next == nullptr)			//key not found
				return;
			previous = previous->next;
		}
		if (previous->next == nullptr)			//if last element is the key
			return;
		Node<T>* temp = previous->next;
		previous->next = previous->next->next;
		delete temp;
	}
	void removeBefore(T key)
	{
		if (!head)
			return;
		if (head->info == key)			//if 1st element is the key
			return;
		if (head->next->info == key)       //if 2nd element is the key
		{
			removeAtHead();
			return;
		}
		Node<T>* previous = head;      //previous is 2 places behind our required element
		while (previous->next->next != nullptr && previous->next->next->info != key)
		{
			previous = previous->next;
		}
		if (previous->next->next == nullptr && previous->next->next->info != key)			//key not found
			return;
		Node<T>* temp = previous->next;
		previous->next = previous->next->next;
		delete temp;
	}
};



