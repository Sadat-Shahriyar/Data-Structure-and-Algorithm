#include<iostream>
#include<cstdlib>

using namespace std;

template<class t>
class Queue
{
private:
    t *a;
    int length;
    int hoq,toq;
public:
    Queue()
    {
        a =(t *)malloc(10*sizeof(t));
        length = 10;
        hoq = 0;
        toq = 0;
    }

    bool empty()
    {
        if((toq-hoq) == 0)
            return true;
        else
            return false;
    }

    int size()
    {
        return (toq - hoq);
    }

    t &front()
    {
        if(empty())
        {
            cout << "queue is empty" << endl;
        }
        else
            return a[hoq];
    }

    t &rear()
    {
        if(empty())
        {
            cout << "queue is empty" << endl;
        }
        else
            return a[toq-1];
    }

    void enqueue(t x)
    {
        if(toq == length)
        {
            realloc(a,(length+10)*sizeof(t));
            length = length + 10;
        }

        a[toq++] = x;
    }
    void dequeue()
    {
        if(!empty())
        {
            a = a+1;
            toq--;
        }
        if(toq <= (length-10))
        {
            length = length-10;
            realloc(a,length*sizeof(t));
        }
    }
    ~Queue()
    {
        free(a);
    }
};


int main()
{
    int choice;
    int value;
    Queue<int> q;
    while(true)
    {
        cout << "what action do you want to perform?" << endl;
        cout << "1. enqueue, 2. dequeue, 3. is empty? 4. size? 5. front? 6. rear? 7.exit" << endl;
        cin >> choice;
        if(choice == 7)
            break;
        else if(choice == 1)
        {
            cout << "insert value = " ;
            cin >> value;
            q.enqueue(value);
        }
        else if(choice == 2)
        {
            q.dequeue();
        }
        else if(choice == 3)
        {
            if(q.empty())
                cout << "queue is empty" << endl;
            else
                cout << "queue is not empty" << endl;
        }
        else if(choice == 4)
        {
            cout << "size is = " << q.size() << endl;
        }
        else if(choice == 5)
        {
            cout << "front = " << q.front() << endl;
        }
        else if(choice == 6)
        {
            cout << "rear = " << q.rear() << endl;
        }
        cout << endl << endl;
    }

    return 0;

}


