#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cstdio>
#include<chrono>

using namespace std;
#define NULL_VALUE -999999
#define INFINITY 999999
#define white 0
#define grey 1
#define black 2


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

class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ;

    int *color;
    int *distance;
    int *parent;

    int *dfsColor;
    int *dfsParent;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u,bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source);
    void dfs(int source);
    void dfsVisit(int source);
    int getOutDegree(int u);
    int getInDegree(int u);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    directed = dir ;
    color = 0;
    distance = 0;
    parent = 0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0;
    }

}

bool Graph::addEdge(int u, int v)
{
    bool edgeAdded;
    if(u<0 || u>=nVertices || v<0 || v>=nVertices || u==v)
        return false;
    if(matrix[u][v] == 0){
        edgeAdded = true;
        matrix[u][v] = 1;
        if(!directed)
            matrix[v][u] = 1;
        nEdges++;
    }
    else{
        edgeAdded = false;
    }
    return edgeAdded;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;
    if(isEdge(u,v)) {
        nEdges--;
        matrix[u][v] = 0;
        if(!directed)
            matrix[v][u] = 0;
    }


}

bool Graph::isEdge(int u, int v)
{
    if(matrix[u][v])
        return true;
    else
        return false;
}

int Graph::getDegree(int u,bool out = true)
{
    int degree = 0;
    if(out)
    {
        for(int i = 0; i<nVertices; i++)
        {
            if(matrix[u][i] == 1)
                degree++;
        }
    }
    else
    {
        for(int i=0; i<nVertices; i++)
        {
            if(matrix[i][u] == 1)
                degree++;
        }
    }

    return degree;
}

int Graph::getOutDegree(int u){
    int degree = 0;
    for(int i = 0; i<nVertices; i++)
    {
        if(matrix[u][i] == 1)
            degree++;
    }
    return degree;
}




int Graph::getInDegree(int u){
    int degree = 0;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[i][u] == 1)
            degree++;
    }

    return degree;
}


void Graph::printAdjVertices(int u)
{
    for(int i = 0; i<nVertices; i++)
    {
        if(matrix[u][i] || matrix[i][u])
            cout << i << " ";
    }
    cout << endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i = 0; i<nVertices; i++)
    {
        if(matrix[u][i] && matrix[v][i])
            return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    if(source < 0 || source >= nVertices) return;

    if(color) delete []color;
    if(distance) delete [] distance;
    if(parent) delete[]parent;

    color = new int[nVertices];
    distance = new int[nVertices];
    parent = new int[nVertices];

    for(int i = 0; i<nVertices; i++)
    {
        color[i] = white;
        distance[i] = INFINITY;
        parent[i] = INFINITY;
    }

    Queue q;
    q.enqueue(source);
    distance[source] = 0;
    int x;
    while(!q.empty())
    {
        x = q.dequeue();
        cout << x << " ";
        for(int i = 0; i<nVertices; i++)
        {
            if(matrix[x][i])
            {
                if(color[i] == white)
                {
                    color[i] = grey;
                    distance[i] = distance[x]+1;
                    parent[i] = x;
                    q.enqueue(i);
                }
            }
        }
        color[x] = black;
    }
    cout << endl;

}

void Graph::dfs(int source){
    if(source<0 || source>=nVertices) return;

    if(dfsColor) delete []dfsColor;
    if(dfsParent) delete []dfsParent;

    dfsColor = new int[nVertices];
    dfsParent = new int[nVertices];

    for(int i=0; i<nVertices; i++){
        dfsColor[i] = white;
        dfsParent[i] = INFINITY;
    }

    dfsVisit(source);
    cout <<endl;
}

void Graph::dfsVisit(int source){
    cout << source << " ";
    dfsColor[source] = grey;
    for(int i=0;i<nVertices;i++){
        if(matrix[source][i] == 1){
            if(dfsColor[i] == white){
                dfsParent[i] = source;
                dfsVisit(i);
            }

        }
    }

    dfsColor[source] = black;
}

