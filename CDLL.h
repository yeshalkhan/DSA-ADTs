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
class CDLL
{
	DNode<T>* head;
public:
	CDLL()
	{
		head = nullptr;
	}
	~CDLL()
	{
		while (head)
			removeAtHead();
		head = nullptr;
	}
	void insertAtHead(T val)
	{
		DNode<T>* ptr = new DNode<T>(val);
		if (!head)
		{
			head = ptr;
			ptr->next = ptr;
			ptr->prev = ptr;
			return;
		}
		ptr->next = head;
		ptr->prev = head->prev;
		head->prev->next = ptr;
		head->prev = ptr;
		head = ptr;
	}
	void insertAtTail(T val)
	{
		if (!head)
		{
			insertAtHead(val);
			return;
		}
		DNode<T>* ptr = new DNode<T>(val);
		head->prev->next = ptr;
		ptr->prev = head->prev;
		ptr->next = head;
		head->prev = ptr;
	}
	void insertAfter(T key, T val)
	{
		if (!head)
			return;
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == head)
				return;
			temp = temp->next;
		}
		DNode<T>* ptr = new DNode<T>(val);
		ptr->next = temp->next;
		ptr->next->prev = ptr;
		temp->next = ptr;
		ptr->prev = temp;
	}
	void insertBefore(T key, T val)
	{
		if (!head)
			return;
		if (key == head->info)		//if value is to be inserted before head
		{
			insertAtHead(val);
			return;
		}
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == head)
				return;
			temp = temp->next;
		}
		DNode<T>* ptr = new DNode<T>(val);
		ptr->prev = temp->prev;
		ptr->prev->next = ptr;
		temp->prev = ptr;
		ptr->next = temp;
	}
	bool search(T key)
	{
		if (!head)
			return false;
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == head)
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
		do
		{
			cout << temp->info << " ";
			temp = temp->next;
		} while (temp != head);
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
			if (temp->next == head)
				return;
			temp = temp->next;
		}
		DNode<T>* del = temp;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete del;
	}
	void removeAtHead()
	{
		if (!head)
			return;
		if (head->next == head)		//if there's only one element
		{
			delete head;
			head = nullptr;
			return;
		}
		DNode<T>* del = head;
		head->prev->next = head->next;
		head->next->prev = head->prev;
		head = head->next;
		delete del;
	}
	void removeAtTail()
	{
		if (!head)
			return;
		if (head->next == head)		//if there's only one element
		{
			removeAtHead();
			return;
		}
		DNode<T>* del = head->prev;
		head->prev = head->prev->prev;
		head->prev->next = head;
		delete del;
	}
	void removeAfter(T key)
	{
		if (!head)
			return;
		if (head->prev!=head && head->prev->info == key)		//if head is to be removed
		{
			removeAtHead();
			return;
		}
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == head)
				return;
			temp = temp->next;
		}
		DNode<T>* del = temp->next;
		temp->next = temp->next->next;
		temp->next->prev = temp;
		delete del;
	}
	void removeBefore(T key)
	{
		if (!head)
			return;
		if (head->prev != head && head->next->info == key)		//if head is to be removed
		{
			removeAtHead();
			return;
		}
		if (head->prev != head && head->info == key)		//if tail is to be removed
		{
			removeAtTail();
			return;
		}
		DNode<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == head)
				return;
			temp = temp->next;
		}
		DNode<T>* del = temp->prev;
		temp->prev = temp->prev->prev;
		temp->prev->next = temp;
		delete del;
	}
};

