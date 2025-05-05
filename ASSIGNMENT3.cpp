#include <iostream>
using namespace std;

class Node
{
private:
    int data;
    int rt;
    int lt;
    Node *left;
    Node *right;

public:
    Node(int val) : data(val), left(nullptr), right(nullptr), rt(1), lt(1) {}
    friend class DTBST;
};

class DTBST
{
private:
    Node *root;

public:
    DTBST() : root(nullptr) {}

    void create(int val)
    {
        if (root == nullptr)
        {
            root = new Node(val);
            return;
        }

        Node *current = root;
        Node *parent = nullptr;

        while (current != nullptr)
        {
            parent = current;
            if (val < current->data)
            {
                if (current->lt == 1)
                {
                    Node *p = new Node(val);
                    p->left = current->left;
                    p->right = current;
                    current->left = p;
                    current->lt = 0;
                    p->lt = 1;
                    p->rt = 1;
                    return;
                }
                else
                {
                    current = current->left;
                }
            }
            else if (val > current->data)
            {
                if (current->rt == 1)
                {
                    Node *p = new Node(val);
                    p->right = current->right;
                    p->left = current;
                    current->right = p;
                    current->rt = 0;
                    p->rt = 1;
                    p->lt = 1;
                    return;
                }
                else
                {
                    current = current->right;
                }
            }
            else
            {
                return;
            }
        }

        Node *p = new Node(val);
        if (val < parent->data)
        {
            parent->left = p;
            parent->lt = 0;
            p->right = parent;
            p->rt = 1;
        }
        else
        {
            parent->right = p;
            parent->rt = 0;
            p->left = parent;
            p->lt = 1;
        }
    }

    Node *getroot()
    {
        return root;
    }

    void threaded_inorder(Node *root)
    {
        if (root == nullptr)
        {
            cout << "Binary Search Tree is Empty!!!\n";
            return;
        }

        Node *current = root;
        while (current->lt == 0)
        {
            current = current->left;
        }
        while (current != nullptr)
        {
            cout << current->data << " ";
            if (current->rt == 1)
            {
                current = current->right;
            }
            else
            {
                current = current->right;
                while (current!=nullptr && current->lt==0)
                {
                    current = current->left;
                }
            }
        }
    }

    void threaded_preorder(Node *root)
    {
        if(root == nullptr)
        {
            cout<<"Binary Search Tree is Empty!!!\n";
            return;
        }

        Node *current = root;
        cout<<current->data<<" ";
        while(current->lt == 0)
        {
            current=current->left;
            cout<<current->data<<" ";
        }
        while (current != nullptr)
        {
            if (current->rt ==1)
            {
                current=current->right;
            }
            else
            {
                current=current->right;
                cout<<current->data<<" ";
                while (current!=nullptr && current->lt == 0)
                {
                    current=current->left;
                    cout<<current->data<<" ";
                }
            }
        }
    }

    Node *Search_child(Node *root,int val)
    {
        Node *parent=nullptr;
        Node *child=root;
        while(child!=nullptr)
        {
            parent=child;
            if(child->data < val)
            {
                if(child->rt==0)
                {
                    child=child->right;
                }else{
                    return nullptr;
                }  
            }
            else if(child->data > val)
            {
                if(child->lt==0)
                {
                    child=child->left;
                }else{
                    return nullptr;
                } 
            }
            else
            {
                return child;
            }
        }
        return child;
    }

    Node *Search_parent(Node *root,int val)
    {
        Node *parent=nullptr;
        Node *child=root;
        while(child!=nullptr)
        {
            if(child->data < val)
            {
                parent=child;
                if(child->rt==0)
                {
                    child=child->right;
                }else{
                    child=nullptr;
                }
            }
            else if(child->data > val)
            {
                parent=child;
                if(child->lt==0)
                {
                    child=child->left;
                }else{
                    child=nullptr;
                }
            }
            else
            {
                return parent;
            }
        }
        return parent;
    }

    void del(Node *root, int val)
    {
        Node *c = Search_child(root, val);
        if (c == nullptr)
        {
            cout << "Element not present!!!\n";
            return;
        }
        Node *p = Search_parent(root, val);

        if (c->lt == 1 && c->rt == 1)
        {
            if (p == nullptr)
            {
                this->root = nullptr;
            }
            else if (c->data < p->data)
            {
                p->left = c->left;
                p->lt = 1;
            }
            else
            {
                p->right = c->right;
                p->rt = 1;
            }
            delete c;
        }
        else if (c->lt == 0 && c->rt == 1)
        {
            Node *child = c->left;
            if (p == nullptr)
            {
                this->root = child;
            }
            else if (c->data < p->data)
            {
                p->left = child;
            }
            else
            {
                p->right = child;
            }

            Node *temp = child;
            while (temp->rt == 0)
            {
                temp = temp->right;
            }
            temp->right = c->right;
            delete c;
        }
        else if (c->lt == 1 && c->rt == 0)
        {
            Node *child = c->right;
            if (p == nullptr)
            {
                this->root = child;
            }
            else if (c->data < p->data)
            {
                p->left = child;
            }
            else
            {
                p->right = child;
            }

            Node *temp = child;
            while (temp->lt == 0)
            {
                temp = temp->left;
            }
            temp->left = c->left;
            delete c;
        }
        else if (c->lt == 0 && c->rt == 0)
        {
            Node *successor = c->right;
            Node *successorParent = c;

            while (successor->lt == 0)
            {
                successorParent = successor;
                successor = successor->left;
            }

            c->data = successor->data;
            if (successor->rt == 1)
            {
                if (successorParent->left == successor)
                {
                    successorParent->left = successor->left;
                    successorParent->lt = 1;
                }
                else
                {
                    successorParent->right = successor->right;
                    successorParent->rt = 1;
                }
            }
            else
            {
                if (successorParent->left == successor)
                {
                    successorParent->left = successor->right;
                }
                else
                {
                    successorParent->right = successor->right;
                }
            }
            delete successor;
        }
    }


};

int main()
{
    DTBST b1;
    int n,m;
    do
    {
        cout<<"\nEnter Operation to be performed:";
        cout<<"\n1.Add Element";
        cout<<"\n2.Delete Element";
        cout<<"\n3.Inorder Traversal";
        cout<<"\n4.Preoerder Traversal\n";
        cin>>n;

        switch(n)
        {
            case 1: cout<<"Enter Element: ";
                    cin>>m;
                    b1.create(m);
                    break;
            
            case 2: cout<<"Enter Element: ";
                    cin>>m;
                    b1.del(b1.getroot(),m);
                    b1.threaded_inorder(b1.getroot());
                    break;
            
            case 3: cout <<"\nThreaded Inorder Traversal: ";
                    b1.threaded_inorder(b1.getroot());
                    cout<<"\n";
                    break;
            
            case 4: cout <<"\nThreaded Preorder Traversal: ";
                    b1.threaded_preorder(b1.getroot());
                    cout<<"\n";
                    break;
        }
    }while(n>0 && n<5);

    return 0;
}
