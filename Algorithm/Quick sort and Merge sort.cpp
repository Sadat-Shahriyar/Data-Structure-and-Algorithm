#include <cstdio>
#include<iostream>
#include<cstdlib>
#include<chrono>
using namespace std;

void merge(int a[],int s,int e)
{
    int mid = s+ (e-s)/2;
    int i=s;
    int j = mid + 1;
    int temp[e-s];
    int k = 0;
    while(i<=mid && j<=e)
    {
        if(a[i]<a[j])
        {
            temp[k++] = a[i++];
        }
        else
            temp[k++] = a[j++];
    }

    while(i<=mid)
    {
        temp[k++] = a[i++];
    }
    while(j<=e)
    {
        temp[k++] = a[j++];
    }
    i=s;
    for(j=0; j<k; j++)
    {
        a[i++] = temp[j];
    }
}

void mergeSort(int a[],int s,int e)
{
    if(s<e)
    {
        int mid = s + (e-s)/2;
        mergeSort(a,s,mid);
        mergeSort(a,mid+1,e);
        merge(a,s,e);
    }
}

int pivotIndex(int a[],int s,int e)
{
    int pivot = a[e];
    int pIndex = s;
    for(int i=s; i<e; i++)
    {
        if(a[i]<pivot)
        {
            int temp = a[pIndex];
            a[pIndex] = a[i];
            a[i] = temp;
            pIndex++;
        }
    }

    int temp = a[pIndex];
    a[pIndex] = a[e];
    a[e] = temp;

    return pIndex;
}

void quickSort(int a[],int s,int e)
{
    if(s<e)
    {
        int pivot = pivotIndex(a,s,e);
        quickSort(a,s,pivot-1);
        quickSort(a,pivot+1,e);
    }
}

int main()
{
    int choice, n,k;
    double timeTaken;
    int *a = nullptr;
    bool Break = false;
    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quick sort\n");
        printf("6. Print array\n");
        cout << "7. exit" << endl;;
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            if(a!=nullptr)
                delete []a;
            a = new int[n];
            for(int i=0; i<n; i++)
            {
                a[i] = rand()%100;
            }
            break;

        case 2:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            if(a!=nullptr)
                delete []a;
            a = new int[n];
            for(int i = 0; i<n; i++)
            {
                a[i] = i+1;
            }
            break;

        case 3:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            if(a!=nullptr)
                delete []a;
            a = new int[n];
            k = n;
            for(int i = 0; i<n; i++)
            {
                a[i] = k--;
            }
            break;

        case 4:
            if(a==nullptr)
                cout << "please insert elements in the array first" << endl;
            else
            {
                auto start = std::chrono::system_clock::now();
                printf("Applying merge sort\n");
                mergeSort(a,0,n-1);
                auto finish = std::chrono::system_clock::now();
                timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();
                printf("Time taken to finish: %lf nanoseconds\n",timeTaken);
            }
            break;

        case 5:
            if(a==nullptr)
                cout << "please insert elements in the array first" << endl;
            else
            {
                auto start = std::chrono::system_clock::now();
                printf("Applying quick sort\n");
                quickSort(a,0,n-1);
                auto finish = std::chrono::system_clock::now();
                timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();
                printf("Time taken to finish: %lf nanoseconds\n",timeTaken);
            }
            break;

        case 6:
            printf("Array\n");
            for(int i=0; i<n; i++)
            {
                cout << a[i] << " ";
            }
            cout << endl;
            break;
        case 7:
            Break = true;
            break;
        }
        if(Break)
            break;
    }
    if(a!=nullptr)
        delete []a;
    return 0;

}


/*
int main()
{
    int n;
    cin >> n;
    int a[n];
    for(int i = 0;i<n;i++)
    {
        a[i] = rand()%100;
    }

    quickSort(a,0,n-1);

    for(int i=0;i<n;i++)
    {
        cout << a[i] << " ";
    }
    return 0;
}

*/
