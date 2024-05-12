#pragma once
#include <iostream>
#include "Stack.h"
using namespace std;
template <typename T>
struct BTNode
{
	T info;
	BTNode<T>* left;
	BTNode<T>* right;
	int height;
	BTNode()
	{
		left = right = nullptr;
		height = 1;
	}
	BTNode(T in)
	{
		info = in;
		left = right = nullptr;
		height = 1;
	}
};
template <typename T>
class AVL
{
	BTNode<T>* root;
	void LVR(BTNode<T>* p)
	{
		if (!p)
			return;
		if (p->left)
			LVR(p->left);
		cout << p->info << " ";
		if (p->right)
			LVR(p->right);
	}
	bool updateHeight(BTNode<T>* p)
	{
		if (!p)
			return true;
		int l = 0, r = 0;
		if (p->left)
			l = p->left->height;
		if (p->right)
			r = p->right->height;
		l > r ? p->height = l + 1 : p->height = r + 1;
		if (l - r > 1 || l - r < -1)		//checking the balance factor
			return false;
		return true;
	}
	void rotate(BTNode<T>* p, Stack<BTNode<T>*>& ancPath)
	{
		int leftHeight, rightHeight;
		p->left ? leftHeight = p->left->height : leftHeight = 0;
		p->right ? rightHeight = p->right->height : rightHeight = 0;
		if (leftHeight - rightHeight > 0)		//go to left
		{
			p->left && p->left->left ? leftHeight = p->left->left->height : leftHeight = 0;
			p->left && p->left->right ? rightHeight = p->left->right->height : rightHeight = 0;
			if (leftHeight - rightHeight > 0)		//go to left left
				LL(p, ancPath);
			else		//go to left right
				LR(p, ancPath);
		}
		else		//go to right
		{
			p->right && p->right->left ? leftHeight = p->right->left->height : leftHeight = 0;
			p->right && p->right->right ? rightHeight = p->right->right->height : rightHeight = 0;
			if (leftHeight - rightHeight > 0)		//go to right left
				RL(p, ancPath);
			else		//go to right right
				RR(p, ancPath);
		}
	}
	void LL(BTNode<T>* P, Stack<BTNode<T>*>& ancPath)
	{
		BTNode<T>* LP = P->left;
		BTNode<T>* RLP = P->left->right;
		LP->right = P;
		P->left = RLP;
		updateHeight(P);
		updateHeight(LP);
		if (ancPath.isEmpty())
			root = LP;
		else
		{
			BTNode<T>* parent = ancPath.stackTop();
			parent->left && parent->left == P ? parent->left = LP : parent->right = LP;
		}
	}
	void LR(BTNode<T>* P, Stack<BTNode<T>*>& ancPath)
	{
		BTNode<T>* LP = P->left;
		BTNode<T>* RLP = LP->right;
		BTNode<T>* RRLP = RLP->right;
		BTNode<T>* LRLP = RLP->left;
		RLP->left = LP;
		RLP->right = P;
		P->left = RRLP;
		LP->right = LRLP;
		updateHeight(LP);
		updateHeight(P);
		updateHeight(RLP);
		if (ancPath.isEmpty())
			root = RLP;
		else
		{
			BTNode<T>* parent = ancPath.stackTop();
			parent->left && parent->left == P ? parent->left = RLP : parent->right = RLP;
		}
	}
	void RL(BTNode<T>* P, Stack<BTNode<T>*>& ancPath)
	{
		BTNode<T>* RP = P->right;
		BTNode<T>* LRP = RP->left;
		BTNode<T>* LLRP = LRP->left;
		BTNode<T>* RLRP = LRP->right;
		LRP->right = RP;
		LRP->left = P;
		RP->left = RLRP;
		P->right = LLRP;
		updateHeight(RP);
		updateHeight(P);
		updateHeight(LRP);
		if (ancPath.isEmpty())
			root = LRP;
		else
		{
			BTNode<T>* parent = ancPath.stackTop();
			parent->left && parent->left == P ? parent->left = LRP : parent->right = LRP;
		}
	}
	void RR(BTNode<T>* P, Stack<BTNode<T>*>& ancPath)
	{
		BTNode<T>* RP = P->right;
		BTNode<T>* LRP = P->right->left;
		RP->left = P;
		P->right = LRP;
		updateHeight(P);
		updateHeight(RP);
		if (ancPath.isEmpty())
			root = RP;
		else
		{
			BTNode<T>* parent = ancPath.stackTop();
			parent->left && parent->left == P ? parent->left = RP : parent->right = RP;
		}
	}
	BTNode<T>* searchNode(T key, Stack<BTNode<T>*>& ancPath)			//returns parent of desired node
	{
		BTNode<T>* p = root;
		while (p)
		{
			ancPath.push(p);
			if ((p->left && p->left->info == key) || (p->right && p->right->info == key))
				return p;
			if (key > p->info)
				p = p->right;
			else
				p = p->left;
		}
		return nullptr;
	}
	void deleteRoot()
	{
		if (!root->right && !root->left)		//if root node has no child
		{
			delete root;
			root = nullptr;
			return;
		}
		BTNode<T>* del = root;
		if (root->left && root->right)			//if root node has two children
		{
			Stack<BTNode<T>*> tempStack;
			BTNode<T>* p = root->right;
			while (p->left)
			{
				tempStack.push(p);
				p = p->left;
			}
			tempStack.push(p);
			p->left = root->left;			//attach root's left node to the smallest node on its right side

			while (!tempStack.isEmpty())	//update height of the node to which we attached root's left child &
											//also update height of all its ancestors & rearrange tree if needed
			{
				p = tempStack.pop();
				if (!updateHeight(p))
					rotate(p, tempStack);
			}
			if (root == del)			//if root hasn't changed in rotation
				root = root->right;
			delete del;
			return;
		}
		if (root->right)			//if root node has only right child
		{
			root = root->right;
			delete del;
			return;
		}
		else						//if root node has only left child
		{
			root = root->left;
			delete del;
			return;
		}
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
public:
	AVL()
	{
		root = nullptr;
	}
	~AVL()
	{
		deleteTree(root);
		root = nullptr;
	}
	void insert(T val)
	{
		if (!root)
		{
			root = new BTNode<T>(val);
			return;
		}
		BTNode<T>* p = root;
		Stack<BTNode<T>*> ancPath;
		while (true)
		{
			ancPath.push(p);
			if (val == p->info)
				return;
			else if (val > p->info)
			{
				if (!p->right)
				{
					p->right = new BTNode<T>(val);
					while (!ancPath.isEmpty())			//updating height of ancestor nodes & rearranging tree if needed
					{
						p = ancPath.pop();
						if (!updateHeight(p))
							rotate(p, ancPath);
					}
					return;
				}
				p = p->right;
			}
			else
			{
				if (!p->left)
				{
					p->left = new BTNode<T>(val);
					while (!ancPath.isEmpty())			//updating height of ancestor nodes & rearranging tree if needed
					{
						p = ancPath.pop();
						if (!updateHeight(p))
							rotate(p, ancPath);
					}
					return;
				}
				p = p->left;
			}
		}
	}
	bool search(T key)
	{
		if (!root)
			return false;
		BTNode<T>* p = root;
		while (p)
		{
			if (p->info == key)
				return true;
			else if (p->info > key)
				p = p->left;
			else
				p = p->right;
		}
		return false;
	}
	void remove(T key)
	{
		if (!root)
			return;
		if (root->info == key)
		{
			deleteRoot();
			return;
		}
		Stack<BTNode<T>*> ancPath;
		BTNode<T>* parent = searchNode(key, ancPath);
		if (!parent)
			return;
		BTNode<T>* p = nullptr;
		BTNode<T>* del = nullptr;			//parent is the parent node & del is the node to be deleted
		parent->left&& parent->left->info == key ? del = parent->left : del = parent->right;
		if (!del->left && !del->right)		//if node to be deleted is a leaf node
		{
			parent->left&& parent->left->info == key ? parent->left = nullptr : parent->right = nullptr;
			delete del;
			while (!ancPath.isEmpty())			//updating height of ancestors & rearranging tree if needed
			{
				p = ancPath.pop();
				if(!updateHeight(p))
					rotate(p,ancPath);
			}
			return;
		}
		if (del->left && del->right)		//if node to be deleted is of degree 2 i.e., has 2 children
		{
			Stack<BTNode<T>*> tempStack;
			BTNode<T>* temp = del->right;
			while (temp->left)
			{
				tempStack.push(temp);
				temp = temp->left;
			}
			tempStack.push(temp);
			temp->left = del->left;			//attach del's left node to the smallest node on its right side

			while (!tempStack.isEmpty())	//update height of the node to which we attached del's left child &
											//also update height of all its ancestors & rearrange tree if needed
			{
				p = tempStack.pop();
				if (!updateHeight(p))
					rotate(p, tempStack);
			}
			if (parent->left && parent->left->info == key)
				parent->left = del->right;
			else
				parent->right = del->right;
			delete del;
			while (!ancPath.isEmpty())			//updating height of ancestors & rearranging tree if needed
			{
				p = ancPath.pop();
				if (!updateHeight(p))
					rotate(p, ancPath);
			}
			return;
		}
		if (del->left)			//if node to be deleted has only left child
		{
			if (parent->left && parent->left->info == key)
				parent->left = del->left;
			else
				parent->right = del->left;
			delete del;
			while (!ancPath.isEmpty())			//updating height of ancestors & rearranging tree if needed
			{
				p = ancPath.pop();
				if (!updateHeight(p))
					rotate(p, ancPath);
			}
			return;
		}
		if (del->right)			//if node to be deleted has only right child
		{
			if (parent->left && parent->left->info == key)
				parent->left = del->right;
			else
				parent->right = del->right;
			delete del;
			while (!ancPath.isEmpty())			//updating height of ancestors & rearranging tree if needed
			{
				p = ancPath.pop();
				if (!updateHeight(p))
					rotate(p, ancPath);
			}
			return;
		}
	}
	T test()
	{
		return root->info;
	}
	void LVR()
	{
		LVR(root);
		cout << endl;
	}
};

