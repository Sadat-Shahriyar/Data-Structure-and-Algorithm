#include<iostream>
#include<stdlib.h>
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
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
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
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	bool searchItem(int item) ;
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
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

bool ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return true;
	}
	return false;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
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

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *color;
	int *distance;
	int *parent;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u,bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	color = 0;
	distance = 0;
	parent = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
	cout << "edge added" << endl;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
    adjList[u].removeItem(v);
    if(!directed)adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v)) return true;
    else return false;
}

int Graph::getDegree(int u,bool out = true)
{
    //returns the degree of vertex u
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
            if(adjList[i].searchItem(u)) degree++;
        }
        return degree;
    }
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    int length = adjList[u].getLength();
    for(int i = 0;i<length;i++)
    {
        cout << adjList[u].getItem(i) << " ";
    }
    cout << endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int length = adjList[u].getLength();
    for(int i = 0; i<length; i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i))) return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables for all n vertices first
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

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
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
    //write your destructor here
    if(adjList) delete []adjList;
    if(color) delete [] color;
    if(distance) delete []distance;
    if(parent) delete []parent;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);
    int u,v;
    while(1)
    {
        printf("1. Add edge. \n");
        cout << "2. remove edge 3.is edge(u,v)? 4. get degree 5. print graph 6. exit " <<
        "7. run bfs 8.get distance 9.print adjacent vertices 10.has common adjacent vertices?" <<endl;

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            cout << "enter vertices = " ;
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            cout << "enter vertices=" ;
            cin >> u >> v;
            g.removeEdge(u,v);

        }
        else if(ch==3)
        {
            cout << "enter vertices=" ;
            cin >> u >> v;

            if(g.isEdge(u,v)) cout << "yes"<< endl;
            else cout << "no" << endl;
        }
        else if(ch==4)
        {
            cout << "enter vertex=";
            cin >> u;
            int c;
            bool out = true;
            cout << "1. out degree? 2. in degree?" ;
            cin >> c;
            if(c == 1) out = true;
            else if(c==2) out = false;
            cout << g.getDegree(u,out) << endl;

        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch == 7)
        {
            cout << "enter root = ";
            cin >> u;
            g.bfs(u);
        }
        else if(ch == 8)
        {
            cout << "enter vertices = ";
            cin >> u >> v;
            int dist = g.getDist(u,v);
            cout << dist << endl;
        }
        else if(ch == 9)
        {
            cout << "enter vertex = ";
            cin >> u;
            g.printAdjVertices(u);
        }
        else if(ch == 10)
        {
            cout << "enter vertices = " ;
            cin >> u >> v;
            if(g.hasCommonAdjacent(u,v)) cout << "yes" << endl;
            else cout << "no" << endl;
        }
    }

}
