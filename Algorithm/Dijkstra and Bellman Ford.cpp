#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
#include<string>
#define NULL_VALUE -99999
#define INF 99999
using namespace std;

//typedef pair<int,int> iPair;

class NodeDistancePair{
public:
    int nodeValue;
    int nodeDistance;
};
class Node{
public:
    int nodeValue;
    int nodeWeight;
};

class ArrayList{
private:
    Node *a;
    int length;
    int maxSize;
public:
    ArrayList(){
        a = new Node[2];
        length = 0;
        maxSize = 2;
    }

    int searchItem(int nodeValue){
        for(int i=0;i<length;i++){
            if(a[i].nodeValue == nodeValue) return i;
        }
        return NULL_VALUE;
    }

    void insertItem(int value, int weight){
        if(length == maxSize){
            Node *temp;
            maxSize = 2*maxSize;
            temp = new Node[maxSize];
            for(int i=0;i<length;i++){
                temp[i] = a[i];
            }
            temp[length].nodeValue = value;
            temp[length].nodeWeight = weight;
            delete []a;
            a = temp;
            length++;
        }
        else{
            a[length].nodeValue = value;
            a[length].nodeWeight = weight;
            length++;
        }

    }

    void removeItem(int value){
        int idx = searchItem(value);
        if(idx == NULL_VALUE) return;

        removeItemAt(idx);
    }

    void removeItemAt(int idx){
        if(idx<0 || idx>=length) return;
        a[idx] = a[--length];
    }
    Node getItem(int idx){
        //if(idx<0 || idx >=length) return ;
        return a[idx];
    }

    int getLength(){return length;}

    bool empty(){
        return (length == 0);
    }
    void printList(){
        for(int i=0;i<length;i++){
            cout << "(" << a[i].nodeValue << "," << a[i].nodeWeight << ") ";
        }
        cout <<endl;
    }

