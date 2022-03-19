#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<cstdlib>
#define NULL_VALUE -99999
#define INF 99999
#define white 1
#define red 2
using namespace std;

class NodeDistancePair
{
public:
    int nodeValue;
    int nodeDistance;
};

class Node
{
public:
    int nodeValue;
    int nodeWeight;
};

class Edge
{
public:
    int firstNode;
    int secondNode;
    int weight;
};

class ArrayList
{
private:
    Node *a;
    int length;
    int maxSize;
public:
    ArrayList()
    {
        a = new Node[2];
        length = 0;
        maxSize = 2;
    }

    int searchItem(int nodeValue)
    {
        for(int i=0; i<length; i++)
        {
            if(a[i].nodeValue == nodeValue)
                return i;
        }
        return NULL_VALUE;
    }

    void insertItem(int value, int weight)
    {
        if(length == maxSize)
        {
            Node *temp;
            maxSize = 2*maxSize;
            temp = new Node[maxSize];
            for(int i=0; i<length; i++)
            {
                temp[i] = a[i];
            }
            temp[length].nodeValue = value;
            temp[length].nodeWeight = weight;
            delete []a;
            a = temp;
            length++;
        }
        else
        {
            a[length].nodeValue = value;
            a[length].nodeWeight = weight;
            length++;
        }

    }

    void removeItem(int value)
    {
        int idx = searchItem(value);
        if(idx == NULL_VALUE)
            return;

        removeItemAt(idx);
    }

    void removeItemAt(int idx)
    {
        if(idx<0 || idx>=length)
            return;
        a[idx] = a[--length];
    }
    Node getItem(int idx)
    {
        //if(idx<0 || idx >=length) return ;
        return a[idx];
    }

    int getLength()
    {
        return length;
    }

    bool empty()
    {
        return (length == 0);
    }
    void printList()
    {
        for(int i=0; i<length; i++)
        {
            cout << "(" << a[i].nodeValue << "," << a[i].nodeWeight << ") ";
        }
        cout <<endl;
    }

    ~ArrayList()
    {
        if(a)
            delete[]a;
        a = 0;
    }

};


class pQueue
{
    NodeDistancePair *a;
    int maxSize;
    int tail;
    int length;
public:
    pQueue()
    {
        a = new NodeDistancePair[2];
        maxSize = 2;
        tail = 1;
        length=0;
    }

    bool empty()
    {
        if(length==0)
            return true;
        else
            return false;
    }

    int leftIndex(int i)
    {
        return 2*i;
    }
    int rightIndex(int i)
    {
        return 2*i+1;
    }

    int parentIndex(int i)
    {
        return i/2;
    }

    void heapify(int i)
    {
        int left = leftIndex(i);
        int right = rightIndex(i);
        int minimum;
        if(left <= length && a[left].nodeDistance<a[i].nodeDistance)
        {
            minimum = left;
        }
        else
            minimum = i;

        if(right<=length && a[right].nodeDistance<a[minimum].nodeDistance)
        {
            minimum = right;
        }

        if(minimum != i)
        {
            NodeDistancePair temp = a[i];
            a[i] = a[minimum];
            a[minimum] = temp;
            heapify(minimum);
        }

    }

    void buildHeap()
    {
        int l = length;
        l = l/2;
        for(int i=l; i>0; i--)
        {
            heapify(i);
        }
    }

    void upwardTransition(int i)
    {
        int parent = parentIndex(i);
        if(parent < 1)
            return;
        NodeDistancePair temp;
        if(a[parent].nodeDistance>a[i].nodeDistance)
        {
            temp = a[parent];
            a[parent] = a[i];
            a[i] = temp;
            upwardTransition(parent);
        }
    }

    void insert(int nodeValue,int distance)
    {
        if(tail == maxSize)
        {
            NodeDistancePair *temp;
            maxSize = 2*maxSize;
            temp = new NodeDistancePair[maxSize];
            for(int i=0; i<tail; i++)
            {
                temp[i] = a[i];
            }
            delete []a;
            a = temp;
        }

        a[tail].nodeValue = nodeValue;
        a[tail].nodeDistance = distance;
        tail++;
        length++;
        upwardTransition(tail-1);
    }
    NodeDistancePair findMin()
    {
        return a[1];
    }

