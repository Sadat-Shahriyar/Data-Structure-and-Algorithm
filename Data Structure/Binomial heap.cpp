#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#define inf 999999

using namespace std;


class node
{
public:
    node *parent = nullptr;
    node *child = nullptr;
    node *sibling = nullptr;
    int value;
    int degree = 0;

    node(int value)
    {
        this->value = value;
    }
};


class BinomialHeap
{
private:
    node *head;
public:
    BinomialHeap()
    {
        head = nullptr;
    }

    node *findMin()
    {
        node *y = nullptr;
        if(head != nullptr)
        {
            node *x = head;
            int minimum = inf;

            while(x != nullptr)
            {
                if(x->value < minimum)
                {
                    minimum = x->value;
                    y = x;
                }

                x = x->sibling;
            }
        }

        return y;
    }

    node *getHead()
    {
        return head;
    }
    void setHead(node *value)
    {
        head = value;
    }

    void mergeRootList(BinomialHeap *h2)
    {
        node *head1 = this->getHead();
        node *head2 = h2->getHead();
        node *temp;
        node *tempHead;
        if(head1 == nullptr && head2 == nullptr){
            return;
        }
        else if(head1 == nullptr)
        {
            temp = tempHead = head2;
            head2 = head2->sibling;
        }

        else if(head2 == nullptr)
        {
            temp = tempHead = head1;
            head1 = head1->sibling;
        }

        else if(head1->degree > head2->degree)
        {
            temp = head2;
            tempHead = head2;
            head2 = head2->sibling;
            temp->sibling = nullptr;
        }
        else
        {
            temp = tempHead = head1;
            head1 = head1->sibling;
            temp->sibling = nullptr;
        }

        while(head1 != nullptr && head2 != nullptr)
        {
            if(head1->degree > head2->degree)
            {
                temp->sibling = head2;
                head2 = head2->sibling;
                temp = temp->sibling;
                temp->sibling = nullptr;
            }
            else
            {
                temp->sibling = head1;
                head1 = head1->sibling;
                temp = temp->sibling;
                temp->sibling = nullptr;
            }
        }
        if(head1 != nullptr )
        {
            temp->sibling = head1;
        }
        else if(head2 != nullptr )
        {
            temp->sibling = head2;
        }

        head = tempHead;
    }


    void binomialLink(node *child, node *parent)
    {
        child->parent = parent;
        child->sibling = parent->child;
        parent->child = child;
        parent->degree += 1;
    }

    void Union(BinomialHeap *h2)
    {
        mergeRootList(h2);
        h2->setHead(nullptr);
        delete h2;

        if(head == nullptr)
        {
            return;
        }

        node *current = head;
        node *prev = nullptr;
        node *next = head->sibling;

        while(next != nullptr)
        {
            if(current->degree != next->degree)
            {
                prev = current;
                current = next;
            }
            else if(next->sibling != nullptr && next->sibling->degree == current->degree)
            {
                prev = current;
                current = next;
            }
            else
            {
                if(current->value <= next->value)
                {
                    current->sibling = next->sibling;
                    binomialLink(next,current);
                }
                else
                {
                    if(prev == nullptr)
                    {
                        head = next;
                    }
                    else
                    {
                        prev->sibling = next;
                    }
                    binomialLink(current, next);
                    current = next;
                }
            }

            next = current->sibling;
        }

    }

    void Insert(int value)
    {
        node *newNode = new node(value);
        BinomialHeap *temp = new BinomialHeap();
        temp->setHead(newNode);
        this->Union(temp);
    }

    node *extractMin()
    {
        node *y = nullptr;
        node *prevY;
        if(head != nullptr)
        {
            node *x = head;
            node *prev = nullptr;
            int minimum = inf;

            while(x != nullptr)
            {
                if(x->value < minimum)
                {
                    minimum = x->value;
                    y = x;
                    prevY = prev;
                }
                prev = x;
                x = x->sibling;
            }


            if(prevY == nullptr)
            {
                this->setHead(y->sibling);
            }
            else
            {
                prevY->sibling = y->sibling;
                y->sibling = nullptr;
            }

            node *childY = y->child;

            node *temp = nullptr;
            node *temp1 = nullptr;

            while(childY != nullptr)
            {
                temp = childY;
                childY = childY->sibling;
                temp->sibling = temp1;
                temp1 = temp;
            }

            BinomialHeap *heap = new BinomialHeap();
            heap->setHead(temp1);

            this->Union(heap);

            y->child = nullptr;
            return y;

        }
        else
        {
            return nullptr;
        }
    }

    void printLevelOrder(node *root){
        if(root == nullptr) return;

        queue<node *> q;
        q.push(root);
        node *c;
        int level = 0;
        while(!q.empty()){
            int nodeCount = q.size();
            cout << "Level " << level << " : ";
            while(nodeCount > 0){
                node *node = q.front();

                cout << node->value << " ";
                q.pop();
                if(node->child != nullptr){
                    c = node->child;
                    while(c != nullptr){
                        q.push(c);
                        c = c->sibling;
                    }
                }
                nodeCount--;
            }
            cout << endl;
            level++;
        }
    }
    void print(){

        cout << "Printing Binomial Heap..." << endl;
        node *h = this->getHead();

        while(h != nullptr){
            cout << "Binomial Tree, B" << h->degree << endl;
            printLevelOrder(h);
            h = h->sibling;
        }
    }

};


int main(){
    BinomialHeap *heap = new BinomialHeap();

    ifstream file;
    file.open("in0.txt");
    char choice;
    int inp;
    int s = 0;
    node *result;
    while(!file.eof()){
        file >> choice;

        if(file.eof()){
            break;
        }
        if(choice == 'I'){
            file >> inp;
            heap->Insert(inp);
        }
        else if(choice == 'P'){
            heap->print();
        }
        else if(choice == 'E'){
            result = heap->extractMin();
            if(result != nullptr)
            {
                cout << "Extract-Min returned " << result->value << endl;
            }
            else
            {
                cout << "Empty heap" << endl;
            }
        }
        else if(choice == 'F'){
            result = heap->findMin();
            if(result != nullptr)
            {
                cout << "Find-Min returned " << result->value << endl;
            }
            else
            {
                cout << "Empty heap" << endl;
            }
        }

        else if(choice == 'U'){
            string str;
            getline(file, str);
            istringstream is(str);
            int n;
            BinomialHeap *heap2 = new BinomialHeap();
            while(is >> n){
                heap2->Insert(n);
            }
            heap->Union(heap2);
        }
        else break;
    }
    file.close();
    return 0;
}
