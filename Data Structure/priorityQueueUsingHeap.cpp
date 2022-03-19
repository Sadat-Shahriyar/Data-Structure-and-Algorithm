#include<iostream>
#include<cstdlib>
using namespace std;


class pQueue
{
    int a[1000];
    int length;
    int tail;
public:
    pQueue()
    {
        //a = (int*)malloc(10);
        //length=10;
        tail = 1;
        a[0]=0;
    }

    int leftIndex(int i)
    {
        return 2*i;
    }
    int rightIndex(int i)
    {
        return 2*i+1;
    }

    int parentIndex(int i)
    {
        return i/2;
    }

    void heapify(int i)
    {
        /*

        int left = leftIndex(i);
        int right = rightIndex(i);
        int maximum = a[i];
        int changedIndex;
        bool changed = false;
        int temp;

        if(left>a[0] && right> a[0])
            return;

        else if(right > a[0])
        {
            temp = a[left];
            a[left]=a[i];
            a[i]=temp;
            changedIndex = left;
            changed = true;
        }

        else
        {
            if(maximum<a[left])
            {
                changedIndex = left;
                maximum = a[left];
            }
            if(maximum<a[right])
            {
                changedIndex = right;
                maximum = a[right];
            }
            if(maximum!= a[i])
            {
                temp = a[changedIndex];
                a[changedIndex] = a[i];
                a[i] = temp;
                changed = true;

            }


            if(changed)
            {
                heapify(changedIndex);
            }
        }
*/

        int left = leftIndex(i);
        int right = rightIndex(i);
        int maximum;
        if(left <= a[0] && a[left]>a[i])
        {
            maximum = left;
        }
        else maximum = i;

        if(right<=a[0] && a[right]>a[maximum])
        {
            maximum = right;
        }

        if(maximum != i)
        {
            int temp = a[i];
            a[i] = a[maximum];
            a[maximum] = temp;
            heapify(maximum);
        }

    }

    void buildHeap()
    {
        int l = a[0];
        l = l/2;
        for(int i=l;i>0;i--)
        {
            heapify(i);
        }
    }

    void upwardTransition(int i)
    {
        int parent = parentIndex(i);
        if(parent < 1)
            return;
        int temp;
        if(a[parent]<a[i])
        {
            temp = a[parent];
            a[parent] = a[i];
            a[i] = temp;
            upwardTransition(parent);
        }
    }

    void insert(int x)
    {
       /* if(tail==length)
        {
            length = length+10;
            realloc(a,length);
        } */
        a[tail++] = x;
        a[0]++;
        upwardTransition(tail-1);
    }
    int FindMax()
    {
        return a[1];
    }

    int ExtractMax()
    {
        int temp = a[1];
        if(tail>1 && a[0]>0)
        {
            tail--;
            a[0]--;
            a[1] = a[tail];
            heapify(1);
        }
        return temp;
    }

    void IncreaseKey(int i, int newKey)
    {
        a[i] = newKey;
        upwardTransition(i);
    }

    void DecreaseKey(int i, int newKey)
    {
        a[i] = newKey;
        heapify(i);
    }

    void print()
    {
        for(int i=1;i<tail;i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
};


int main()
{
    pQueue q;
    int ch;
    int value,index;
    while(1)
    {
        cout << "1.insert 2.Find Max 3.Extract Max 4.Increase Key 5.Decrease key 6.Print 7. Exit" << endl;
        cin >> ch;
        if(ch==1)
        {
            cout << "enter value= " ;
            cin >> value;
            q.insert(value);
        }
        else if(ch==2)
        {
            cout << "Maximum value = " << q.FindMax() << endl;
        }
        else if(ch==3)
        {
            cout << "Extracted maximum value = " << q.ExtractMax() << endl;
        }

        else if(ch==4)
        {
            cout << "insert position = ";
            cin >> index;
            cout << "insert new key = " ;
            cin >> value;
            q.IncreaseKey(index,value);
        }
        else if(ch==5)
        {
            cout << "insert position = ";
            cin >> index;
            cout << "insert new key = " ;
            cin >> value;
            q.DecreaseKey(index,value);
        }

        else if(ch==6)
        {
            q.print();
        }

        else if(ch==7)
        {
            break;
        }
    }

    return 0;
}

/*
int main()
{
    pQueue q;
    int n;
    cin >> n;
    int x;

    for(int i=0;i<n;i++)
    {
        cin >> x;
        q.insert(x);
    }

    q.print();

    return 0;
}
*/
