#include<iostream>
#include<stdlib.h>
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
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data;
    data = 0;
}

class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        delete[] list ;
        list = tempList ;
	};

	list[length] = newitem ;
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position)
{
	if ( position < 0 || position >= length ) return ;
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
    for(int i = 0;i<length;i++)
    {
        if(list[i]==item)
        {
            removeItemAt(i);
            return;
        }
    }
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;

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
    int getOutDegree(int u);
    int getInDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void dfs(int source);
	void dfsVisit(int source);

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
	color = 0;
	distance = 0;
	parent = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ;
	adjList = new ArrayList[nVertices] ;
}

bool Graph::addEdge(int u, int v)
{
    bool edgeAdded;
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || u == v) return false;
    if(adjList[u].searchItem(v) == NULL_VALUE){
        this->nEdges++ ;
        adjList[u].insertItem(v) ;
        if(!directed) adjList[v].insertItem(u) ;
        edgeAdded = true;
    }
    else edgeAdded = false;

    return edgeAdded;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    if(isEdge(u,v)){
        this->nEdges-- ;
        adjList[u].removeItem(v);
        if(!directed)adjList[v].removeItem(u);
    }
}

bool Graph::isEdge(int u, int v)
{
    if(adjList[u].searchItem(v) == NULL_VALUE) return false;
    else return true;
}

int Graph::getDegree(int u,bool out = true)
{
    if(out)
    {
        return adjList[u].getLength();
    }
    else
    {
        int degree = 0;
        for(int i=0; i<nVertices;i++)
        {
            if(i==u) continue;
            if(adjList[i].searchItem(u) != NULL_VALUE) degree++;
        }
        return degree;
    }
}

int Graph::getOutDegree(int u){
    return adjList[u].getLength();
}

int Graph::getInDegree(int u){
    int degree = 0;
    for(int i=0; i<nVertices; i++)
    {
        if(i==u)
            continue;
        if(adjList[i].searchItem(u) != NULL_VALUE)
            degree++;
    }
    return degree;
}


void Graph::printAdjVertices(int u)
{
    int length = adjList[u].getLength();
    for(int i = 0;i<length;i++)
    {
        cout << adjList[u].getItem(i) << " ";
    }
    cout << endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    int length = adjList[u].getLength();
    for(int i = 0; i<length; i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i)) != NULL_VALUE) return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    color = new int[nVertices];
    distance = new int[nVertices];
    parent = new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        color[i] = white;
        parent[i] = INFINITY;
        distance[i] = INFINITY;
    }

    distance[source] = 0;
    Queue q;
    q.enqueue(source);
    int u,length;
    while(!q.empty())
    {
        u = q.dequeue();
        cout << u << " ";
        length = adjList[u].getLength();
        for(int i=0;i<length;i++)
        {
            int x = adjList[u].getItem(i);
            if(color[x] == white)
            {
                color[x] = grey;
                distance[x] = distance[u] + 1;
                parent[x] = u;
                q.enqueue(x);
            }
        }
        color[u] = black;
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

void Graph::dfsVisit(int source)
{
    cout << source << " ";
    dfsColor[source] = grey;
    for(int i=0; i<adjList[source].getLength(); i++)
    {
        int idx = adjList[source].getItem(i);
        if(dfsColor[idx] == white)
        {
            dfsParent[idx] = source;
            dfsVisit(idx);
        }
    }
    dfsColor[source] = black;
}



int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
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
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList) delete []adjList;
    if(color) delete [] color;
    if(distance) delete []distance;
    if(parent) delete []parent;
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

