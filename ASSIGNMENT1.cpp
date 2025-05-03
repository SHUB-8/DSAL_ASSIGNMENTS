// Beginning with an empty binary tree, construct binary tree by inserting
// the values in the order given. After constructing a binary tree perform
// following operations on it-
// • Perform inorder, preorder and post order traversal
// • Change a tree so that the roles of the left and right pointers are swapped at every node
// • Find the height of tree
// • Copy this tree to another [operator=]
// • Count number of leaves, number of internal nodes.
// • Erase all nodes in a binary tree. (Implement both recursive and nonrecursive methods)

#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    int data;
    Node *left;
    Node *right;

public:
    Node(int val) : data(val),left(nullptr),right(nullptr){}
    friend class Binary_Tree;
};

class Binary_Tree
{
private:
    Node *root;
public:
    Binary_Tree() : root(nullptr) {}

    void addnode(Node*& root, int val)
    {
        if (root == nullptr)
        {
            root = new Node(val);
            return;
        }

        if (root->left == nullptr)
        {
            addnode(root->left, val);
        }
        else if (root->left!=nullptr && root->right == nullptr)
        {
            addnode(root->right, val);
        }
        else
        {
            addnode(root->left, val);
        }
    }

    void add(int data)
    {
        addnode(root,data);
    }

    void Inorder_trav(Node *root)
    {
        if(root == nullptr)
        {
            return;
        }
        Inorder_trav(root->left);
        cout<< root->data << " ";
        Inorder_trav(root->right);
    }

    void Preorder_trav(Node *root)
    {
        if(root==nullptr)
        {
            cout<<"Tree is Empty";
            return;
        }
        cout<< root->data << " ";
        Preorder_trav(root->left);
        Preorder_trav(root->right);
    }

    void Postorder_trav(Node *root)
    {
        if(root==nullptr)
        {
            return;
        }
        Postorder_trav(root->left);
        Postorder_trav(root->right);
        cout<< root->data<< " ";
    }

    Node *getroot()
    {
        return root;
    }

    int height(Node *root)
    {
        if(root==nullptr)
        {
            return -1;
        }
        
        int lheight = height(root->left);
        int rheight = height(root->right);

        return max(lheight,rheight)+1;
    }

    void swaptree(Node *root)
    {
        if(root==nullptr)
        {
            return;
        }
        swap(root->left,root->right);
        swaptree(root->left);
        swaptree(root->right);
    }

    int calculate_leaves(Node *root)
    {
        if(root==nullptr)
        {
            return 0;
        }
        if(root->left==nullptr && root->right==nullptr)
        {
            return 1;
        }
        return calculate_leaves(root->left)+calculate_leaves(root->right);
    }

    int internal_nodes(Node *root)
    {
        if(root==nullptr)
        {
            return 0;
        }
        if (root->left != nullptr || root->right != nullptr)
        {
            return internal_nodes(root->left) + internal_nodes(root->right) + 1;
        }
        return 0;
    }

    Node* copyTree(Node* val)
    {
        if (val == nullptr)
            return nullptr;

        Node* newNode = new Node(val->data);
        newNode->left = copyTree(val->left);
        newNode->right = copyTree(val->right);

        return newNode;
    }

    Binary_Tree& operator=(const Binary_Tree& other)
    {
        if (this == &other)  
            return *this;
        
        root = copyTree(other.root);
        return *this;
    }


    void deleteTree(Node*& root)
    {
        if (root == nullptr)
        {
            return;
        }
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
    
    void del()
    {
        deleteTree(root);
    }


    void Iterative_preorder(Node *root)
    {
        stack<Node*> s;
        s.push(root);
        while(!s.empty())
        {
            Node* top = s.top();
            s.pop();
            cout<<top->data<<" ";
            if(top->right!=nullptr)
            {
                s.push(top->right);
            }
            if(top->left!=nullptr)
            {
                s.push(top->left);
            }
        }
    }

    void inorder(Node *root)
    {
        stack<Node*> s;
        Node* current = root;
        while(current!=nullptr || !s.empty())
        {
            while(current!=nullptr)
            {
                s.push(current);
                current=current->left;
            }
            current=s.top();
            s.pop();
            cout<<current->data<<" ";
            current=current->right;
        }
    }

    void post_order(Node *root)
    {
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(root);
        while(!s1.empty())
        {
            Node* p = s1.top();
            s1.pop();
            s2.push(p);
            if(p->left!=nullptr)
            {
                s1.push(p->left);
            }
            if(p->right!=nullptr)
            {
                s1.push(p->right);
            }
        }
        while(!s2.empty())
        {
            cout<<s2.top()->data<<" ";
            s2.pop();
        }
    }
};

int main()
{
    Binary_Tree B;
    int n;
    do{
        cout<<"\nEnter your choice:";
        cout<<"\n1.Add Node to Tree ";
        cout<<"\n2.Traversal of Tree ";
        cout<<"\n3.Iterative Traversal ";
        cout<<"\n4.Height of Tree  ";
        cout<<"\n5.Swap Tree ";
        cout<<"\n6.Total Leaves and Internal Nodes of the Tree ";
        cout<<"\n7.Delete Tree ";
        cout<<"\n8.Copy Tree\n";
        cin>>n;
        switch(n)
        {
            case 1: int val;
                    cout<<"Enter the value:";
                    cin>>val;
                    B.add(val);
                    cout<<"\n";
                    break;
            
            case 2: cout<<"\nInorder Traversal: ", B.Inorder_trav(B.getroot());
                    cout<<"\nPreorder Traversal: ", B.Preorder_trav(B.getroot());
                    cout<<"\nPostorder Traversal: ", B.Postorder_trav(B.getroot());
                    cout<<"\n";
                    break;
            
            case 3: cout<<"\nNon-recursive Inorder Traversal: ", B.inorder(B.getroot());
                    cout<<"\nNon-recursive Preorder Traversal: ", B.Iterative_preorder(B.getroot());
                    cout<<"\nNon-recursive Postorder Traversal: ", B.post_order(B.getroot());
                    cout<<"\n";
                    break;
            
            case 4: cout<<"\nHeight of the Tree is: "<<B.height(B.getroot())<<endl;
                    break;
            
            case 5: cout<<"\nSwapped Tree is: ",B.swaptree(B.getroot()),B.Inorder_trav(B.getroot());
                    break;
            
            case 6: cout<<"\nTotal Leaves of the Tree are: "<<B.calculate_leaves(B.getroot());
                    cout<<"\nTotal Internal Nodes of the Tree are: "<<B.internal_nodes(B.getroot())<<endl;
                    break;

            case 7: B.del();
                    cout<<"\nBinary Tree deleted!!!";
                    break;

            case 8: Binary_Tree B1;
                    B1=B;
                    cout<<"\nInorder Traversal of new Tree: ",B1.Inorder_trav(B1.getroot());
                    break;
            
        }
    }while(n>0 && n<8);

    return 0;
}