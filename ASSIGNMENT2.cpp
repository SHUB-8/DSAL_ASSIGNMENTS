// A dictionary stores keywords and its meanings. Provide facility for add-
// ing new keywords, deleting keywords, updating values of any entry.
// Provide facility to display whole data sorted in ascending/ Descending
// order. Also find how many maximum comparisons may require for finding
// any keyword. Use Binary Search Tree for implementation.

#include <iostream>
using namespace std;

class Node
{
    private:
    string data;
    string meaning;
    Node *left;
    Node *right;
    public:
    Node(string val1, string val2) : data(val1) , meaning(val2) , left(nullptr) , right(nullptr) {}
    friend class BST;
};

class BST
{
    private:
    Node *root;
    public:
    BST(): root(nullptr){}

    void insert(string val1, string val2)
    {
        if(root==nullptr)
        {
            root=new Node(val1,val2);
            return;
        }
        Node *current = root;
        Node *parent = nullptr;
        while (current != nullptr)
        {
            parent = current;
            if (val1 < current->data)
                current = current->left;
            else if (val1 > current->data)
                current = current->right;
            else
            {
                cout << "Duplicate entry not allowed!!!" << endl;
                return;
            }
        }
        if (val1< parent->data)
            parent->left = new Node(val1,val2);
        else
            parent->right = new Node(val1,val2);
    }

    void update(string val1, string val2)
    {
        if(root==nullptr)
        {
            cout<<"Binary Search Tree is Empty";
            return;
        }
        Node* p = root;
        while(p!=nullptr && p->data!=val1)
        {
            if(p->data > val1)
            {
                p=p->left;
            }
            else
            {
                p=p->right;
            }
        }
        if(p==nullptr)
        {
            cout<<"Entry is not present in BST";
        }
        p->meaning=val2;
        
    }

    void Inorder_trav(Node *root)
    {
        if(root == nullptr)
        {
            return;
        }
        Inorder_trav(root->left);
        cout<< root->data << ": "<<root->meaning<<endl;
        Inorder_trav(root->right);
    }

    void descend_ord(Node *root)
    {
        if(root == nullptr)
        {
            return;
        }
        descend_ord(root->right);
        cout<< root->data << ": "<<root->meaning<<endl;
        descend_ord(root->left);
    }

    Node *getroot()
    {
        return root;
    }

    Node *InSuccessor(Node *root)
    {
        if (root == nullptr || root->right == nullptr)
        {
            cout << "\nInorder Successor not present\n";
            return nullptr;
        }
        Node *p = root->right;
        while (p->left != nullptr)
        {
            p = p->left;
        }
        return p;
    }


    Node *Search_child(Node *root,string val)
    {
        Node *parent=nullptr;
        Node *child=root;
        while(child!=nullptr)
        {
            parent=child;
            if(child->data < val)
            {
                child=child->right;
            }
            else if(child->data >val)
            {
                child=child->left;
            }
            else
            {
                return child;
            }
        }
        if(child==nullptr)
        {
            cout<<"\nElement not present\n";
        }
        return nullptr;
    }

    Node *Search_parent(Node *root,string val)
    {
        Node *parent=nullptr;
        Node *child=root;
        while(child!=nullptr)
        {
            if(child->data < val)
            {
                parent=child;
                child=child->right;
            }
            else if(child->data >val)
            {
                parent=child;
                child=child->left;
            }
            else
            {
                return parent;
            }
        }
        if(child==nullptr)
        {
            cout<<"\nElement not present\n";
        }
        return parent;
    }


    void del(Node *root,string val)
    {
        Node *c = Search_child(root, val);
        if (c == nullptr)
        {
            cout << "\nElement not present\n";
            return;
        }

        Node *p = Search_parent(root, val);
        if (c->left == nullptr && c->right == nullptr)
        {
            if (p == nullptr)
            {
                this->root = nullptr;
            }
            else if (p->left == c)
            {
                p->left = nullptr;
            }
            else
            {
                p->right = nullptr;
            }
            delete c;
        }
        else if (c->left == nullptr || c->right == nullptr)
        {
            Node *child;
            if (c->left!=nullptr)
            {
                child = c->left;
            }
            else
            {
                child = c->right;
            }
            
            if (p == nullptr)
            {
                this->root = child;
            }
            else if (p->left == c)
            {
                p->left = child;
            }
            else
            {
                p->right = child;
            }
            delete c;
        }
        else
        {
            Node *successor = InSuccessor(c);
            string tempData = successor->data;
            string tempMeaning = successor->meaning;
            del(root,successor->data);
            c->data = tempData;
            c->meaning = tempMeaning;
        }
    }

    int maxcompar(Node *root)
    {
        if(root==nullptr)
        {
            return -1;
        }
        int lcompar = maxcompar(root->left);
        int rcompar = maxcompar(root->right);
        return max(lcompar,rcompar)+1;
    }

    int compar(Node *root,string val)
    {
        int count=0;
        Node *current=root;
        while(current!=nullptr)
        {
            if(current->data < val)
            {
                count+=1;
                current=current->right;
            }
            else if(current->data > val)
            {
                count+=1;
                current=current->left;
            }else
            {
                count+=1;
                return count;
            }
        }
        return -1;
    }

};


int main()
{
    BST B1;
    string val1,val2;
    int n;

    do
    {
        cout<<"\nEnter the Operation: ";
        cout<<"\n1.Add Word";
        cout<<"\n2.Update Meaning";
        cout<<"\n3.Delete Word";
        cout<<"\n4.Display Words in Ascending Order";
        cout<<"\n5.Display Words in Descending Order";
        cout<<"\n6.Maximum Comparisons";
        cout<<"\n7.Search element\n";
        cin>>n;

        switch(n)
        {
            case 1: cout<<"\nEnter the word:";
                    cin>>val1;
                    cout<<"Enter it's meaning:";
                    cin>>val2;
                    B1.insert(val1,val2);
                    cout<<"\n";
                    B1.Inorder_trav(B1.getroot());
                    break;
            
            case 2: cout<<"\nEnter the word for updating:";
                    cin>>val1;
                    cout<<"Enter it's updated meaning:";
                    cin>>val2;
                    B1.update(val1,val2);
                    cout<<"\n";
                    B1.Inorder_trav(B1.getroot());
                    break;
            
            case 3: cout<<"\nEnter the word to be deleted:";
                    cin>>val1;
                    B1.del(B1.getroot(),val1);
                    cout<<"\n";
                    B1.Inorder_trav(B1.getroot());
                    break;
            
            case 4: cout<<"\n";
                    B1.Inorder_trav(B1.getroot());
                    break;

            case 5: cout<<"\n";
                    B1.descend_ord(B1.getroot());
                    break;

            case 6: cout<<"\nMaximum Comparisons are :"<<B1.maxcompar(B1.getroot())<<endl;
                    break;
            
            case 7: cout<<"\nEnter word to be Searched: ";
                    cin>>val1;
                    if(B1.Search_child(B1.getroot(),val1))
                    {
                        cout<<"\nElement Present\n";
                        cout<<"\nElement found in "<<B1.compar(B1.getroot(),val1)<<" comparisions\n";
                    }
                    break;
        }
    }while(n>0 && n<8);
    return 0;
}