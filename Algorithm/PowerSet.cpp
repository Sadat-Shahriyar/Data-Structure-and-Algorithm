#include<iostream>
#include<chrono>
#include<cmath>
using namespace std;

double powerSet(int a[],int n)
{
    auto start = std::chrono::system_clock::now();
    int powerSetSize = pow(2,n);
    bool first;
    int b;
    cout << "ans:" << endl;

    for(int i=0; i<powerSetSize; i++)
    {
        cout << "{";

        b = i;
        first = true;
        for(int j=0; j<n; j++)
        {
            if(b&1)
            {
                if(first)
                {
                    first = false;
                }
                else
                {
                    cout << ",";

                }
                cout << a[j];

            }
            b = b/2;
        }
        cout << "}" << endl;

    }
    auto finish = std::chrono::system_clock::now();
    double timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();
    return timeTaken;

}

int main()
{
    int n=0;
    double totalTime;
    while(n>=0)
    {
        cout << "size=" ;
        cin >> n;
        int a[n];
        for(int i=0; i<n; i++)
        {
            a[i] = rand()%30;
        }
        totalTime = powerSet(a,n);
        cout << "total time= " << totalTime << endl;
    }
    return 0;
}
