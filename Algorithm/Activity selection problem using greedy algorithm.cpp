#include<iostream>
#include<string>
#include<bits/stdc++.h>
using namespace std;


class activities
{
private:
    int startTime;
    int finishTime;
    string activityName;
public:
    void setStartTime(int time);
    void setFinishTime(int time);
    void setActivityName(string name);
    int getStartTime()
    {
        return startTime;
    }
    int getFinishTime()
    {
        return finishTime;
    }
    string getActivityName()
    {
        return activityName;
    }

};

void activities::setStartTime(int time)
{
    startTime = time;
}

void activities::setFinishTime(int time)
{
    finishTime=time;
}

void activities::setActivityName(string name)
{
    activityName = name;
}


void mergeActivities(activities a[],int start,int finish)
{
    int mid = (start+finish)/2;
    int i = start;
    int j = mid+1;
    activities temp[finish-start+1];
    int k = 0;
    while(i<=mid && j<=finish)
    {
        if(a[j].getFinishTime() < a[i].getFinishTime())
        {
            temp[k++] = a[j++];
        }
        else
        {
            temp[k++] = a[i++];
        }
    }

    while(i<=mid)
    {
        temp[k++] = a[i++];
    }
    while(j<=finish)
    {
        temp[k++] = a[j++];
    }

    k = 0;
    i = start;
    int S = finish-start+1;

    while(k<S)
    {
        a[i++] = temp[k++];
    }
}

void sortByFinishTime(activities a[],int start, int finish)
{
    if(start<finish)
    {
        int mid = (start+finish)/2;
        sortByFinishTime(a,start,mid);
        sortByFinishTime(a,mid+1,finish);
        mergeActivities(a,start,finish);
    }
}


int main()
{
    int n;
    cout << "number of activities: ";
    cin >> n;
    activities a[n];
    for(int i=0; i<n; i++)
    {
        //int x;
        //cin >> x;
        a[i].setStartTime(rand()%20);
        int x =  rand()%30;
        while(x<=a[i].getStartTime())
            x = rand()%30;

        //cin >> x;
        a[i].setFinishTime(x);
        string name = "a"+ to_string(i+1);
        a[i].setActivityName(name);
    }

    sortByFinishTime(a,0,n-1);

    cout << "activities: " << endl;
    for(int i=0; i<n; i++)
    {
        cout << a[i].getActivityName() << " " << a[i].getStartTime() << " " << a[i].getFinishTime() << endl;
    }

    int i=0;
    int counter = 1;
    for(int j=1;j<n;j++)
    {
        if(a[j].getStartTime() >= a[i].getFinishTime())
        {
            i=j;
            counter++;
        }
    }

    cout << "ans: " <<  counter << " activities"<< endl;

    activities ans[counter];
    ans[0] = a[0];
    int idx = 1;
    i=0;

    for(int j=1;j<n;j++)
    {
        if(a[j].getStartTime() >= a[i].getFinishTime())
        {
            ans[idx] = a[j];
            i=j;
            idx++;
        }
    }


    for(int i=0;i<counter;i++)
    {
        cout << ans[i].getActivityName() << " ";
    }

    return 0;

  /*  cout << "ans: " << endl;

    int totalCombinations = (int)pow(2,n);
    vector<activities> v;
    for(int i=0;i<totalCombinations;i++)
    {
        int b = i;
        for(int j=0;j<n;j++)
        {
            if(b&1)
            {
                v.push_back(a[j]);
            }
            b = b/2;
        }

        if(v.size()!=counter)
        {
            v.clear();
            continue;
        }

        else
        {
            bool ok = true;
            for(int j=0;j<counter-1;j++)
            {
                if(v[j+1].getStartTime() < v[j].getFinishTime())
                {
                    ok = false;
                    break;
                }
            }

            if(ok)
            {
                for(int j=0;j<counter;j++)
                {
                    cout << v[j].getActivityName() << " ";
                }
                cout << endl;
            }

            v.clear();
        }
    }



    return 0;
    */
}
