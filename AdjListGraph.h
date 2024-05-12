#pragma once
#include <iostream>
#include "GenericArray.h"
#include "Queue.h"
#include "Stack.h"
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
struct Vertex
{
	T info;
	bool visited;
	Vertex* next;
	int edgeWeight;
	Vertex()
	{
		visited = false;
		info = 0;
		next = nullptr;
		edgeWeight = 0;
	}
	Vertex(T i)
	{
		info = i;
		visited = false;
		next = nullptr;
		edgeWeight = 0;
	}
};

template <typename T>
struct Edge
{
	T src;
	T dest;
	int edgeWeight;
};

template <typename T>
class AdjListGraph
{
	GenericArray<Vertex<T>*> vertices;
	int noOfVertices;

	bool isUndirected()
	{
		for (int i = 0; i < noOfVertices; i++)
			vertices[i]->visited = false;
		Vertex<T>* temp = nullptr;
		for (int i = 0; i < noOfVertices; i++)
		{
			temp = vertices[i]->next;
			while (temp)
			{
				if (!temp->visited)
				{
					//check if there's an edge from temp to vertices[i]
					if (!isEdge(temp, vertices[i]->info))
						return false;
				}
				temp->visited = true;
				temp = temp->next;
			}
		}
		return true;
	}

	bool isEdge(Vertex<T>* temp, T ver)
	{
		int tempIndex = findVertexIndex(temp->info);
		Vertex<T>* edge = vertices[tempIndex]->next;
		while (edge)
		{
			edge->visited = true;		//using flags on edges to reduce the number of iterations
			if (edge->info == ver)
				return true;
			edge = edge->next;
		}
		return false;
	}

	void DFSHelper(T ver)
	{
		int verIndex = findVertexIndex(ver);
		vertices[verIndex]->visited = true;
		cout << vertices[verIndex]->info << " ";
		int tempIndex;
		Vertex<T>* temp = vertices[verIndex]->next;
		while (temp)
		{
			tempIndex = findVertexIndex(temp->info);
			if (!vertices[tempIndex]->visited)
				DFSHelper(vertices[tempIndex]->info);
			temp = temp->next;
		}
	}

	void BFSHelper(Vertex<T>* ver)
	{
		if (!ver)
			return;
		Queue<Vertex<T>*> q;
		q.enQueue(ver);
		Vertex<T>* temp;
		Vertex<T>* curr;
		while (!q.isEmpty())
		{
			curr = q.deQueue();
			for (int i = 0; i < noOfVertices; i++)
			{
				if (vertices[i]->info == curr->info)			//search current vertex in the array of vertices
				{
					if (!vertices[i]->visited)                  //proceed if vertex is not already visited
					{
						cout << vertices[i]->info << " ";
						vertices[i]->visited = true;
						temp = vertices[i]->next;
						while (temp)
						{
							q.enQueue(temp);
							temp = temp->next;
						}
					}
					break;                                   //break loop if current is found in array of vertices
				}
			}
		}
	}

	void deleteList(Vertex<T>* ver)
	{
		if (!ver)
			return;
		Vertex<T>* temp;
		while (ver->next)
		{
			temp = ver->next;
			ver->next = ver->next->next;
			delete temp;
		}
		temp = nullptr;
	}

	bool isVertexInsideOutMST(Vertex<T>* temp, vector<Vertex<T>*>& outMST)
	{
		if (!temp)
			return false;
		for (auto elem : outMST)
		{
			if (temp->info == elem->info)
				return true;
		}
		return false;
	}

	void deleteVertexFromOutMST(Vertex<T>* temp, vector<Vertex<T>*>& outMST)
	{
		if (!temp)
			return;
		int count = 0;
		for (auto elem : outMST)
		{
			if (elem->info == temp->info)
			{
				outMST.erase(outMST.begin() + count);
				return;
			}
			count++;
		}
	}

	void insertAllEdges(vector<Edge<T>>& edges)
	{
		Vertex<T>* temp = nullptr;
		for (int i = 0; i < noOfVertices; i++)
		{
			temp = vertices[i]->next;
			while (temp)
			{
				edges.push_back({ vertices[i]->info, temp->info, temp->edgeWeight });
				temp = temp->next;
			}
		}
	}

