#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#define NULL_VALUE -99999
#define INF 99999
using namespace std;

class NodeDistancePair
{
public:
    int nodeValue;
    int nodeDistance;
};

class Edge
{
private:
    int nodeValue;
    double nodeWeight;
public:
    void setNodeValue(int value)
    {
        nodeValue = value;
    }
    int getNodeValue()
    {
        return nodeValue;
    }
    void setNodeWeight(double weight)
    {
        nodeWeight = weight;
    }
    double getNodeWeight()
    {
        return nodeWeight;
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
};


class ArrayList
{
private:
    Edge *a;
    int length;
    int maxSize;
public:
    ArrayList()
    {
        a = new Edge[2];
        length = 0;
        maxSize = 2;
    }

    int searchItem(int nodeValue)
    {
        for(int i=0; i<length; i++)
        {
            if(a[i].getNodeValue() == nodeValue)
                return i;
        }
        return NULL_VALUE;
    }

    void insertItem(int value, double weight)
    {
        if(length == maxSize)
        {
            Edge *temp;
            maxSize = 2*maxSize;
            temp = new Edge[maxSize];
            for(int i=0; i<length; i++)
            {
                temp[i] = a[i];
            }
            temp[length].setNodeValue(value);
            temp[length].setNodeWeight(weight);
            delete []a;
            a = temp;
            length++;
        }
        else
        {
            a[length].setNodeValue(value);
            a[length].setNodeWeight(weight);
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
    Edge getItem(int idx)
    {
        if(idx<0 || idx>=length){
            Edge x;
            x.setNodeValue(NULL_VALUE);
            x.setNodeWeight(NULL_VALUE);
            return x;
        }
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
            cout << "(" << a[i].getNodeValue() << "," << a[i].getNodeWeight() << ") ";
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
    int nVertices;
    ArrayList *adjList,*g;
    double *distance;
    double *distanceDijkstra;
    int *parentDijkstra;
    int *parent,**parentMatrix;
    double **distanceMatrix;

    Edge temp;

public:
    Graph()
    {
        distance = 0;
        parent = 0;
        adjList = 0;
    }

    void setnVertices(int vertices)
    {
        this->nVertices = vertices;
        adjList = new ArrayList[nVertices];

        distanceMatrix = new double*[nVertices];
        for(int i=0; i<nVertices; i++)
        {
            distanceMatrix[i] = new double[nVertices];
            for(int j=0; j<nVertices; j++)
            {
                if(i==j)
                    distanceMatrix[i][j] = 0;
                else
                    distanceMatrix[i][j] = INF;
            }
        }

        parentMatrix = new int*[nVertices];
        for(int i=0; i<nVertices; i++)
        {
            parentMatrix[i] = new int[nVertices];
            for(int j=0; j<nVertices; j++)
            {
                parentMatrix[i][j] = -1;
            }
        }

    }

    void addEdge(int u, int v, double weight)
    {
        if(u<0 || u>nVertices || v<0 || v>nVertices || u==v)
            return;
        adjList[u].insertItem(v,weight);
    }

    void removeEdge(int u,int v)
    {
        if(u<0 || u>nVertices || v<0 || v>nVertices)
            return;
        adjList[u].removeItem(v);
    }

    Edge *searchEdge(int u, int v)
    {
        int idx = adjList[u].searchItem(v);
        if(idx == NULL_VALUE) return nullptr;
        temp = adjList[u].getItem(idx);
        return &temp;
    }

    void reweightEdge(int u, int v, int weight)
    {
        int idx = adjList[u].searchItem(v);
        if(idx == NULL_VALUE)
        {
            addEdge(u,v,weight);
        }
        else
        {
            adjList[u].getItem(idx).setNodeWeight(weight);
        }
    }

    bool isEdge(int u, int v)
    {
        if(adjList[u].searchItem(v) == NULL_VALUE)
            return false;
        else
            return true;
    }

    double getWeight(int u,int v)
    {
        int idx = adjList[u].searchItem(v);
        if(idx != NULL_VALUE)
            return adjList[u].getItem(idx).getNodeWeight();
        else
            return NULL_VALUE;
    }

    void output(int s, int d){
        if(parentMatrix[s][d] == -1) {
            cout << "no shortest path available" << endl;
            return;
        }
        cout << "shortest path weight: " << distanceMatrix[s][d] << endl;
        int *a = new int[nVertices];
        int length = 0;
        int i=0;
        a[i++] = d;
        length++;
        int predecessor = d;
        double *pathWeight = new double[nVertices];
        while(parentMatrix[s][predecessor] != -1){
            pathWeight[i] = adjList[parentMatrix[s][predecessor]].getItem(adjList[parentMatrix[s][predecessor]].searchItem(predecessor)).getNodeWeight();
            predecessor = parentMatrix[s][predecessor];
            a[i++] = predecessor;
            length++;
        }

        int j=length-1;

        for(int i=length-1;i>=0;i--){
            cout << a[i]+1;
            if(i!=length-1) cout << "(" << pathWeight[j--] << ")";
            if(i!=0) cout << "->";
        }
        cout << endl;
        delete []a;
        delete []pathWeight;

    }
    void dijkstra(int s)
    {
        if(distanceDijkstra)
            delete []distanceDijkstra;
        if(parentDijkstra)
            delete []parentDijkstra;

        distanceDijkstra = new double[nVertices];
        parentDijkstra = new int[nVertices];

        for(int i=0; i<nVertices; i++)
        {
            distanceDijkstra[i] = INF;
            parentDijkstra[i] = -1;
        }
        distanceDijkstra[s] = 0;
        parentDijkstra[s] = s;
        pQueue q;
        q.insert(s,0);
        int u,v;
        double weightOfUV;
        NodeDistancePair x;
        while(!q.empty())
        {
            x = q.extractMin();
            u = x.nodeValue;
            int l = g[u].getLength();
            for(int i=0; i<l; i++)
            {
                v = g[u].getItem(i).getNodeValue();
                weightOfUV = g[u].getItem(i).getNodeWeight();
                if(weightOfUV < 0)
                    weightOfUV = -weightOfUV;
                if(distanceDijkstra[v] > distanceDijkstra[u]+weightOfUV)
                {
                    distanceDijkstra[v] = distanceDijkstra[u]+weightOfUV;
                    parentDijkstra[v] = u;
                    q.insert(v,distanceDijkstra[v]);
                }
            }
        }
    }

    void relax(int u, int v,double weight)
    {
        double distFromU = distance[u] + weight;
        if(distance[v] > distFromU)
        {
            distance[v] = distFromU;
            parent[v] = u;
        }
    }

    bool bellManFord(int s)
    {
        int newVertex = nVertices+1;
        if(distance)
            delete []distance;
        if(parent)
            delete []parent;

        distance = new double[newVertex];
        parent = new int[newVertex];

        for(int i=0; i<newVertex; i++)
        {
            distance[i] = INF;
        }

        distance[s] = 0;
        parent[s] = s;
        for(int i=0; i<newVertex-1; i++)
        {
            for(int j=0; j<newVertex; j++)
            {
                int l = g[j].getLength();
                for(int k=0; k<l; k++)
                {
                    relax(j,g[j].getItem(k).getNodeValue(),g[j].getItem(k).getNodeWeight());
                }
            }
        }

        for(int i=0; i<newVertex; i++)
        {
            int l = g[i].getLength();
            for(int j=0; j<l; j++)
            {
                Edge source = g[i].getItem(j);
                if((distance[source.getNodeValue()] > distance[i] + source.getNodeWeight())  && distance[source.getNodeValue()]!=INF)
                {
                    return true;
                }
            }
        }

        return false;
    }

    double minimum(double x, double y)
    {
        if(y<x)
            return y;
        else
            return x;
    }

    void floyedWarshal()
    {
        cleanSPInfo();
        for(int i=0;i<nVertices;i++) distanceMatrix[i][i] = 0;

        for(int i=0; i<nVertices; i++)
        {
            int l = adjList[i].getLength();
            for(int j=0; j<l; j++)
            {
                int node = adjList[i].getItem(j).getNodeValue();
                distanceMatrix[i][node] = adjList[i].getItem(j).getNodeWeight();
                parentMatrix[i][node] = i;
            }
        }

        for(int k=0; k<nVertices; k++)
        {
            for(int i=0; i<nVertices; i++)
            {
                for(int j=0; j<nVertices; j++)
                {
                    if(distanceMatrix[i][j] > distanceMatrix[i][k]+distanceMatrix[k][j])
                    {
                        distanceMatrix[i][j] = distanceMatrix[i][k]+distanceMatrix[k][j];
                        parentMatrix[i][j] = parentMatrix[k][j];
                    }
                }
            }
        }
    }

    void johnsonsAlgo()
    {
        cleanSPInfo();
        for(int i=0;i<nVertices;i++) distanceMatrix[i][i] = 0;

        g = new ArrayList[nVertices+1];
        int newVertex = nVertices+1;

        for(int i=0; i<nVertices; i++)
        {
            int l = adjList[i].getLength();
            for(int j=0; j<l; j++)
            {
                Edge node = adjList[i].getItem(j);
                g[i].insertItem(node.getNodeValue(),node.getNodeWeight());
            }
        }

        for(int i=0; i<nVertices; i++)
        {
            g[nVertices].insertItem(i,0);
        }
        if(bellManFord(newVertex-1))
        {
            cout << "graph has negative cycle" << endl;
            return;
        }

        ArrayList *temp = new ArrayList[nVertices];

        for(int i=0; i<newVertex-1; i++)
        {
            int l = g[i].getLength();
            for(int j=0; j<l; j++)
            {
                int dest = g[i].getItem(j).getNodeValue();
                double newWeight = g[i].getItem(j).getNodeWeight() + distance[i]-distance[dest];

                temp[i].insertItem(dest,newWeight);
            }
        }

        delete []g;
        g = temp;
        for(int i=0;i<nVertices;i++){
            dijkstra(i);
            for(int j=0;j<nVertices;j++){
                distanceMatrix[i][j] = distanceDijkstra[j] + distance[j]-distance[i];
                if(i==j) parentMatrix[i][j] = -1;
                else parentMatrix[i][j] = parentDijkstra[j];
            }
        }
    }

    double getShortestPathWeight(int u,int v)
    {
        return distanceMatrix[u][v];
    }

    void printDistanceMatrix()
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                if(distanceMatrix[i][j] == INF)
                    cout << "INF" << " ";
                else
                    cout << distanceMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void printPredecessorMatrix()
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                if(parentMatrix[i][j] == -1)
                    cout << "NIL" << " ";
                else
                    cout << parentMatrix[i][j]+1 << " ";
            }
            cout << endl;
        }
    }

