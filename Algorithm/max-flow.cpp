#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<cstdlib>
#define NULL_VALUE -99999
#define INF 99999
#define white 0
#define grey 1
#define black 2
#define red 5
#define green 6

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item);
    int dequeue();
    bool empty();
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ;
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ;
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ;
        }
        rear = 0 ;
        front = length ;
        delete[] data ;
        data = tempData ;
    }

    data[front] = item ;
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data;
    data = 0;
}

class Node
{
public:
    int nodeValue;
    int edgeCapacity;
    int edgeFlow;
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

    //void insertItem(int value, int capacity, int flow = 0, bool residualEdge = false)
    void insertItem(int value, int capacity, int flow = 0)
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
            temp[length].edgeCapacity = capacity;
            temp[length].edgeFlow = flow;
            delete []a;
            a = temp;
            length++;
        }
        else
        {
            a[length].nodeValue = value;
            a[length].edgeCapacity = capacity;
            a[length].edgeFlow = flow;
            length++;
        }

    }
    Node getItem(int idx)
    {
        //if(idx<0 || idx >=length) return ;
        return a[idx];
    }

    void changeCapacity(int idx, int newCapacity)
    {
        a[idx].edgeCapacity = newCapacity;
    }

    void changeFlow(int idx, int newFlow)
    {
        a[idx].edgeFlow = newFlow;
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
            cout << "(" << a[i].nodeValue << "," << a[i].edgeCapacity << "," << a[i].edgeFlow << ") ";
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


class Graph
{
private:
    int nVertices, nEdges;
    ArrayList *adjList;
    ArrayList *residualGraph;
    ofstream file;

    int *color;
    int *distance;
    int *parent;

public:
    Graph(int vertices,int edges)
    {

            this->nVertices = vertices;
            this->nEdges = edges;
            adjList = new ArrayList[nVertices];
            residualGraph = new ArrayList[nVertices];

            color = new int[nVertices];
            distance = new int[nVertices];
            parent = new int[nVertices];


        //file.open("output.txt");
    }

    void addEdge(int u, int v, int capacity, bool bipartite = false)
    {

            if(u<0 || u>=nVertices || v<0 || v>=nVertices)
                return;

            adjList[u].insertItem(v, capacity);
            int idx = residualGraph[u].searchItem(v);
            if(idx == NULL_VALUE)
            {
                residualGraph[u].insertItem(v,capacity);
                residualGraph[v].insertItem(u,0);
            }
            else
            {
                residualGraph[u].changeCapacity(idx, capacity);
            }


    }

    bool isEdge(int u, int v)
    {
        if(adjList[u].searchItem(v) == NULL_VALUE)
            return false;
        else
            return true;
    }


    bool augmentedPathExists(int source,int sink)
    {
        bool pathExists = false;
        for(int i=0; i<nVertices; i++)
        {
            color[i] = white;
            parent[i] = -1;
            distance[i] = INF;
        }
        distance[source] = 0;
        Queue q;
        q.enqueue(source);
        int u,length;
        while(!q.empty())
        {
            u = q.dequeue();
            if(u == sink)
                pathExists = true;

            length = residualGraph[u].getLength();
            for(int i=0; i<length; i++)
            {
                Node x = residualGraph[u].getItem(i);
                if(color[x.nodeValue] == white && (x.edgeCapacity-x.edgeFlow) > 0 )
                {
                    color[x.nodeValue] = grey;
                    distance[x.nodeValue] = distance[u] + 1;
                    parent[x.nodeValue] = u;
                    q.enqueue(x.nodeValue);
                }
            }
            color[u] = black;

        }
        return pathExists;
    }

    void fordFulkarson(int source, int sink)
    {
        int pathMinFlow;

        while(augmentedPathExists(source, sink))
        {
            pathMinFlow = INF;
            int t = sink;
            while(parent[t] != -1)
            {
                int p = parent[t];
                int idx = residualGraph[p].searchItem(t);
                int flow = residualGraph[p].getItem(idx).edgeCapacity;
                if(flow < pathMinFlow)
                    pathMinFlow = flow;
                t = parent[t];
            }

            t = sink;
            while(parent[t] != -1)
            {
                bool antiParallal = false;

                int p = parent[t];
                if(isEdge(p,t) && isEdge(t,p))
                    antiParallal = true;

                if(!antiParallal)
                {
                    int idx = adjList[p].searchItem(t);
                    if(idx != NULL_VALUE)
                    {
                        adjList[p].changeFlow(idx,adjList[p].getItem(idx).edgeFlow + pathMinFlow);
                        residualGraph[p].changeCapacity(residualGraph[p].searchItem(t),adjList[p].getItem(idx).edgeCapacity - adjList[p].getItem(idx).edgeFlow);
                        residualGraph[t].changeCapacity(residualGraph[t].searchItem(p),adjList[p].getItem(idx).edgeFlow);
                    }
                    else
                    {
                        int i = adjList[t].searchItem(p);
                        adjList[t].changeFlow(i,adjList[t].getItem(i).edgeFlow - pathMinFlow);
                        residualGraph[t].changeCapacity(residualGraph[t].searchItem(p),adjList[t].getItem(i).edgeCapacity - adjList[t].getItem(i).edgeFlow);
                        residualGraph[p].changeCapacity(residualGraph[p].searchItem(t),adjList[t].getItem(i).edgeFlow);
                    }
                }
                else{
                    int idx = adjList[p].searchItem(t);
                    if(adjList[p].getItem(idx).edgeCapacity - adjList[p].getItem(idx).edgeFlow >= pathMinFlow){
                        adjList[p].changeFlow(idx, adjList[p].getItem(idx).edgeFlow + pathMinFlow);
                        residualGraph[p].changeCapacity(residualGraph[p].searchItem(t), adjList[p].getItem(idx).edgeCapacity - adjList[p].getItem(idx).edgeFlow + adjList[t].getItem(adjList[t].searchItem(p)).edgeFlow);
                        residualGraph[t].changeCapacity(residualGraph[t].searchItem(p), adjList[p].getItem(idx).edgeFlow + adjList[t].getItem(adjList[t].searchItem(p)).edgeCapacity - adjList[t].getItem(adjList[t].searchItem(p)).edgeFlow);
                    }
                    else{
                        adjList[p].changeFlow(idx, adjList[p].getItem(idx).edgeCapacity);
                        int flow = pathMinFlow - (adjList[p].getItem(idx).edgeCapacity - adjList[p].getItem(idx).edgeFlow);
                        adjList[t].changeFlow(adjList[t].searchItem(p),adjList[t].getItem(adjList[t].searchItem(p)).edgeFlow - flow);
                        residualGraph[p].changeCapacity(residualGraph[p].searchItem(t), adjList[p].getItem(idx).edgeCapacity - adjList[p].getItem(idx).edgeFlow + adjList[t].getItem(adjList[t].searchItem(p)).edgeFlow);
                        residualGraph[t].changeCapacity(residualGraph[t].searchItem(p), adjList[p].getItem(idx).edgeFlow + adjList[t].getItem(adjList[t].searchItem(p)).edgeCapacity - adjList[t].getItem(adjList[t].searchItem(p)).edgeFlow);
                    }
                }

                t = parent[t];
            }

        }

        maxFlowOutput(source);

    }

    void maxFlowOutput(int source){
        int maxFlow = 0;
        int length = adjList[source].getLength();

        for(int i=0;i<length;i++){
            maxFlow += adjList[source].getItem(i).edgeFlow;
        }
        cout << maxFlow << endl;

        for(int i=0;i<nVertices;i++){
            length = adjList[i].getLength();
            for(int j=0;j<length;j++){
                cout << i << " " << adjList[i].getItem(j).nodeValue << " " << adjList[i].getItem(j).edgeFlow << "/" << adjList[i].getItem(j).edgeCapacity << endl;
            }
        }
    }

    void printGraph()
    {
        for(int i=0; i<nVertices; i++)
        {
            cout << i << ":";
            int length = adjList[i].getLength();
            for(int j=0; j<length; j++)
            {
                cout << " (" <<adjList[i].getItem(j).nodeValue << ", " << adjList[i].getItem(j).edgeCapacity << ", " << adjList[i].getItem(j).edgeFlow << ") " ;
            }
            cout << endl;
        }

        cout << "residual graph: " << endl;

        for(int i=0; i<nVertices; i++)
        {
            cout << i << ":";
            int length = residualGraph[i].getLength();
            for(int j=0; j<length; j++)
            {
                cout << " (" <<residualGraph[i].getItem(j).nodeValue << ", " << residualGraph[i].getItem(j).edgeCapacity << ", " << residualGraph[i].getItem(j).edgeFlow << ") " ;
            }
            cout << endl;
        }
    }

    ~Graph()
    {
        if(adjList)
            delete []adjList;
        file.close();
    }
};

int main()
{
    ifstream file;
    file.open("input.txt");
    int vertices, edges;
    file >> vertices >> edges;

    Graph g(vertices, edges);

    int u,v,capacity;

    for(int i=0;i<edges;i++){
        file >> u >> v >> capacity;
        g.addEdge(u,v,capacity);
    }

    file >> u >> v;

    g.fordFulkarson(u,v);
}
