#include<iostream>

using namespace std;

class node
{
public:
    int data;
    node *left = NULL;
    node *right = NULL;
    node *parent = NULL;

    node(int data)
    {
        this->data = data;
    }

};

class tree
{
public:
    bool search(int a,node *root)
    {
        if(root == NULL)
            return false;
        else if(root->data == a)
        {
            return true;
        }

        else if(a < root->data)
        {
            return search(a,root->left);
        }
        else
            return search(a,root->right);
    }



    node *insert(node *insertValue, node *root,bool firstTime = true)
    {
        node *y = NULL;
        node *x = root;
        node *r = root;
        bool present = false;
        if(firstTime)
        {
            int a = insertValue->data;
            if(search(a,r))
                present = true;
        }

        if(!present)
        {
            while(x!=NULL)
            {
                y = x;
                if(insertValue->data < x->data)
                    x = x->left;
                else
                    x = x->right;
            }

            if(y==NULL)
            {
                root = insertValue;
            }
            else if(insertValue->data < y->data)
            {
                y->left = insertValue;
                insertValue->parent = y;
            }
            else
            {
                y->right = insertValue;
                insertValue->parent = y;
            }

        }
        return root;

    }

    void inOrder(node *root)
    {
        if(root!=NULL)
        {
            inOrder(root->left);
            cout << root->data << " ";
            inOrder(root->right);
        }
    }

