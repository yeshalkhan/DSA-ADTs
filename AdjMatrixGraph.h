#pragma once
#include <iostream>
#include "Queue.h"
using namespace std;
class AdjMatrixGraph
{
	bool* visited;
	int** data;
	int noOfVertices;
	void DFSHelper(int i)
	{
		cout << i << " ";
		visited[i] = true;
		for (int j = 0; j < noOfVertices; j++)
		{
			if (data[i][j] == 1 && !visited[j])
				DFSHelper(j);
		}
	}
	void BFSHelper(int ver)
	{
		Queue<int> q;
		q.enQueue(ver);
		int i, j;
		while (!q.isEmpty())
		{
			i = q.deQueue();
			if (!visited[i])
			{
				cout << i << " ";
				visited[i] = true;
				for (j = 0; j < noOfVertices; j++)
				{
					if (data[i][j] == 1 && !visited[j])
						q.enQueue(j);
				}
			}
		}
	}
public:
	AdjMatrixGraph(int n = 0)
	{
		if (n <= 0)
		{
			data = nullptr;
			noOfVertices = 0;
			visited = nullptr;
			return;
		}
		noOfVertices = n;
		visited = new bool[n];
		data = new int* [n];
		for (int i = 0; i < n; i++)
		{
			visited[i] = false;
			data[i] = new int[n];
		}
		for (int i = 0; i < noOfVertices; i++)
			for (int j = 0; j < noOfVertices; j++)
				data[i][j] = 0;
	}
	~AdjMatrixGraph()
	{
		if (data)
		{
			for (int i = 0; i < noOfVertices; i++)
				delete[]data[i];
			delete[]data;
			data = nullptr;
			delete[]visited;
			visited = nullptr;
			noOfVertices = 0;
		}
	}
	void addEdge(int row, int col)
	{
		if (!data || row < 0 || row >= noOfVertices || col < 0 || col >= noOfVertices)
			return;
		data[row][col] = 1;
	}
	void removeEdge(int row, int col)
	{
		if (!data || row < 0 || row >= noOfVertices || col < 0 || col >= noOfVertices)
			return;
		data[row][col] = 0;
	}
	void printGraph()
	{
		if (!data)
			return;
		cout << "    ";
		for (int j = 0; j < noOfVertices; j++)		//display column number
			cout << j << " ";
		cout << endl << "   " ;
		for (int j = 1; j < noOfVertices; j++)		//display column number
			cout << " - ";
		cout << endl;
		for (int i = 0; i < noOfVertices; i++)
		{
			cout << i << " | ";                     //display row nunmber
			for (int j = 0; j < noOfVertices; j++)
				cout << data[i][j] << " ";
			cout << endl;
		}
	}
	void DFS(int ver)
	{
		if (!data)
			return;
		if (ver < 0 || ver >= noOfVertices)
		{
			cout << "Vertex not found" << endl;
			return;
		}
		for (int i = 0; i < noOfVertices; i++)
			visited[i] = false;
		DFSHelper(ver);
		for (int i = 0; i < noOfVertices; i++)			//for disconnected vertices
		{
			if (!visited[i])
				DFSHelper(i);
		}
		cout << endl;
	}
	void BFS(int ver)
	{
		if (!data)
			return;
		if (ver < 0 || ver >= noOfVertices)
		{
			cout << "Vertex not found" << endl;
			return;
		}
		for (int i = 0; i < noOfVertices; i++)
			visited[i] = false;
		BFSHelper(ver);
		for (int i = 0; i < noOfVertices; i++)			//for disconnected vertices
		{
			if (!visited[i])
				BFSHelper(i);
		}
		cout << endl;
	}
};



