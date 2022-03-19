#include<iostream>
#include<cstdlib>
using namespace std;

template<class t>
class Stack
{
private:
    t *a;
    int length;
    int tos;
public:
    Stack()
    {
        a = (t *)malloc(10*sizeof(t));
        length = 10;
        tos = 0;
    }
    bool empty()
    {
        if(tos==0) return true;
        else return false;
    }

    int size()
    {
        return tos;
    }

    t &top()
    {
        if(empty())
            cout << "stack is empty" << endl;
        else
        {
            return a[tos-1];
        }
    }

    void push(t x)
    {
        if(tos >= length)
        {
            a = (t *)realloc(a,(length+10)*sizeof(t));
            length = length + 10;
        }

        a[tos++] = x;
    }

    void pop()
    {
        if(!empty())
            tos--;
        if(tos <= (length-10))
        {
            a = (t *)realloc(a,(length-10)*sizeof(t));
            length = length - 10;
        }
    }

    ~Stack()
    {
        free(a);
    }

};


int main()
{
    int choice;
    int value;
    bool Break = false;
    Stack<int> s;
    while(true)
    {
        cout << "what action do you want to perform?" << endl;
        cout << "1.push 2.pop 3.top 4.is empty? 5.size 6.exit" << endl;
        cin >> choice;
        switch(choice)
        {
        case 1:
            cout << "enter value = " ;
            cin >> value;
            s.push(value);
            break;
        case 2:
            s.pop();
            break;
        case 3:
            cout << s.top() << endl;
            break;
        case 4:
            if(s.empty()) cout << "stack is empty" << endl;
            else cout << "stack is not empty" << endl;
            break;
        case 5:
            cout << "size = " << s.size() << endl;
            break;
        case 6:
            Break = true;
            break;
        }
        if(Break) break;
        cout << endl << endl;
    }

    return 0;

}


