    void preOrder(node *root)
    {
        if(root!=NULL)
        {
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    node *minimum(node *root)
    {
        node *r = root;
        while(r->left!=NULL)
        {
            r = r->left;
        }

        return r;
    }

    node *maximum(node *root)
    {
        node *r = root;
        while(r->right != NULL)
        {
            r = r->right;
        }
        return r;
    }

    node *Transplant(node *root,node *previous, node *newNode)
    {

        if(root == NULL)
        {
            root = newNode;
        }
        else if(root->data == previous->data)
        {
            root = newNode;
        }

        else if(previous == previous->parent->right)
        {
            previous->parent->right = newNode;
        }
        else if(previous == previous->parent->left)
        {
            previous->parent->left = newNode;
        }

        if(newNode!=NULL) newNode->parent = previous->parent;

        return root;
    }

    node *Delete(node *root, int value)
    {
        node *r = root;
        bool present = false;
        while(r!=NULL)
        {
            if(r->data == value)
            {
                present = true;
                break;
            }
            else if(value < r->data)
            {
                r = r->left;
            }
            else
                r = r->right;
        }


        if(present)
        {
            if(r->right == NULL)
            {
                root = Transplant(root,r,r->left);
            }

            else if(r->left == NULL)
            {
                root = Transplant(root,r,r->right);
            }

            else
            {
                node *successor = minimum(r->right);
                if(successor->parent == r)
                {
                    successor->parent->right = NULL;
                    root = Transplant(root,r,successor);
                    successor->left = r->left;
                    successor->left->parent = successor;
                }

                else
                {
                    successor->parent->left = NULL;
                    root = Transplant(root,r,successor);
                    successor->left = r->left;
                    successor->right = r->right;
                    successor->left->parent = successor;
                    successor->right->parent = successor;
                }
            }
        }

        return root;

    }

};


void pointer(int *x)
{
    x = new int(1000);
}

int main()
{
    node *root = NULL;
    node *temp = NULL;
    tree t;
    int choice;
    int value;
    while(true)
    {
        cout << "what action do you want to perform?" << endl;
        cout << "1. insert 2. delete 3. search 4.inorder traversal 5.preorder traversal 6. exit" << endl;

        cin >> choice ;
        if(choice == 1)
        {
            cout << "insert value = ";
            cin >> value;
            temp = new node(value);
            root = t.insert(temp,root);
        }
        else if(choice == 2)
        {
            cout << "insert value = " ;
            cin >> value;
            root = t.Delete(root,value);
        }

        else if(choice == 3)
        {
            cin >> value;
            temp = root;
            if(t.search(value,temp)) cout << value << " is in the binary tree" << endl;
            else cout << value << " is not in the tree" << endl;
        }
        else if(choice == 4)
        {
            temp = root;
            t.inOrder(temp);
            cout << endl;
        }

        else if(choice == 5)
        {
            temp = root;
            t.preOrder(temp);
            cout << endl;
        }

        else if(choice == 6)
        {
            break;
        }
    }

    return 0;

}




/*
int main()
{
    node *root = NULL;
    node *value = new node(7);

    node *value2 = new node(10);

    node *value3 = new node(2);


    node *value4 = new node(4);


    node *value5 = new node(1);

    node *value6 = new node(15);
    node *value7 = new node(20);

    node *value8 = new node(3);

    node *value9 = new node(5);
    node *value10 = new node(9);
    node *value11 = new node(8);

    tree t;
    root = t.insert(value,root,false);
    root = t.insert(value2,root,false);
    root = t.insert(value3,root,false);
    root = t.insert(value4,root,false);
    root = t.insert(value5,root,false);
    root = t.insert(value6,root,false);
    root = t.insert(value7,root,false);
    root = t.insert(value8,root,false);
    root = t.insert(value9,root,false);
    root = t.insert(value10,root,false);
    root = t.insert(value11,root,false);
    root = t.insert(value11,root);
   // root = t.insert(value11,root,false);


   if(t.search(3,root)) cout << "yes" << endl;
   t.inOrder(root);

    //root = t.Delete(root,7);
    //root = t.Transplant(root,value,value6);

    // node *x = t.maximum(root);

    //t.inOrder(root);
    //cout << x->data << endl;
   // t.inOrder(root);

    return 0;
}

*/




/*
int main()
{
    node *root = new node;
    root->data = 5;

    node *leftChild = new node;
    leftChild->data = 4;
    root->left = leftChild;

    node *rightChild = new node;
    rightChild->data = 10;
    root->right = rightChild;


    node *leftchild1 = new node;
    leftchild1->data = 2;
    leftChild->left = leftchild1;

    node *leftchild2 = new node;
    leftchild2->data = 3;
    leftchild1->right = leftchild2;

    node *leftchild3 = new node;
    leftchild3->data = 1;
    leftchild1->left = leftchild3;

    node *rightChild1 = new node;
    rightChild1->data = 7;
    rightChild->left = rightChild1;

    rightChild->right = new node;
    rightChild->right->data = 15;

    cout << rightChild << endl;

    node *insertValue = new node;
    insertValue->data = 8;


    tree t;


    t.insert(8,root,true);

    if(t.search(8,root)) cout << "4 is present" << endl;
    else cout << "4 is not present" << endl;

    t.inOrder(root);
    cout << endl;

    t.preOrder(root);

}


 node *Delete(node *root, int deleteValue)
    {
        node *r = root;
        bool present = false;
        while(r!=NULL)
        {
            if(r->data == deleteValue)
            {
                present = true;
                break;
            }

            else if(deleteValue < r->data)
            {
                r = r->left;
            }
            else
                r = r->right;
        }
        if(present)
        {

            if(r->right == NULL)
            {
                root = Transplant(root,r,r->left);
            }

            else if(r->left == NULL)
            {
                root = Transplant(root,r,r->right);
            }

            else
            {
                node *r1 = minimum(r->right);
                if(r1->parent == r)
                {
                    r1->right = r->right;
                    r1->parent = r->parent;
                    if(r->parent->left == r)
                    {
                        r->parent->left = r1;
                    }
                    else
                        r->parent->right = r1;
                }

                else
                {
                    root = Transplant(root,r,r1);
                    r1->right = r->right;
                    r1->left = r->left;
                }
            }
        }

    }



        node *Transplant(node *root, node *previous, node *newNode)
    {
        if(newNode != NULL)
        {
            if(root == NULL)
            {
                root = newNode;
            }
            else if(root == previous)
            {
                //cout << "ulala";
                root = newNode;
            }

            else if(previous == previous->parent->left)
            {
                previous->parent->left = newNode;
            }

            else if(previous == previous->parent->right)
            {
                previous->parent->right = newNode;
            }

            newNode->parent = previous->parent;

        }

        return root;
    }

    void insert(int a, node *root,bool firstTime)
       {
           bool present = false;
           if(firstTime)
           {
               if(search(a,root)) present = true;
           }

           if(!present)
           {
              // cout << "ulala" << endl;
               if(root == NULL)
               {
                   //cout << root << endl;
                   root = new node;
                   //cout << root << endl;
                   root->data = a;
                   //cout << root->data << endl;
               }
               else if(a < root->data)
               {
                   insert(a,root->left,false);
               }
               else if(a > root->data)
               {
                   insert(a,root->right,false);
               }
           }
       }

*/
