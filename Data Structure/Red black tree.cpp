#include<iostream>
#include<fstream>
#define red 1000
#define black 2000
#define NULL_VALUE -999999
using namespace std;

class node
{
public:
    node *parent = nullptr;
    node *left = nullptr;
    node *right = nullptr;
    int data;
    int color;

    node(int data)
    {
        this->data = data;
    }
    ~node()
    {
        if(parent)
            delete parent;
        if(left)
            delete left;
        if(right)
            delete right;
    }
};

class RBT
{
private:
    node *root = nullptr;
public:
    bool search(int key)
    {
        if(root == nullptr)
        {
            return false;
        }
        node *itr = root;
        while(itr->data != NULL_VALUE)
        {
            if(itr->data == key)
            {
                return true;
            }
            else if(key > itr->data)
            {
                itr = itr->right;
            }
            else
            {
                itr = itr->left;
            }
        }

        return false;
    }

    void leftRotate(node *t)
    {
        node *target = t;
        node *p = target->parent;
        node *right = target->right;

        target->right = right->left;
        right->left->parent = target;


        right->parent = p;
        if(p!= nullptr)
        {
            if(p->right == target)
            {
                p->right = right;
            }
            else
                p->left = right;
        }
        target->parent = right;
        right->left = target;

        if(target == root)
        {
            root = right;
        }
    }


    void rightRotate(node *t)
    {
        node *target = t;
        node *p = target->parent;
        node *left = target->left;

        target->left = left->right;
        left->right->parent = target;

        left->parent = p;
        if(p != nullptr)
        {
            if(p->right == target)
            {
                p->right = left;
            }
            else
            {
                p->left = left;
            }
        }


        target->parent = left;
        left->right = target;
        if(target == root)
        {
            root = left;
        }
    }

    void RBTinserFixUp(node *target)
    {
        if(target->parent == nullptr)
        {
            root->color = black;
            return;
        }
        else if(target->parent->parent == nullptr)
        {
            root->color = black;
            return;
        }
        else
        {
            while(target->parent != nullptr && target->parent->color == red )
            {
                if(target->parent == target->parent->parent->left)
                {
                    node *uncle = target->parent->parent->right;
                    if(uncle->color == red)
                    {
                        uncle->color = black;
                        target->parent->color = black;
                        target->parent->parent->color = red;
                        target = target->parent->parent;
                    }
                    else
                    {
                        if(target == target->parent->right)
                        {
                            target = target->parent;
                            leftRotate(target);
                        }
                        target->parent->color = black;
                        target->parent->parent->color = red;
                        rightRotate(target->parent->parent);
                    }
                }
                else
                {
                    node *uncle = target->parent->parent->left;
                    if(uncle->color == red)
                    {
                        uncle->color = black;
                        target->parent->color = black;
                        target->parent->parent->color = red;
                        target = target->parent->parent;
                    }
                    else
                    {
                        if(target == target->parent->left)
                        {
                            target = target->parent;
                            rightRotate(target);
                        }
                        target->parent->color = black;
                        target->parent->parent->color = red;
                        leftRotate(target->parent->parent);
                    }
                }

            }

            root ->color = black;
        }
    }

    void insert(int value)
    {
        node *newNode = new node(value);
        node *newNodeLeftChild = new node(NULL_VALUE);
        node *newNodeRightChild = new node(NULL_VALUE);
        newNode->right = newNodeRightChild;
        newNode->left = newNodeLeftChild;
        newNode->color = red;
        newNodeLeftChild->color = black;
        newNodeRightChild->color = black;
        newNodeLeftChild->parent = newNode;
        newNodeRightChild->parent = newNode;

        if(root == nullptr)
        {

            root = newNode;
            RBTinserFixUp(newNode);
        }
        else
        {
            bool present = search(value);
            if(!present)
            {
                node *tempRoot = root;

                while(tempRoot->data != NULL_VALUE)
                {
                    if(value > tempRoot->data)
                    {
                        tempRoot = tempRoot->right;
                    }
                    else{

                        tempRoot = tempRoot->left;
                    }

                }
                newNode->parent = tempRoot->parent;
                if(tempRoot == tempRoot->parent->left)
                {
                    tempRoot->parent->left = newNode;
                }
                else
                {
                    tempRoot->parent->right = newNode;
                }
                tempRoot->parent = nullptr;
                delete tempRoot;

                RBTinserFixUp(newNode);
            }
        }
        preOrder(root);
        if(root != nullptr) cout << endl;
    }