    ~ArrayList(){
        if(a) delete[]a;
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

    bool empty(){
        if(length==0) return true;
        else return false;
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
        else minimum = i;

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
        for(int i=l;i>0;i--)
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
        if(tail == maxSize){
            NodeDistancePair *temp;
            maxSize = 2*maxSize;
            temp = new NodeDistancePair[maxSize];
            for(int i=0;i<tail;i++){
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
        for(int i=1;i<tail;i++)
        {
            if(a[i].nodeValue == node){
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
        for(int i=1;i<tail;i++)
        {
            if(a[i].nodeValue == node){
                idx = i;
                break;
            }
        }
        a[idx].nodeDistance = newKey;
        upwardTransition(idx);
    }

    void print()
    {
        for(int i=1;i<tail;i++)
        {
            cout << a[i].nodeValue << " ";
        }
        cout << endl;
    }
};



class Graph{
private:
    int nVertices, nEdges;
    ArrayList *adjList;
    int *distance;
    int *parent;

    ofstream file;
public:
    Graph(int vertices,int edges){
        this->nVertices = vertices;
        this->nEdges = edges;
        adjList = new ArrayList[nVertices];

        distance = new int[nVertices];
        parent = new int[nVertices];
        file.open("output.txt");
    }

    void addEdge(int u, int v, int weight){
        if(u<0 || u>nVertices || v<0 || v>nVertices || u==v) return;
        adjList[u].insertItem(v,weight);
    }

    void removeEdge(int u,int v){
        if(u<0 || u>nVertices || v<0 || v>nVertices) return;
        adjList[u].removeItem(v);
    }

    bool isEdge(int u, int v){
        if(adjList[u].searchItem(v) == NULL_VALUE) return false;
        else return true;
    }

    int getWeight(int u,int v){
        //if(u<0 || u>nVertices || v<0 || v>nVertices) return NULL_VALUE;
        int idx = adjList[u].searchItem(v);
        if(idx != NULL_VALUE) return adjList[u].getItem(idx).nodeWeight;
        else return NULL_VALUE;
    }

    /*
    void dijkstra(int s,int d){
        priority_queue<iPair,vector<iPair>,greater<iPair>> q;

        for(int i=0;i<nVertices;i++){
            distance[i] = INFINITY;
        }
        distance[s] = 0;
        parent[s] = s;
        q.push(make_pair(0,s)); // make_pair(weight,node)
        int u,v,weightOfUV;
        while(!q.empty()){
            u = q.top().second;
            q.pop();
            int l = adjList[u].getLength();
            for(int i=0; i<l; i++){
                v = adjList[u].getItem(i).nodeValue;
                weightOfUV = adjList[u].getItem(i).nodeWeight;
                if(distance[v] > distance[u]+weightOfUV)
                {
                    distance[v] = distance[u]+weightOfUV;
                    parent[v] = u;
                    q.push(make_pair(distance[v],v));
                }
            }
        }

        cout << distance[d] << endl;
        cout << d << " ";
        while(parent[d] != d){
            d = parent[d];
            cout << d << " ";
        }

        cout << endl;


    }

    */

    void outputToFile(string algoName, int d){
        ArrayList output;
        file << algoName << ":" << endl;
        file << distance[d] <<endl;

        output.insertItem(d,0);
        while(parent[d] != d){
            d = parent[d];
            output.insertItem(d,0);
        }

        int len = output.getLength();
        for(int i=len-1; i>=0;i--){
            file << output.getItem(i).nodeValue ;
            if(i!=0) file << "->";
        }
        file << endl;
    }

    void dijkstra(int s, int d){
        if(distance) delete []distance;
        if(parent) delete []parent;

        distance = new int[nVertices];
        parent = new int[nVertices];

        for(int i=0;i<nVertices;i++)
        {
            distance[i] = INF;
        }
        distance[s] = 0;
        parent[s] = s;
        pQueue q;
        q.insert(s,0);
        int u,v,weightOfUV;
        NodeDistancePair x;
        while(!q.empty()){
            x = q.extractMin();
            u = x.nodeValue;
            int l = adjList[u].getLength();
            for(int i=0;i<l;i++){
                v = adjList[u].getItem(i).nodeValue;
                weightOfUV = adjList[u].getItem(i).nodeWeight;
                if(weightOfUV < 0) weightOfUV = -weightOfUV;
                if(distance[v] > distance[u]+weightOfUV)
                {
                    distance[v] = distance[u]+weightOfUV;
                    parent[v] = u;
                    q.insert(v,distance[v]);
                }
            }
        }

        outputToFile("dijkstra",d);
    }

    void relax(int u, int v,int weight){
        int distFromU = distance[u] + weight;
        if(distance[v] > distFromU){
            distance[v] = distFromU;
            parent[v] = u;
        }
    }

    void bellManFord(int s, int d){
        if(distance) delete []distance;
        if(parent) delete []parent;

        distance = new int[nVertices];
        parent = new int[nVertices];

        for(int i=0; i<nVertices; i++)
        {
            distance[i] = INF;
        }

        distance[s] = 0;
        parent[s] = s;
        for(int i=0; i<nVertices-1; i++)
        {
            for(int j=0; j<nVertices; j++)
            {
                int l = adjList[j].getLength();
                for(int k=0; k<l; k++)
                {
                    relax(j,adjList[j].getItem(k).nodeValue,adjList[j].getItem(k).nodeWeight);
                }
            }
        }

        for(int i=0;i<nVertices;i++){
            int l = adjList[i].getLength();
            for(int j=0;j<l;j++){
                Node source = adjList[i].getItem(j);
                if((distance[source.nodeValue] > distance[i] + source.nodeWeight)  && distance[source.nodeValue]!=INF){
                    file << "bellman ford:" << endl; ;
                    file << "no solution" << endl;
                    return;
                }
            }
        }


        outputToFile("bellman ford",d);
    }

    void printGraph(){
        for(int i=0;i<nVertices;i++){
            cout << i << ":";
            for(int j=0;j<adjList[i].getLength();j++){
                cout << adjList[i].getItem(j).nodeValue << " ";
            }
            cout << endl;
        }
    }


    ~Graph(){
        if(adjList) delete []adjList;
        if(distance) delete [] distance;
        if(parent) delete []parent;
        file.close();
    }
};


int main(){
    ifstream file;
    file.open("input.txt");
    int vertices,edges;
    file >> vertices >> edges;
    Graph *g = new Graph(vertices,edges);

    int u,v,w;
    for(int i=0;i<edges;i++){
        file >> u >> v >> w;
        g->addEdge(u,v,w);
    }

    int s,d;
    file >>  s >> d;
    g->bellManFord(s,d);
    g->dijkstra(s,d);
    file.close();
    delete g;
}
