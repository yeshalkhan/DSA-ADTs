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
class CSLL
{
	Node<T>* head;
public:
	CSLL()
	{
		head = nullptr;
	}
	void insertAtHead(T val)
	{
		Node<T>* ptr = new Node<T>(val);
		if (!head)
		{
			head = ptr;
			head->next = head;
			return;
		}
		Node<T>* tail = head;
		while (tail->next != head)
		{
			tail = tail->next;
		} 
		tail->next = ptr;
		ptr->next = head;
		head = ptr;
	}
	void insertAtTail(T val)
	{
		if (!head)
		{
			insertAtHead(val);
			return;
		}
		Node<T>* ptr = new Node<T>(val);
		Node<T>* tail = head;
		while (tail->next != head)
		{
			tail = tail->next;
		}
		ptr->next = tail->next;
		tail->next = ptr;
	}
	void insertAfter(T key, T val)
	{
		if (!head)
			return;
		Node<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == head)
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
		while (previous->next->info != key)
		{
			if (previous->next == head)
				return;
			previous = previous->next;
		}
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
		Node<T>* temp = head;
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
		Node<T>* previous = head;
		while (previous->next->info != key)
		{
			if (previous->next == head)
				return;
			previous = previous->next;
		}
		Node<T>* del = previous->next;
		previous->next = previous->next->next;
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
		Node<T>* tail = head;
		while (tail->next != head)
		{
			tail = tail->next;
		}
		Node<T>* del = head;
		tail->next = head->next;
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
		Node<T>* previous = head;
		while (previous->next->next != head)
		{
			previous = previous->next;
		}
		Node<T>* del = previous->next;
		previous->next = head;
		delete del;
	}
	void removeAfter(T key)
	{
		if (!head)
			return;
		Node<T>* temp = head;
		while (temp->info != key)
		{
			if (temp->next == head)
				break;
			temp = temp->next;
		}
		if (temp->next == head && temp->info != key)
			return;
		if (temp->next == head && temp->info == key)		//if key is at tail
		{
			removeAtHead();
			return;
		}
		Node<T>* del = temp->next;
		temp->next = temp->next->next;
		delete del;
	}
	void removeBefore(T key)
	{
		if (!head)
			return;
		if (head->next != head && head->info == key)			//if key is at head
		{
			removeAtTail();
			return;
		}
		if (head->next != head && head->next->info == key)		//if 2nd element is the key
		{
			removeAtHead();
			return;
		}
		Node<T>* previous = head;		//previous is 2 places behind actual key here
		while (previous->next->next->info != key)
		{
			if (previous->next->next == head)
				return;
			previous = previous->next;
		}
		Node<T>* del = previous->next;
		previous->next = previous->next->next;
		delete del;
	}
};

