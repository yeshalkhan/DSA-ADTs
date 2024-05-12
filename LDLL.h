#pragma once
#include <iostream>
using namespace std;
template <typename T>
struct DNode
{
	T info;
	DNode<T>* next;
	DNode<T>* prev;
	DNode()
	{
		next = nullptr;
		prev = nullptr;
	}
	DNode(T val)
	{
		info = val;
		next = nullptr;
		prev = nullptr;
	}
};
template <typename T>
class LDLL
{
	DNode<T>* head;
public:
	LDLL()
	{
		head = nullptr;
	}
	~LDLL()
	{
		while (head)
			removeAtHead();
		head = nullptr;
	}
	void insertAtHead(T val)
	{
		DNode<T>* ptr = new DNode<T>(val);
		if (!head)		//if there's no element
		{
			head = ptr;
			return;
		}
		ptr->next = head;
		head = ptr;
		ptr->next->prev = ptr;
	}
	void insertAtTail(T val)
	{
		if (!head)
		{
			head = new DNode<T>(val);
			return;
		}
		DNode<T>* temp = head;
		DNode<T>* ptr = new DNode<T>(val);
		while (temp->next)
			temp = temp->next;
		temp->next = new DNode<T>(val);
		temp->next->prev = temp;
	}
	void insertAfter(T key, T val)
	{
		if (!head)
			return;
		DNode<T>* temp = head;
		while (temp->info!=key)
		{
			if (!temp->next)
				return;
			temp = temp->next;
		}
		DNode<T>* ptr = new DNode<T>(val);
		if (!temp->next)	//if key is at tail
		{
			temp->next = ptr;
			ptr->prev = temp;
			return;
		}
		ptr->next = temp->next;
		ptr->next->prev = ptr;
		temp->next = ptr;
		ptr->prev = temp;
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
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (!temp->next)
				return;
			temp = temp->next;
		}
		DNode<T>* ptr = new DNode<T>(val);
		temp->prev->next = ptr;
		ptr->prev = temp->prev;
		ptr->next = temp;
		temp->prev = ptr;
	}
	bool search(T key)
	{
		if (!head)
			return false;
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (!temp->next)
				return false;
			temp = temp->next;
		}
		return true;
	}
	void printList()
	{
		if (!head)
			return;
		DNode<T>* temp = head;
		cout << temp->info << " ";
		while (temp->next)
		{
			temp = temp->next;
			cout << temp->info << " ";
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
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (!temp->next)
				return;
			temp = temp->next;
		}
		DNode<T>* del = temp;
		if (!temp->next)		//if key is at tail
		{
			temp->prev->next = nullptr;
			delete del;
			return;
		}
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete del;
	}
	void removeAtHead()
	{
		if (!head)
			return;
		DNode<T>* temp = head;
		if (!head->next)		//if there's only one element
		{
			head = nullptr;
			delete temp;
			return;
		}
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}
	void removeAtTail()
	{
		if (!head)
			return;
		DNode<T>* temp = head;
		if (!head->next)		//if there's only one element
		{
			head = nullptr;
			delete temp;
			return;
		}
		while (temp->next)
			temp = temp->next;
		DNode<T>* del = temp;
		temp->prev->next = nullptr;
		delete del;
	}
	void removeAfter(T key)
	{
		if (!head)
			return;
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (!temp->next)
				return;
			temp = temp->next;
		}
		if (!temp->next)		//if key is at tail
			return;
		DNode<T>* del = temp->next;
		if (!temp->next->next)		//if tail is to be removed
		{
			temp->next = nullptr;
			delete del;
			return;
		}
		temp->next = temp->next->next;
		temp->next->prev = temp;
		delete del;
	}
	void removeBefore(T key)
	{
		if (!head)
			return;
		if (head->info == key)
			return;
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (!temp->next)
				return;
			temp = temp->next;
		}
		DNode<T>* del = temp->prev;
		if (!temp->prev->prev)		//if head is to be removed
		{
			temp->prev = nullptr;
			head = temp;
			delete del;
			return;
		}
		temp->prev = temp->prev->prev;
		temp->prev->next = temp;
		delete del;
	}
	
};

