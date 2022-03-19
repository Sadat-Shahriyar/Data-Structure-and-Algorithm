#include<iostream>
#include<bits/stdc++.h>
#include<ctime>
#include<sys/time.h>
#include<chrono>
using namespace std;

long long int inputSize[] = {10,100,200,500,1000,2000,5000,10000};


int main()
{

    long long int n,key;
    double timeTaken ;
    double linearTime[8];
    double binaryTime[8];
    double linearTimeSum=0.0,binaryTimeSum=0.0;
    for(int x=0; x<8; x++)
    {
        n = inputSize[x];
        long long int a[n];
        for(long long int i=0 ; i<n; i++)
        {
            a[i] = rand()%10000;
        }
        sort(a,a+n);


        for(long long int j=0; j<5; j++)
        {
            key = rand()%10000;

            //linear search
            //time_t linearTime1 = time(0);
            auto start = std::chrono::system_clock::now();
            for(long long int i=0; i<n; i++)
            {
                cout <<"";
                if(a[i]==key)
                    break;

            }
            auto finish = std::chrono::system_clock::now();

            timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();


            linearTimeSum += timeTaken;
            timeTaken = 0;


            //binary search
            long long int l=0,r=n-1,mid;
            start = std::chrono::system_clock::now();
            while(l<=r)
            {
                cout << "";
                mid = (l+r)/2;
                if(a[mid] == key)
                {
                    cout << "";
                    break;
                }
                else
                {
                    if(key > a[mid])
                    {
                        cout << "";
                        l = mid+1;
                    }
                    else
                    {
                        cout << "";
                        r = mid-1;
                    }

                }
            }
            finish = std::chrono::system_clock::now();
            timeTaken = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>)(finish-start).count();

            binaryTimeSum += timeTaken;
            timeTaken = 0;

        }
        linearTime[x] = linearTimeSum/5.0;
        binaryTime[x] = binaryTimeSum/5.0;
        linearTimeSum = 0.0;
        binaryTimeSum = 0.0;


    }
    for(long long int i =0;i<8;i++)
    {
        cout << "n=" << inputSize[i] << " " << "time for linear search=" << linearTime[i] << " time for binary search=" << binaryTime[i] << endl;
    }

}