    NodeDistancePair extractMin()
    {
        NodeDistancePair temp = a[1];
        if(tail>1 && length>0)
        {
            tail--;
            length--;
            a[1] = a[tail];
            heapify(1);
        }
        return temp;
    }

    void increaseKey(int node, int newKey)
    {
        int idx;
        for(int i=1; i<tail; i++)
        {
            if(a[i].nodeValue == node)
            {
                idx = i;
                break;
            }
        }
        a[idx].nodeDistance = newKey;
        heapify(idx);
    }

    void decreaseKey(int node, int newKey)
    {
        int idx;
        for(int i=1; i<tail; i++)
        {
            if(a[i].nodeValue == node)
            {
                idx = i;
                break;
            }
        }
        a[idx].nodeDistance = newKey;
        upwardTransition(idx);
    }

    void print()
    {
        for(int i=1; i<tail; i++)
        {
            cout << a[i].nodeValue << " ";
        }
        cout << endl;
    }

    bool isInQueue(int value){
        for(int i=0;i<tail;i++){
            if(value == a[i].nodeValue) return true;
        }
        return false;
    }

    ~pQueue()
    {
        if(a)
            delete []a;
        a = 0;
    }
};

class Set
{
private:
    int *parent;
    int *r;
    int length;
public:
    Set(int s)
    {
        parent = new int[s];
        r = new int[s];
        length = s;
    }

    void makeSet(int item)
    {
        parent[item] = item;
        r[item] = 1;
    }
    int findSet(int value)
    {
        while(value != parent[value])
            value = parent[value];
        return value;
    }
    void Union(int u, int v)
    {
        int first = findSet(u);
        int second = findSet(v);
        if(first == second)
            return;

        if(r[first] < r[second])
        {
            parent[first] = second;
        }
        else
        {
            parent[second] = first;
        }
        if(r[first] == r[second])
            r[first]++;
    }

    void printSet(int s)
    {
        int p = findSet(s);
        for(int i=0; i<length; i++)
        {
            if(findSet(i)==p)
                cout << i << " ";
        }
        cout << endl;
    }
    ~Set()
    {
        if(parent)
            delete []parent;
        if(r)
            delete []r;
    }
};


class Graph
{
private:
    int nVertices, nEdges,kruskalEdgesIdx=0;
    ArrayList *adjList;
    int *key;
    int *parent;
    int *color;
    Edge *edges;
    Edge *kruskalEdges;

    ofstream file;
public:
    Graph(int vertices,int edges)
    {
        this->nVertices = vertices;
        this->nEdges = edges;
        adjList = new ArrayList[nVertices];

        kruskalEdges = new Edge[edges];
        file.open("output.txt");
    }

    void addEdge(int u, int v, int weight)
    {
        if(u<0 || u>nVertices || v<0 || v>nVertices || u==v)
            return;
        adjList[u].insertItem(v,weight);
        adjList[v].insertItem(u,weight);

        kruskalEdges[kruskalEdgesIdx].firstNode = u;
        kruskalEdges[kruskalEdgesIdx].secondNode = v;
        kruskalEdges[kruskalEdgesIdx].weight = weight;
        kruskalEdgesIdx++;
    }

    void removeEdge(int u,int v)
    {
        if(u<0 || u>nVertices || v<0 || v>nVertices)
            return;
        adjList[u].removeItem(v);
        adjList[v].removeItem(u);
    }

    bool isEdge(int u, int v)
    {
        if(adjList[u].searchItem(v) == NULL_VALUE)
            return false;
        else
            return true;
    }

    int getWeight(int u,int v)
    {
        //if(u<0 || u>nVertices || v<0 || v>nVertices) return NULL_VALUE;
        int idx = adjList[u].searchItem(v);
        if(idx != NULL_VALUE)
            return adjList[u].getItem(idx).nodeWeight;
        else
            return NULL_VALUE;
    }

