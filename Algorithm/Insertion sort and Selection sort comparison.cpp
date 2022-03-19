#include<iostream>
#include<chrono>
#include<bits/stdc++.h>
#include<cstdlib>
#define size 8
using namespace std;

int inputSize[] = {10,100,200,500,1000,2000,5000,10000};

void print(int a[],int n)
{
    for(int i=0; i<n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

double insertionSort(int a[], int n)
{
    auto start = std::chrono::system_clock::now();
    int temp,i;
    for(int j=1; j<n; j++)
    {
        temp = a[j];
        for(i=j-1; i>=0 && a[i]>temp; i--)
        {
            a[i+1] = a[i];
        }
        a[i+1] = temp;
    }
    auto finish = std::chrono::system_clock::now();
    double timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();
    return timeTaken;
}

double selectionSort(int a[],int n)
{
    auto start = std::chrono::system_clock::now();
    int minimum,temp,idx;
    minimum = a[0];

    for(int i=0; i<n-1; i++)
    {
        minimum = a[i];
        idx = i;
        for(int j=i+1; j<n; j++)
        {
            if(minimum > a[j])
            {
                minimum = a[j];
                idx = j;
            }
        }

        temp = a[i];
        a[i] = minimum;
        a[idx] = temp;
    }
    auto finish = std::chrono::system_clock::now();
    double timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();
    return timeTaken;

}

int main()
{
    double insertionBest[size];
    double insertionAverage[size];
    double insertionWorst[size];
    double selectionBest[size];
    double selectionAverage[size];
    double selectionWorst[size];

    for(int x=0; x<size; x++)
    {
        int n = inputSize[x];
        int a[n];
        int b[n];
        for(int i=0; i<n; i++)
        {
            a[i] = rand()%10000;
        }
        insertionAverage[x] = insertionSort(a,n);

        insertionBest[x] = insertionSort(a,n);

        reverse(a,a+n);
        insertionWorst[x] = insertionSort(a,n);

        for(int i=0; i<n; i++)
        {
            b[i] = rand()%10000;
        }
        selectionAverage[x] = selectionSort(b,n);

        selectionBest[x] = selectionSort(b,n);

        reverse(b,b+n);
        selectionWorst[x] = selectionSort(b,n);
    }

    cout << "insertion sort time:" << endl;
    for(int i=0; i<size; i++)
    {
        cout << "n=" << inputSize[i] << " best case=" << insertionBest[i] << " average case=" << insertionAverage[i] <<
             " worst case=" << insertionWorst[i] << endl;
    }

    cout << endl << endl << "Selection sort time:" << endl;
    for(int i=0; i<size; i++)
    {
        cout << "n=" << inputSize[i] << " best case=" << selectionBest[i] << " average case=" << selectionAverage[i] <<
             " worst case=" << selectionWorst[i] << endl;
    }

    return 0;

}

/*
int main()
{
    int n;
    cin >> n;
    int a[n];
    for(int i=0;i<n;i++)
    {
        a[i] = i+1;
    }

    cout << insertionSort(a,n);
    for(int i=0;i<n;i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}
*/