    void cleanSPInfo()
    {
        for(int i=0; i<nVertices; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                distanceMatrix[i][j] = INF;
                parentMatrix[i][j] = -1;
            }
        }
    }


    void printGraph()
    {
        cout << "Graph:" << endl;
        for(int i=0; i<nVertices; i++)
        {
            cout << i+1 << ":";
            int l = adjList[i].getLength();
            for(int j=0; j<l; j++)
            {
                cout << adjList[i].getItem(j).getNodeValue()+1 <<"(" << adjList[i].getItem(j).getNodeWeight() <<")" << " ";
                if(j!=l-1) cout << "->";
            }
            cout << endl;
        }
    }


    ~Graph()
    {
        if(adjList)
            delete []adjList;
        if(distance)
            delete [] distance;
        if(parent)
            delete []parent;
        if(distanceMatrix)
        {
            for(int i=0; i<nVertices; i++)
            {
                delete []distanceMatrix[i];
            }
            delete []distanceMatrix;
        }

        if(parentMatrix)
        {
            for(int i=0; i<nVertices; i++)
            {
                delete []parentMatrix[i];
            }
            delete []parentMatrix;
        }

    }
};

int main(){
    ifstream file;
    file.open("input.txt");
    int vertices,edges;

    file >> vertices >> edges;
    Graph *g = new Graph();
    g->setnVertices(vertices);

    int u,v;
    double w;
    for(int i=0; i<edges; i++)
    {
        file >> u >> v >> w;
        g->addEdge(u-1,v-1,w);
    }
    cout << "Graph created" << endl;
    int choice;
    while(1){
        file >> choice;
        if(choice == 1){
            g->cleanSPInfo();
            cout << "APSP matrices cleared"<<endl;
        }
        else if(choice == 2){
            g->floyedWarshal();
            cout << "Floyed-Warshal algorithm implemented" << endl;
        }
        else if(choice == 3){
            g->johnsonsAlgo();
            cout << "johnson's algorithm implemented" << endl;
        }

        else if(choice == 4){
            file >> u >> v;
            g->output(u-1,v-1);
        }

        else if(choice == 5){
            g->printGraph();
        }
        else if(choice == 6){
            cout << "Distance matrix:" << endl;
            g->printDistanceMatrix();
        }
        else if(choice == 7){
            cout << "Predecessor matrix:" << endl;
            g->printPredecessorMatrix();
        }
        else break;
    }
    file.close();
    delete g;
}