    void primsAlgo(int s)
    {
        if(key)
            delete []key;
        if(parent)
            delete []parent;
        if(color)
            delete []color;
        if(edges)
            delete []edges;

        key = new int[nVertices];
        parent = new int[nVertices];
        color = new int[nVertices];
        edges = new Edge[nVertices-1];

        pQueue q;
        for(int i=0; i<nVertices; i++)
        {
            if(i == s)
                q.insert(s,0);
            else
                q.insert(i,INF);
            color[i] = white;
            key[i] = INF;
        }

        //q.print();

        key[s] = 0;
        parent[s] = -1;
        while(!q.empty()){
            int u = q.extractMin().nodeValue;
            int l = adjList[u].getLength();
            for(int i=0;i<l;i++){
                int v = adjList[u].getItem(i).nodeValue;
                if(color[v] == white && key[v] > adjList[u].getItem(i).nodeWeight){
                    parent[v] = u;
                    key[v] = adjList[u].getItem(i).nodeWeight;
                    q.decreaseKey(v,key[v]);
                }
            }
            color[u] = red;
        }

        int treeWeight = 0;
        for(int i=0;i<nVertices;i++) treeWeight += key[i];

        file << "prims algorithm:" << endl;
        file << "root node:" << s << endl;

        for(int i=0;i<nVertices;i++){
            if(parent[i] == -1) continue;
            file << i << " " << parent[i] << endl;
        }
    }


    int pivotIndex(Edge a[],int s,int e)
    {
        int pivot = a[e].weight;
        int pIndex = s;
        for(int i=s; i<e; i++)
        {
            if(a[i].weight < pivot)
            {
                Edge temp = a[pIndex];
                a[pIndex] = a[i];
                a[i] = temp;
                pIndex++;
            }
        }

        Edge temp = a[pIndex];
        a[pIndex] = a[e];
        a[e] = temp;

        return pIndex;
    }

    void quickSort(Edge a[],int s,int e)
    {
        if(s<e)
        {
            int pivot = pivotIndex(a,s,e);
            quickSort(a,s,pivot-1);
            quickSort(a,pivot+1,e);
        }
    }

    void kruskalAlgo()
    {
        if(edges)
            delete []edges;
        edges = new Edge[nVertices-1];

        Set s(nVertices);
        for(int i=0; i<nVertices; i++)
            s.makeSet(i);

        quickSort(kruskalEdges,0,nEdges-1);

        int idx = 0;
        for(int i=0; i<nEdges; i++)
        {
            int first = s.findSet(kruskalEdges[i].firstNode);
            int second = s.findSet(kruskalEdges[i].secondNode);
            if(first != second)
            {
                edges[idx].firstNode = kruskalEdges[i].firstNode;
                edges[idx].secondNode = kruskalEdges[i].secondNode;
                edges[idx].weight = kruskalEdges[i].weight;
                idx++;
                s.Union(kruskalEdges[i].firstNode, kruskalEdges[i].secondNode);
            }
        }

        int distance=0;
        for(int i=0; i<nVertices-1; i++)
        {
            distance+=edges[i].weight;
        }

        file << distance << endl;

        file << "Kruskal's algorithm:" << endl;


        for(int i=0; i<nVertices-1; i++)
        {
            file << edges[i].firstNode << " " << edges[i].secondNode << endl;
        }

    }

    void printArr()
    {
        cout << "start" << endl;
        for(int i=0; i<nEdges; i++)
        {
            cout << kruskalEdges[i].firstNode << " " << kruskalEdges[i].secondNode << " " << kruskalEdges[i].weight << endl;
        }
        cout <<endl;
    }

    void printGraph()
    {
        for(int i=0; i<nVertices; i++)
        {
            cout << i << ":";
            for(int j=0; j<adjList[i].getLength(); j++)
            {
                cout << adjList[i].getItem(j).nodeValue << " ";
            }
            cout << endl;
        }
    }


    ~Graph()
    {
        if(adjList)
            delete []adjList;
        if(parent)
            delete []parent;
        if(key)
            delete []key;
        if(color)
            delete[]color;
        if(edges)
            delete []edges;
        if(kruskalEdges)
            delete []kruskalEdges;
        file.close();
    }
};

int main()
{
    ifstream file;
    file.open("input.txt");
    int vertices,edges;
    file >> vertices >> edges;
    Graph *g = new Graph(vertices,edges);

    int u,v,w;
    for(int i=0; i<edges; i++)
    {
        file >> u >> v >> w;
        g->addEdge(u,v,w);
    }
    g->kruskalAlgo();
    g->primsAlgo(rand()%vertices);
    file.close();
    delete g;
    return 0;
}