    node *successor(node *z){
        node *target = z;
        target = target->right;
        while(target->left->data != NULL_VALUE){
            target = target->left;
        }
        return target;
    }

    void RBTdeleteFixUp(node *target){
        while(target->color == black && target->parent != nullptr){

            if(target == target->parent->left){
                node *w = target->parent->right;
                if(w->color == red){
                    w->color = black;
                    target->parent->color = red;
                    leftRotate(target->parent);
                    w = target->parent->right;
                }
                if(w->color == black && w->right->color == black && w->left->color == black){
                    w->color = red;
                    target = target->parent;
                }
                else{
                    if(w->right->color == black && w->left->color == red){
                        w->left->color = black;
                        w->color = red;
                        rightRotate(w);
                        w = target->parent->right;
                    }

                    w->color = target->parent->color;
                    target->parent->color = black;
                    w->right->color = black;
                    leftRotate(target->parent);
                    target = root;
                }
            }
            else{
                node *w = target->parent->left;
                if(w->color == red){
                    w->color = black;
                    target->parent->color = red;
                    rightRotate(target->parent);
                    w = target->parent->left;
                }
                if(w->color == black && w->left->color == black && w->right->color == black){
                    w->color = red;
                    target = target->parent;
                }
                else{
                    if(w->left->color == black && w->right->color == red){
                        w->right->color = black;
                        w->color = red;
                        leftRotate(w);
                        w = target->parent->left;
                    }

                    w->color = target->parent->color;
                    target->parent->color = black;
                    w->left->color = black;
                    rightRotate(target->parent);
                    target = root;
                }
            }
        }
        target->color = black;
    }

    void deleteNode(int value)
    {
        node *temp = root;
        node *z = nullptr;
        while(temp->data != NULL_VALUE)
        {
            if(temp->data == value)
            {
                z = temp;
                break;
            }
            else if(value > temp->data)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }

        if(z!=nullptr)
        {

            node *y = nullptr;
            node *x = nullptr;
            if(z->right->data == NULL_VALUE || z->left->data == NULL_VALUE){
                y = z;
            }
            else y = successor(z);

            if(y->left->data != NULL_VALUE){
                x = y->left;
            }
            else{
                x = y->right;
            }
            x->parent = y->parent;
            if(y->parent != nullptr){
                if(y == y->parent->left){
                    y->parent->left = x;
                }
                else{
                    y->parent->right = x;
                }


            }
            else{
                if(x->data != NULL_VALUE){
                    root = x;
                }
                else root = nullptr;

            }

            if(y != z){
                z->data = y->data;
            }
            if(y->color == black){
                RBTdeleteFixUp(x);
            }

            y->parent == nullptr;
            y->left == nullptr;
            y->right == nullptr;
        }
        preOrder(root);
        if(root != nullptr) cout << endl;
    }

    void preOrder(node *target)
    {
        if(target != nullptr && target->data != NULL_VALUE)
        {
            if(target->color == black){
                cout << target->data << ":b" ;
            }
            else{
                cout << target->data << ":r";
            }

            if(target->left->data == NULL_VALUE && target->right->data != NULL_VALUE){
                cout << "()";
                cout << "(";
                preOrder(target->right);
                cout << ")";
            }
            else if(target->right->data == NULL_VALUE && target->left->data != NULL_VALUE){
                cout << "(";
                preOrder(target->left);
                cout << ")";
                cout << "()";
            }
            else if(target->left->data != NULL_VALUE && target->right->data != NULL_VALUE){
                cout << "(";
                preOrder(target->left);
                cout << ")";
                cout << "(";
                preOrder(target->right);
                cout << ")";
            }

            /*
            if(target->right->data != NULL_VALUE) cout << "(" ;
            preOrder(target->left);
            if(target->right->data != NULL_VALUE) cout << ")";



            if(target->left->data != NULL_VALUE) cout << "(" ;
            preOrder(target->right);
            if(target->left->data != NULL_VALUE) cout << ")"; */

        }

    }

};


int main(){
    RBT tree;
    ifstream file;
    file.open("input.txt");
    char choice;
    int nodeValue;
    while(!file.eof()){
        file >> choice >> nodeValue;

        if(choice == 'F'){
            bool present = tree.search(nodeValue);
            if(present) cout << "True" <<endl;
            else cout << "False" <<endl;
        }
        else if(choice == 'I'){
            tree.insert(nodeValue);
        }
        else if(choice == 'D'){
            tree.deleteNode(nodeValue);
        }
    }
}