int Graph::getDist(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return INFINITY ;
    else
    {
        bfs(u);
        return distance[v];
    }
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(color) delete []color;
    if(distance) delete []distance;
    if(parent) delete []parent;
    if(matrix)
    {
        for(int i = 0;i<nVertices;i++)
            delete []matrix[i];
        delete []matrix;
    }

    if(dfsColor) delete []dfsColor;
    if(dfsParent) delete []dfsParent;
}


void getBfsTime(Graph *g, int numOfVertices){
    int u,v,source;
    long long int numOfEdgeRange = (numOfVertices*numOfVertices - numOfVertices)/8;
    long long int numOfEdge;

    cout << "vertices = " << numOfVertices << ":" << endl;

    for(numOfEdge=numOfVertices; numOfEdge<=numOfEdgeRange; numOfEdge*=2){
        for(long long int i=0; i<numOfEdge; i++)
        {
            u = rand()%numOfVertices;
            v = rand()%numOfVertices;
            while(g->isEdge(u,v))
            {
                u = rand()%numOfVertices;
                v = rand()%numOfVertices;
            }

            g->addEdge(u,v);
        }

        double totalTime = 0;
        for(int i=0;i<10;i++)
        {
            source = rand()%numOfVertices;
            auto start = std::chrono::system_clock::now();
            g->bfs(source);
            auto finish = std::chrono::system_clock::now();
            double timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();
            totalTime += timeTaken;
        }
        cout << "edges = " << numOfEdge << " average time = " << totalTime/10 << endl;

    }
}


int main(void)
{
    int n;
    int numOfVertices;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)
        dir = true;
    else if(choice == 2)
        dir = false;

    Graph *g = new Graph(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g->setnVertices(n);
    numOfVertices = n;
    int u, v;
    while(1)
    {

        cout << "1. add edge 2. remove edge 3.is edge(u,v)? 4. get out degree 5. get in degree 6. print graph 7. exit " <<
        "8. run bfs 9.get distance 10.print adjacent vertices 11.has common adjacent vertices? 12. run dfs" <<
        " 13. create new graph  14. get bfs time"<<endl;

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            cout << "enter vertices = ";
            scanf("%d%d", &u, &v);
            g->addEdge(u, v);
        }
        else if(ch==2)
        {
            cout << "enter vertices = " ;
            cin >> u >> v;
            g->removeEdge(u,v);

        }
        else if(ch==3)
        {
            cout << "enter vertices=" ;
            cin >> u >> v;

            if(g->isEdge(u,v)) cout << "yes"<< endl;
            else cout << "no" << endl;
        }
        else if(ch==4)
        {
            cout << "enter vertex=";
            cin >> u;
            cout << g->getOutDegree(u) << endl;

        }
        else if(ch == 5){
            cout << "enter vertex = ";
            cin >> u;
            cout << g->getInDegree(u) << endl;
        }
        else if(ch==6)
        {
            g->printGraph();
        }
        else if(ch==7)
        {
            break;
        }
        else if(ch == 8)
        {
            cout << "enter root = ";
            cin >> u;
            g->bfs(u);
        }
        else if(ch == 9)
        {
            cout << "enter vertices = ";
            cin >> u >> v;
            cout << g->getDist(u,v) << endl;
        }
        else if(ch == 10)
        {
            cout << "enter vertex = ";
            cin >> u;
            g->printAdjVertices(u);
        }
        else if(ch == 11)
        {
            cout << "enter vertices = " ;
            cin >> u >> v;
            if(g->hasCommonAdjacent(u,v)) cout << "yes" << endl;
            else cout << "no" << endl;
        }
        else if(ch == 12){
            cout << "source = ";
            cin >> u;
            g->dfs(u);
        }

        else if(ch == 13){
            delete g;
            printf("Enter your choice:\n");
            printf("1. directed graph   2. undirected graph\n");
            scanf("%d",&choice);
            if(choice == 1)
                dir = true;
            else if(choice == 2)
                dir = false;

            g = new Graph(dir);
            printf("Enter number of vertices: ");
            scanf("%d", &n);
            numOfVertices = n;
            g->setnVertices(n);
        }

        else if(ch == 14){
            getBfsTime(g,numOfVertices);
        }
    }

}