/*
int main(){
    int vertices,edges;
    cin >> vertices >> edges;

    Graph *g = new Graph();
    g->setnVertices(vertices);

    int u,v;
    double w;
    for(int i=0;i<edges;i++){
        cin >> u >> v >> w;
        g->addEdge(u-1,v-1,w);
    }

    cout << "Graph created " << endl;
    int choice;
    while(1){
        cin >> choice;
        if(choice == 1){
            g->cleanSPInfo();
            cout << "APSP matrices cleared"<<endl;
        }
        else if(choice == 2){
            g->floyedWarshal();
            cout << "Floyed-Warshal algorithm implemented" << endl;
        }
        else if(choice == 3){
            g->johnsonsAlgo();
            cout << "johnson's algorithm implemented" << endl;
        }

        else if(choice == 4){
            cin >> u >> v;
            cout << "shortest path weight:" <<g->getShortestPathWeight(u-1,v-1) << endl;
            g->output(u-1,v-1);
        }

        else if(choice == 5){
            g->printGraph();
        }
        else if(choice == 6){
            cout << "Distance matrix:" << endl;
            g->printDistanceMatrix();
        }
        else if(choice == 7){
            cout << "Predecessor matrix:" << endl;
            g->printPredecessorMatrix();
        }
        else break;
    }
    delete g;

}*/
