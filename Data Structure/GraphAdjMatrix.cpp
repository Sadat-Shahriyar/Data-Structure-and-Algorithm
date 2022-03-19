#include<stdio.h>
#include<stdlib.h>
#include<iostream>


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
    rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix ; //adjacency matrix to store the graph
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
    matrix = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    color = 0;
    distance = 0;
    parent = 0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;
    matrix[u][v] = 1;
    if(!directed)
        matrix[v][u] = 1;
    nEdges++;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return;
    if(isEdge(u,v)) nEdges--;
    matrix[u][v] = 0;
    if(!directed)
        matrix[v][u] = 0;


}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(matrix[u][v])
        return true;
    else
        return false;
}

int Graph::getDegree(int u,bool out = true)
{
    //returns the degree of vertex u
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

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    for(int i = 0; i<nVertices; i++)
    {
        if(matrix[u][i] || matrix[i][u])
            cout << i << " ";
    }
    cout << endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    for(int i = 0; i<nVertices; i++)
    {
        if(matrix[u][i] && matrix[v][i])
            return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    //write this function
    if(source < 0 || source >= nVertices) return;
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

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
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
    //write your destructor here
    if(color)
        delete []color;
    if(distance)
        delete []distance;
    if(parent)
        delete []parent;
    if(matrix)
    {
        for(int i = 0;i<nVertices;i++)
            delete []matrix[i];
        delete []matrix;
    }
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
    if(choice == 1)
        dir = true;
    else if(choice == 2)
        dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);
    int u, v;
    while(1)
    {
        printf("1. Add edge. \n");
        cout << "2. remove edge 3.is edge(u,v)? 4. get degree 5. print graph 6. exit " <<
        "7. run bfs 8.get distance 9.print adjacent vertices 10.has common adjacent vertices?" <<endl;

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            cout << "enter vertices = ";
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
