#pragma once
#include <iostream>
#include <math.h>
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
class LinkBinaryTree
{
	BTNode<T>* root;
	BTNode<T>* findNode(BTNode<T>* p, T key)
	{
		if (!p)
			return nullptr;
		BTNode<T>* status = nullptr;
		if (p->info == key)
			status = p;
		if (!status && p->left)
			status = findNode(p->left, key);
		if (!status && p->right)
			status = findNode(p->right, key);
		return status;
	}
	BTNode<T>* getParent(BTNode<T>* p, T ch)
	{
		if (!p)
			return nullptr;
		BTNode<T>* status = nullptr;
		if (p->left && p->left->info == ch || p->right && p->right->info == ch)
			status = p;
		if (!status && p->left)
			status = getParent(p->left, ch);
		if (!status && p->right)
			status = getParent(p->right, ch);
		return status;
	}
	int getHeight(BTNode<T>* p)
	{
		if (!p)
			return 0;
		int l = 0, r = 0;
		if (p->left)
			l = getHeight(p->left);
		if (p->right)
			r = getHeight(p->right);
		if (l > r)
			return l + 1;
		else
			return r + 1;
	}
	void VLR(BTNode<T>* p)
	{
		if (!p)
			return;
		cout << p->info << " ";
		if (p->left)
			VLR(p->left);
		if (p->right)
			VLR(p->right);
	}
	void remove(BTNode<T>* p)
	{
		if (!p)
			return;
		if (p->left)
			remove(p->left);
		if (p->right)
			remove(p->right);
		delete p;
	}
public:
	LinkBinaryTree()
	{
		root = nullptr;
	}
	~LinkBinaryTree()
	{
		remove(root);
		root = nullptr;
	}
	void setRoot(T ch)
	{
		if (!root)
			root = new BTNode<T>(ch);
		else
			root->info = ch;
	}
	void setLeftChild(T par, T ch)
	{
		if (!root)
			return;
		BTNode<T>* p = findNode(root, par);
		if (!p)
			return;
		if (!p->left)
			p->left = new BTNode<T>(ch);
		else
			p->left->info = ch;
	}
	void setRightChild(T par, T ch)
	{
		if (!root)
			return;
		BTNode<T>* p = findNode(root, par);
		if (!p)
			return;
		if (!p->right)
			p->right = new BTNode<T>(ch);
		else
			p->right->info = ch;
	}
	T getParent(T ch)
	{
		if (!root || root->info == ch)
			exit(0);
		BTNode<T>* p = getParent(root, ch);
		if (!p)
			exit(0);
		return p->info;
	}
	int getHeight()
	{
		return getHeight(root);
	}
	void printDescendants(T ch)
	{
		BTNode<T>* p = findNode(root, ch);
		if (!p)
			return;
		if (p->left)
			VLR(p->left);
		if (p->right)
			VLR(p->right);
		cout << endl;
	}
	void printAncestors(T ch)
	{
		if (!root || root->info == ch)
			return;
		BTNode<T>* p = new BTNode<T>(ch);
		while (p)
		{
			p = getParent(root, p->info);
			if (p)
				cout << p->info << " ";
		}
		cout << endl;
	}
	void remove(T key)
	{
		if (root->info == key)
		{
			remove(root);
			root = nullptr;
			return;
		}
		BTNode<T>* p = getParent(root, key);
		if (!p)
			return;
		if (p->left && p->left->info == key)
		{
			remove(p->left);
			p->left = nullptr;
		}
		else
		{
			remove(p->right);
			p->right = nullptr;
		}
	}
	void VLR()
	{
		VLR(root);
		cout << endl;
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

