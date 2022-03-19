#include<iostream>
#include<string>
using namespace std;

void printLcs(int **b,string x,int i,int j)
{
    if(i==0 || j==0)
        return;
    if(b[i][j]==1)
    {
        printLcs(b,x,i-1,j-1);
        cout << x[i-1];
    }

    else if(b[i][j]==2)
    {
        printLcs(b,x,i-1,j);
    }
    else if(b[i][j]==3)
    {
        printLcs(b,x,i,j-1);
    }
}

void lcs(string x,string y)
{
    int m = x.size();
    int n = y.size();
    int c[m+1][n+1];
    int **b;
    b = new int*[m+1];
    for(int i=0;i<m+1;i++)
    {
        b[i] = new int[n+1];
    }


    for(int i=0;i<m+1;i++)
    {
        c[i][0] = 0;
        b[i][0] = 0;
    }
    for(int i=0;i<n+1;i++)
    {
        c[0][i] = 0;
        b[0][i] = 0;
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(x[i]==y[j])
            {
                c[i+1][j+1] = c[i][j]+1;
                b[i+1][j+1] = 1;
            }
            else if(c[i][j+1] >= c[i+1][j])
            {
                c[i+1][j+1] = c[i][j+1];
                b[i+1][j+1] = 2;
            }
            else
            {
                c[i+1][j+1] = c[i+1][j];
                b[i+1][j+1] = 3;
            }
        }
    }

    printLcs(b,x,m,n);
}


int main()
{
    string first,second;
    cin >> first >> second;
    lcs(first,second);
    return 0;
}
