#pragma once
#include <iostream>
#include <math.h>
using namespace std;
template <typename T>
class ArrayBinaryTree
{
	int arraySize;
	int maxHeight;
	T* nodes;
	bool* nodesStatus;
	int searchNode(T par)
	{
		return searchNode(0, par);
	}
	int searchNode(int i, T par)			//prefix search
	{
		int status = -1;
		if (i >= arraySize || nodesStatus[i] == false)
			return status;
		if (nodes[i] == par)
			status = i;
		if (status == -1 && (i * 2 + 1) < arraySize && nodesStatus[i * 2 + 1])
			status = searchNode(i * 2 + 1, par);
		if (status == -1 && (i * 2 + 2) < arraySize && nodesStatus[i * 2 + 2])
			status = searchNode(i * 2 + 2, par);
		return status;
	}
	void printAncestorsHelper(int i)
	{
		if (i < 0 || nodesStatus[i] == false)
			return;
		if (i == 0)
		{
			cout << nodes[0] << " ";
			return;
		}
		cout << nodes[i] << " ";
		if ((i - 1) / 2 >= 0)
			printAncestorsHelper((i - 1) / 2);
	}
	void removeHelper(int i)
	{
		if (i >= arraySize || nodesStatus[i] == false)
			return;
		if (i * 2 + 1 < arraySize && nodesStatus[i * 2 + 1])
			removeHelper(i * 2 + 1);
		if (i * 2 + 2 < arraySize && nodesStatus[i * 2 + 2])
			removeHelper(i * 2 + 2);
		nodesStatus[i] = false;
	}
	void VLR(int i)
	{
		if (i >= arraySize || nodesStatus[i] == false)
			return;
		cout << nodes[i] << " ";
		if (i * 2 + 1 < arraySize && nodesStatus[i * 2 + 1])
			VLR(i * 2 + 1);
		if (i * 2 + 2 < arraySize && nodesStatus[i * 2 + 2])
			VLR(i * 2 + 2);
	}
	int getHeightHelper(int i)
	{
		if (i >= arraySize || nodesStatus[i] == false)
			return 0;
		int l = 0, r = 0;
		if (i * 2 + 1 < arraySize && nodesStatus[i * 2 + 1])
			l = getHeightHelper(i * 2 + 1);
		if (i * 2 + 2 < arraySize && nodesStatus[i * 2 + 2])
			r = getHeightHelper(i * 2 + 2);
		if (l > r)
			return l + 1;
		else
			return r + 1;
	}
public:
	ArrayBinaryTree(int h)
	{
		if (h <= 0)
		{
			arraySize = maxHeight = 0;
			nodes = nullptr;
			nodesStatus = nullptr;
			return;
		}
		arraySize = pow(2, h) - 1;
		maxHeight = h;
		nodes = new T[arraySize];
		nodesStatus = new bool[arraySize];
		for (int i = 0; i < arraySize; i++)
			nodesStatus[i] = false;
	}
	~ArrayBinaryTree()
	{
		if (nodes)
		{
			delete[]nodes;
			nodes = nullptr;
		}
		if (nodesStatus)
		{
			delete[]nodesStatus;
			nodesStatus = nullptr;
		}
		arraySize = 0;
		maxHeight = 0;
	}
	void setRoot(T ch)
	{
		if (arraySize)
		{
			nodes[0] = ch;
			nodesStatus[0] = true;
		}
	}
	void setLeftChild(T par, T ch)
	{
		int ind = searchNode(par);
		if (ind == -1)
			return;
		if (ind * 2 + 1 < arraySize)
		{
			nodes[ind * 2 + 1] = ch;
			nodesStatus[ind * 2 + 1] = true;
		}
	}
	void setRightChild(T par, T ch)
	{
		int ind = searchNode(par);
		if (ind == -1)
			return;
		if (ind * 2 + 2 < arraySize)
		{
			nodes[ind * 2 + 2] = ch;
			nodesStatus[ind * 2 + 2] = true;
		}
	}
	T getParent(T ch)
	{
		int ind = searchNode(ch);
		if (ind == -1 || ind == 0)		//there's no parent of root node
			exit(0);
		return nodes[(ind - 1) / 2];
	}
	int getHeight()
	{
		return getHeightHelper(0);
	}
	void printDescendants(T ch)
	{
		int ind = searchNode(ch);
		if (ind == -1)
			return;
		if (ind * 2 + 1 < arraySize && nodesStatus[ind * 2 + 1])
			VLR(ind * 2 + 1);
		if (ind * 2 + 2 < arraySize && nodesStatus[ind * 2 + 2])
			VLR(ind * 2 + 2);
		cout << endl;
	}
	void printAncestors(T ch)
	{
		int ind = searchNode(ch);
		if (ind == -1 || ind == 0)
			return;
		printAncestorsHelper((ind - 1) / 2);
		cout << endl;
	}
	void remove(T ch)
	{
		int ind = searchNode(ch);
		if (ind == -1)
			return;
		else if (ind == 0)
		{
			~ArrayBinaryTree();
			return;
		}
		removeHelper(ind);
	}
	void VLR()
	{
		VLR(0);
		cout << endl;
	}
};