	int find(vector<int>& parent, int node)
	{
		if (parent[node] == -1)
			return node;
		return find(parent, parent[node]);
	}

	int findVertexIndex(T ver)
	{
		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == ver)
				return i;
		}
		return -1;	//vertex not found
	}

	bool isVertexInPath(vector<Vertex<T>*>& insidePath, T ver)
	{
		for (auto vertex : insidePath)
		{
			if (vertex->info == ver)
				return true;
		}
		return false;
	}

	void topoSortHelper(T ver, Stack<T>& stk)
	{
		int verIndex = findVertexIndex(ver);
		vertices[verIndex]->visited = true;
		int tempIndex;
		Vertex<T>* temp = vertices[verIndex]->next;
		while (temp)
		{
			tempIndex = findVertexIndex(temp->info);
			if (!vertices[tempIndex]->visited)
				topoSortHelper(vertices[tempIndex]->info, stk);
			temp = temp->next;
		}
		stk.push(ver);		//when all edges of vertex are traversed, add it to stack
	}

	void reverseGraph(AdjListGraph<T>& graph)
	{
		for (int i = 0; i < noOfVertices; i++)
			graph.addVertex(vertices[i]->info);
		Vertex<T>* temp = nullptr;
		for (int i = 0; i < noOfVertices; i++)
		{
			temp = vertices[i]->next;
			while (temp)
			{
				graph.addEdge(temp->info, vertices[i]->info, temp->edgeWeight);
				temp = temp->next;
			}
		}
	}

