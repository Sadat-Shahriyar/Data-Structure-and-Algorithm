#include<iostream>
#include<bits/stdc++.h>
#define setSize 100
using namespace std;

class disjointSet{
private:
    int parent[setSize];
    int r[setSize];
public:
    disjointSet()
    {
        for(int i=0;i<setSize;i++)
        {
            parent[i]=-1;
            r[i]=-1;
        }
    }

    void makeSet(int x)
    {
        parent[x]=x;
        r[x]=0;
    }

    int findSet(int x)
    {
        if(parent[x] == -1)
            return -1;
        if(x!=parent[x])
            parent[x] = findSet(parent[x]);

        return parent[x];
    }

    void unionSet(int x,int y)
    {
        int root1 = findSet(x);
        int root2 = findSet(y);
        if(root1 == -1 || root2 == -1)
            return;
        if(root1 == root2)
            return;

        if(r[root1] > r[root2])
        {
            parent[root2] = root1;
            //r[root2] = -1;
        }
        else if(r[root1] < r[root2])
        {
            parent[root1] = root2;
            //parent[root1] = -1;
        }
        else if(r[root1] == r[root2])
        {
            parent[root2]=root1;
            r[root1]++;
            //r[root2] = -1;
        }
    }

    void print(int x)
    {
        int root = findSet(x);
        if(root == -1)
        {
            cout << "enter valid element" << endl;
            return;
        }
        for(int i=0;i<setSize;i++)
        {
            if(findSet(i)==root)
                cout << i << " ";
        }
    }

};



int main()
{
    disjointSet s;
    int choice;
    int input;
    while(true)
    {
        cout << "1.Make set  2.Find set 3.Union set 4.Print  5. Quit" << endl;
        cout << "enter choice: " ;
        cin >> choice;

        if(choice == 1)
        {
            cout << "enter value: ";
            cin >> input;
            s.makeSet(input);
        }

        else if(choice == 2)
        {
            cout << "enter value: ";
            cin >> input;
            cout << s.findSet(input) << endl;
        }

        else if(choice == 3)
        {
            int input2;
            cout << "enter 1st value: ";
            cin >> input;
            cout << "enter 2nd value: " ;
            cin >> input2;
            s.unionSet(input,input2);
        }

        else if(choice == 4)
        {
            cout << "enter value: ";
            cin >> input;
            s.print(input);
            cout << endl;
        }
        else if(choice == 5)
            break;
    }
    return 0;
}
