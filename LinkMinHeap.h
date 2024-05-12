#pragma once
#include <iostream>
#include "Stack.h"
#include "Queue.h"
using namespace std;
template <typename T>
struct BTNode
{
	T info;
	BTNode<T>* left;
	BTNode<T>* right;
	BTNode()
	{
		left = right = nullptr;
	}
	BTNode(T in)
	{
		info = in;
		left = right = nullptr;
	}
};
template <typename T>
class LinkMinHeap
{
	BTNode<T>* root;
	int noOfNodes;
	void getBinary(int num, Stack<bool>& stk)
	{
		while (num >= 1)
		{
			stk.push(num % 2);
			num = num / 2;
		}
		stk.pop();               //removing the first bit
	}
	void deleteTree(BTNode<T>* p)
	{
		if (!p)
			return;
		if (p->left)
			deleteTree(p->left);
		if (p->right)
			deleteTree(p->right);
		delete p;
	}
	void upHeap(BTNode<T>* cur, Stack<BTNode<T>*>& ancPath)	  //cur is the node we just inserted, it can be par->right or par->left 
	{
		T temp;
		BTNode<T>* par = nullptr;
		while (!ancPath.isEmpty())
		{
			par = ancPath.pop();
			if (cur->info < par->info)	   
			{
				temp = cur->info;		 //swapping
				cur->info = par->info;
				par->info = temp;

				cur = par;
			}
			else	//if data arrangement is correct at one node, it'll be correct on all nodes above so so need to check
				return;
		}
	}
	void downHeap(BTNode<T>* cur)			
	{
		BTNode<T>* minChild;
		T temp;
		while (cur->left)				//When there'll be no left child, no right child either
		{
			if (cur->right)		//right exits so left must also exist
				minChild = cur->right->info < cur->left->info ? cur->right : cur->left;
			else						//only left
				minChild = cur->left;

			if (cur->info > minChild->info)
			{
				temp = cur->info;		 //swapping
				cur->info = minChild->info;
				minChild->info = temp;

				cur = minChild;
			}
			else		//if data arrangement is correct at one node, it'll be correct on all nodes above so so need to check
				return;
		}
	}
public:
	LinkMinHeap()
	{
		noOfNodes = 0;
		root = nullptr;
	}
	~LinkMinHeap()
	{
		deleteTree(root);
		root = nullptr;
	}
	void insert(T val)
	{
		if (!root)
		{
			root = new BTNode<T>(val);
			noOfNodes++;
			return;
		}
		noOfNodes++;
		BTNode<T>* par = root;
		Stack<bool> binary;
		Stack<BTNode<T>*> ancPath;
		getBinary(noOfNodes, binary);				//get binary of the index at which we're inserting rn
		bool ind;
		while (binary.getNumberOfElements() > 1)	//we'll ignore the last bit because we need address of parent not of actual node
		{
			ind = binary.pop();
			ancPath.push(par);
			if (ind == 0)
				par = par->left;
			else if (ind == 1)
				par = par->right;
		}
		ancPath.push(par);
		if (!par->left)			//insertion at left node
		{
			par->left = new BTNode<T>(val);
			upHeap(par->left, ancPath);		//rearranging tree acc to heap rules i.e, sending min value to top
		}
		else				//insertion at right node
		{
			par->right = new BTNode<T>(val);
			upHeap(par->right, ancPath);		//rearranging tree acc to heap rules i.e, sending min value to top
		}
	}
	T getMin()
	{
		if (!root)
			exit(0);
		return root->info;
	}
	T deleteMin()
	{
		if (!root)
			exit(0);
		T min = root->info;
		if (noOfNodes == 1)
		{
			delete root;
			root = nullptr;
			noOfNodes--;
			return min;
		}
		BTNode<T>* par = root;
		Stack<bool> binary;
		getBinary(noOfNodes, binary);
		bool ind;
		while (binary.getNumberOfElements() > 1)			//to reach the parent of the last inserted node
		{
			ind = binary.pop();
			if (ind == 0)
				par = par->left;
			else if (ind == 1)
				par = par->right;
		}
		if (par->right)
		{
			root->info = par->right->info;
			delete par->right;
			par->right = nullptr;
		}
		else
		{
			root->info = par->left->info;
			delete par->left;
			par->left = nullptr;
		}
		noOfNodes--;
		downHeap(root);
		return min;
	}
	void BFS()
	{
		if (!root)
			return;
		Queue<BTNode<T>*> q;
		BTNode<T>* temp;
		q.enQueue(root);
		while (!q.isEmpty())
		{
			temp = q.deQueue();
			cout << temp->info << " ";
			if (temp->left)
				q.enQueue(temp->left);
			if (temp->right)
				q.enQueue(temp->right);
		}
		cout << endl;
	}
	
};