public:
	AdjListGraph(int n = 1) : vertices(n)
	{
		noOfVertices = 0;
	}

	~AdjListGraph()
	{
		for (int i = 0; i < noOfVertices; i++)
		{
			deleteList(vertices[i]);
			delete vertices[i];
			vertices[i] = nullptr;
		}
		noOfVertices = 0;
	}

	void addVertex(T info)
	{
		if (vertices.getCapacity() <= 0)
			return;
		int cap = vertices.getCapacity();
		if (noOfVertices >= cap)
			cap == 0 ? vertices.resize(1) : vertices.resize(cap * 2);
		vertices[noOfVertices++] = new Vertex<T>(info);
	}

	void addEdge(T src, T dest, int weight = 0)
	{
		if (vertices.getCapacity() <= 0)
			return;
		if (findVertexIndex(dest) == -1)
		{
			cout << "Destination Vertex " << dest << " not found" << endl;	 //dest must exist in array of vertices to make an edge towards it
			return;
		}
		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == src)
			{
				Vertex<T>* temp = vertices[i]->next;
				vertices[i]->next = new Vertex<T>(dest);
				vertices[i]->next->edgeWeight = weight;
				vertices[i]->next->next = temp;

				return;
			}
		}
		cout << "Source Vertex " << src << " not found" << endl;	//if array of vertices has been traversed but src is not found
	}

	void deleteEdge(T src, T dest)
	{
		if (vertices.getCapacity() <= 0)
			return;
		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == src)
			{
				Vertex<T>* temp = vertices[i];
				while (temp->next)
				{
					if (temp->next->info == dest)
					{
						Vertex<T>* del = temp->next;
						temp->next = temp->next->next;
						delete del;
						del = nullptr;
						return;				//return if the desired destination vertex is found
					}
					temp = temp->next;
				}
				return;			//return if all of source vertex's edges have been checked but destnation vertex is not found
			}
		}
	}

	void printGraph()
	{
		if (vertices.getCapacity() <= 0)
			return;
		Vertex<T>* temp = nullptr;
		for (int i = 0; i < noOfVertices; i++)
		{
			if (!vertices[i]->next)
				cout << "Vertex " << vertices[i]->info << " has no edges" << endl;
			else
			{
				temp = vertices[i];
				cout << "Vertex " << temp->info << " has edges with ";
				while (temp->next)
				{
					temp = temp->next;
					cout << temp->info << "  Weight : " << temp->edgeWeight << ", ";
				}
				cout << endl;
			}
		}
	}

	void DFS(T ver)
	{
		if (vertices.getCapacity() <= 0)
			return;
		int srcIndex = findVertexIndex(ver);
		if (srcIndex == -1)
		{
			cout << "Source vertex not found" << endl;
			return;
		}

		for (int i = 0; i < noOfVertices; i++)
			vertices[i]->visited = false;
		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == ver)
			{
				DFSHelper(vertices[i]->info);
				break;
			}
		}
		for (int i = 0; i < noOfVertices; i++)		//for remaining vertices
		{
			if (!vertices[i]->visited)
				DFSHelper(vertices[i]->info);
		}
		cout << endl;
	}

	void BFS(T ver)
	{
		if (vertices.getCapacity() <= 0)
			return;
		int srcIndex = findVertexIndex(ver);
		if (srcIndex == -1)
		{
			cout << "Source vertex not found" << endl;
			return;
		}

		for (int i = 0; i < noOfVertices; i++)
			vertices[i]->visited = false;
		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == ver)
			{
				BFSHelper(vertices[i]);
				break;
			}
		}
		for (int i = 0; i < noOfVertices; i++)		//for remaining vertices
		{
			if (!vertices[i]->visited)
				BFSHelper(vertices[i]);
		}
		cout << endl;
	}

	void PrimsMST(T src)		
	{
		if (vertices.getCapacity() <= 0)
			return;
		if (!isUndirected())
		{
			cout << "Prim's algorithm doesn't work on directed graphs" <<
				endl << "Use this function on undirected graphs" << endl;
			return;
		}

		vector<Vertex<T>*> inMST;			//vertices incuded in MST
		vector<Vertex<T>*> outMST;			//vertices not yet included in MST
		vector<Edge<T>> output;				//final MST
		int minWeight, cost = 0;
		T source;
		Vertex<T>* temp = nullptr;
		Vertex<T>* minVertex = nullptr;

		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == src)
				inMST.push_back(vertices[i]);
			else
				outMST.push_back(vertices[i]);
		}

		int count = noOfVertices - 1;
		while (count > 0)			//keep finding minimum edge weight till all vertices are included in MST & outMST is empty
		{
			minWeight = INT_MAX;

			for (auto elem : inMST)	//finding the edge with the minimum weight out of available edges
			{
				temp = elem->next;		//traversing adjacenct vertices of current vertex i.e., edges of current vertex inMST[i]
				while (temp)
				{
					if (isVertexInsideOutMST(temp, outMST) && temp->edgeWeight < minWeight)	//to find minimum edge, include only those
																						//vertices which are in the array outMST
					{
						minWeight = temp->edgeWeight;
						minVertex = temp;
						source = elem->info;
					}
					temp = temp->next;
				}
			}

			cost += minWeight;						//adding minimum edge weight to total cost
			inMST.push_back(vertices[findVertexIndex(minVertex->info)]);   //we have to add actual vertex from array of vertices in 
																		   //inMST, so that it can point to is edges. minVertex is 
																		   //just a copy; it doesn't point to next edges

			deleteVertexFromOutMST(minVertex, outMST);
			output.push_back({ source,minVertex->info,minVertex->edgeWeight });
			count--;
		}

		//printing resultant MST
		for (auto elem : output)
			cout << elem.src << elem.dest << ",";
		cout << endl << "Cost : " << cost << endl;
	}

	void KruskalsMST()
	{
		if (vertices.getCapacity() <= 0)
			return;
		if (!isUndirected())
		{
			cout << "Kruskal's algorithm doesn't work on directed graphs" <<
				endl << "Use this function on undirected graphs" << endl;
			return;
		}

		vector<Edge<T>> edges;					//vector containing all edges 
		vector<Edge<T>> outputMST;				//final MST
		vector<int> parent(noOfVertices, -1);	//a vector initialized with -1 on each index

		insertAllEdges(edges);
		//sorting edges according to their weights
		sort(edges.begin(), edges.end(), [](const Edge<T>& a, const Edge<T>& b) { return a.edgeWeight < b.edgeWeight; });

		int srcRoot, destRoot, cost = 0, i = 0;

		for (auto edge : edges)
		{
			// Find the representatives (root nodes) of the components containing src and dest
			srcRoot = find(parent, findVertexIndex(edge.src));
			destRoot = find(parent, findVertexIndex(edge.dest));

			// If adding this edge doesn't form a cycle, include it in the MST
			if (srcRoot != destRoot) {
				outputMST.push_back(edge);
				cost += edge.edgeWeight;

				// Union the components (merge trees)
				parent[srcRoot] = destRoot;
			}
		}

		//printing output MST
		for (auto elem : outputMST)
			cout << elem.src << elem.dest << ",";
		cout << endl << "Cost: " << cost << endl;
	}

	void dijkstra(T src)
	{
		if (vertices.getCapacity() <= 0)
			return;
		vector<int> dist(noOfVertices, INT_MAX);	//a vector containing distance of the vertex at each index from the source
													//initially all distances are infinity 
		vector<T> pred(noOfVertices, 0);			//a vector containing predecessor of each vertex 
													//initially all predecessors are null
		vector<Vertex<T>*> insidePath;				//a vector containing vertices included in the shortest path

		Vertex<T>* temp = nullptr;
		T minVertex;
		int tempIndex, currIndex, min;

		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == src)					//making source vertex's distance 0
			{
				dist[i] = 0;
				insidePath.push_back(vertices[i]);
				break;
			}
		}

		int count = 0;
		while (count != noOfVertices)		//keep finding minimum edge till all vertices are included in insidePath
		{
			min = INT_MAX;
			for (auto curr : insidePath)
			{
				temp = curr->next;
				currIndex = findVertexIndex(curr->info);		//finding index of current vertex in array of vertices

				while (temp)
				{
					if (temp->edgeWeight < 0)
					{
						cout << "Dijkstra can't work on graphs with negative edge weights" << endl;
						return;
					}

					if (!isVertexInPath(insidePath, temp->info))	    //if vertex is not already included in shortest path
					{
						tempIndex = findVertexIndex(temp->info);		//finding index of temp in array of vertices

						if (dist[currIndex] + temp->edgeWeight < dist[tempIndex])
						{
							dist[tempIndex] = dist[currIndex] + temp->edgeWeight;	//update distance of temp in dist vertex
							pred[tempIndex] = vertices[currIndex]->info;			//update predecessor of temp in pred vertex
						}

						if (dist[tempIndex] < min)		//finding vertex with minimum edge weight from all available outgoing edges
						{
							min = dist[tempIndex];
							minVertex = vertices[tempIndex]->info;
						}
					}

					temp = temp->next;
				}
			}

			insidePath.push_back(vertices[findVertexIndex(minVertex)]);	//adding the vertex with minimum weight in shortest path
			count++;
		}

		for (int i = 0; i < noOfVertices; i++)
			cout << "Cost to reach " << src << " from " << vertices[i]->info << " is " << dist[i] << endl;

		cout << endl;
		for (int i = 0; i < noOfVertices; i++)
		{
			cout << "Predecessor of " << vertices[i]->info << " is ";
			pred[i] == 0 ? cout << "none " : cout << pred[i];		//special case for for source vertex
			cout << endl;
		}
	}

	void topoSort(T ver)
	{
		if (vertices.getCapacity() <= 0)
			return;
		int srcIndex = findVertexIndex(ver);
		if (srcIndex == -1)
		{
			cout << "Source vertex not found" << endl;
			return;
		}

		if (isUndirected())
		{
			cout << "Topological sort doesn't work on undirected graphs\nUse this function on directed graphs" << endl;
			return;
		}

		Stack<T> stk;
		for (int i = 0; i < noOfVertices; i++)
			vertices[i]->visited = false;
		for (int i = 0; i < noOfVertices; i++)
		{
			if (vertices[i]->info == ver)
			{
				topoSortHelper(vertices[i]->info, stk);
				break;
			}
		}
		for (int i = 0; i < noOfVertices; i++)		//for remaining vertices
		{
			if (!vertices[i]->visited)
				topoSortHelper(vertices[i]->info, stk);
		}
		while (!stk.isEmpty())
			cout << stk.pop() << ",";
		cout << endl;
	}

	void connectedComponents()
	{
		if (vertices.getCapacity() <= 0)
			return;
		if (!isUndirected())
		{
			cout << "Directed graphs don't have connected components, they have strongly connected components" <<
				endl << "Use this function on undirected graphs" << endl;
			return;
		}

		for (int i = 0; i < noOfVertices; i++)
			vertices[i]->visited = false;
		int compCount = 1;
		for (int i = 0; i < noOfVertices; i++)
		{
			if (!vertices[i]->visited)
			{
				cout << "Component # " << compCount++ << " : ";
				DFSHelper(vertices[i]->info);
				cout << endl;		//go on next line to indicate start of another component
			}
		}
	}

	void stronglyConnectedComponents()
	{
		if (vertices.getCapacity() <= 0)
			return;
		if (isUndirected())
		{
			cout << "Undirected graphs don't have strongly connected components\nUse this function on directed graphs" << endl;
			return;
		}

		Stack<T> stk;
		T elem;
		for (int i = 0; i < noOfVertices; i++)
			vertices[i]->visited = false;
		for (int i = 0; i < noOfVertices; i++)
		{
			if (!vertices[i]->visited)
				topoSortHelper(vertices[i]->info, stk);		//we have to do the same thing we did in topo sort i.e., 
															//push vertex in stack when all of its edges are visited
		}

		AdjListGraph<T> revGraph(noOfVertices);
		int compCount = 1;
		reverseGraph(revGraph);
		while (!stk.isEmpty())	//pop element from stack & run DFS on it in the reversed graph
								//when all edges of a vertex have been visited in DFS, that completes a connected component
		{
			elem = stk.pop();
			for (int i = 0; i < noOfVertices; i++)
			{
				if (revGraph.vertices[i]->info == elem)
				{
					if (!revGraph.vertices[i]->visited)
					{
						cout << "Component # " << compCount++ << " : ";
						revGraph.DFSHelper(revGraph.vertices[i]->info);
						cout << endl;		//go on next line to indicate start of another component
					}
					break;		//break the loop when element is found
				}
			}
		}
	}

	void BellmanFordMST(T src)
	{
		if (vertices.getCapacity() <= 0)
			return;
		int srcIndex = findVertexIndex(src);
		if (srcIndex == -1)
		{
			cout << "Source vertex not found" << endl;
			return;
		}

		vector<int> dist(noOfVertices, INT_MAX);	 //vector containing min. distance to reach each vertex initialzed with infinity
		vector<T> pred(noOfVertices, 0);			 //vector containing predecessors of all vertices initialzed with null
		dist[srcIndex] = 0;				             //placing 0 at first vertex's distance
		Vertex<T>* temp = nullptr;
		int tempIndex;
		int count = noOfVertices - 1;

		while (count > 0)		//run the algorithm n-1 times where n is noOfVertices
		{
			for (int i = 0; i < noOfVertices; i++)
			{
				temp = vertices[i]->next;
				while (temp)
				{
					tempIndex = findVertexIndex(temp->info);
					if (dist[i] != INT_MAX && dist[i] + temp->edgeWeight < dist[tempIndex])
					{
						dist[tempIndex] = dist[i] + temp->edgeWeight;
						pred[tempIndex] = vertices[i]->info;
					}
					temp = temp->next;
				}
			}
			count--;
		}

		//run algorithm one more time to detect negative weight cycle
		for (int i = 0; i < noOfVertices; i++)
		{
			temp = vertices[i]->next;
			while (temp)
			{
				tempIndex = findVertexIndex(temp->info);
				if (dist[i] + temp->edgeWeight < dist[tempIndex])
				{
					cout << "Graph contains negative weight cycle" << endl;
					return;
				}
				temp = temp->next;
			}
		}

		//print result if cycle doesn't exist
		for (int i = 0; i < noOfVertices; i++)
			cout << "Cost to reach " << src << " from " << vertices[i]->info << " is " << dist[i] << endl;

		cout << endl;
		for (int i = 0; i < noOfVertices; i++)
		{
			cout << "Predecessor of " << vertices[i]->info << " is ";
			pred[i] == 0 ? cout << "none " : cout << pred[i];		//special case for for source vertex
			cout << endl;
		}
	}


};









