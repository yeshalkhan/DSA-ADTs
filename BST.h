#pragma once
#include <iostream>
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
class BST
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
	BTNode<T>* searchNode(T key)			//returns parent of desired node
	{
		BTNode<T>* p = root;
		while (p)
		{
			if ((p->left && p->left->info == key) || (p->right && p->right->info == key))
				return p;
			if (key >= p->info)
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
			BTNode<T>* p = root->right;
			while (p->left)
				p = p->left;
			p->left = root->left;
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
	BST()
	{
		root = nullptr;
	}
	~BST()
	{
		if (root)
		{
			deleteTree(root);
			root = nullptr;
		}
	}
	void insert(T val)
	{
		if (!root)
		{
			root = new BTNode<T>(val);
			return;
		}
		BTNode<T>* p = root;
		while (true)
		{
			if (val >= p->info)
			{
				if (!p->right)
				{
					p->right = new BTNode<T>(val);
					return;
				}
				p = p->right;
			}
			else
			{
				if (!p->left)
				{
					p->left = new BTNode<T>(val);
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
			if (key > p->info)
				p = p->right;
			else
				p = p->left;
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
		BTNode<T>* par = searchNode(key);
		if (!par)
			return;
		BTNode<T>* del = nullptr;			//par is the parent node & del is the node to be deleted
		par->left && par->left->info == key ? del = par->left : del = par->right;
		if (!del->left && !del->right)		//if node to be deleted is a leaf node
		{
			par->left && par->left->info == key ? par->left = nullptr : par->right = nullptr;
			delete del;
			return;
		}
		if (del->left && del->right)		//if node to be deleted is of degree 2 i.e., has 2 children
		{
			BTNode<T>* temp = del->right;		
			while (temp->left)
				temp = temp->left;
			temp->left = del->left;
			if (par->left && par->left->info == key)
				par->left = del->right;
			else
				par->right = del->right;
			delete del;
			return;
		}
		if (del->left)			//if node to be deleted has only left child
		{
			if (par->left && par->left->info == key)
				par->left = del->left;
			else
				par->right = del->left;
			delete del;
			return;
		}
		if (del->right)			//if node to be deleted has only right child
		{
			if (par->left && par->left->info == key)
				par->left = del->right;
			else
				par->right = del->right;
			delete del;
			return;
		}
	}
	void LVR()
	{
		LVR(root);
		cout << endl;
	}
};

