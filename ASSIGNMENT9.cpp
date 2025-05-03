#include <bits/stdc++.h>
using namespace std;

class Node
{
    string key;
    string meaning;
    Node *left, *right;
    int height;

public:
    Node(string k, string m)
    {
        key = k;
        meaning = m;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

    friend class AVL;
};

class AVL
{
    Node *root;

public:
    AVL() : root(nullptr) {}

    int height(Node *n)
    {
        if (n == nullptr)
            return 0;
        return n->height;
    }

    int getBalance(Node *n)
    {
        if (!n)
            return 0;
        return height(n->left) - height(n->right);
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    void insert(string key, string meaning)
    {
        bool rotated = false;
        root = insert(root, key, meaning, rotated);
        if (rotated)
        {
            cout << "\nTree after rotation\n";
            display(root);
        }
    }


    Node* insert(Node* node, string key, string meaning, bool& rotated)
    {
        if (!node)
            return new Node(key, meaning);

        if (key < node->key)
            node->left = insert(node->left, key, meaning, rotated);
        else if (key > node->key)
            node->right = insert(node->right, key, meaning, rotated);
        else {
            node->meaning = meaning;
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 || balance < -1)
        {
            cout << "\nTree before rotation\n";
            display(root);
            cout << "\nImbalance at node: " << node->key << ", Balance Factor: " << balance << "\n";
        }

        if (balance > 1 && key < node->left->key)
        {
            cout << "Performing Right Rotation (LL Case) on " << node->key << "\n";
            rotated = true;
            return rightRotate(node);
        }

        if (balance < -1 && key > node->right->key)
        {
            cout << "Performing Left Rotation (RR Case) on " << node->key << "\n";
            rotated = true;
            return leftRotate(node);
        }

        if (balance > 1 && key > node->left->key)
        {
            cout << "Performing Left Rotation on " << node->left->key << "\n";
            node->left = leftRotate(node->left);
            cout << "Performing Right Rotation (LR Case) on " << node->key << "\n";
            rotated = true;
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            cout << "Performing Right Rotation on " << node->right->key << "\n";
            node->right = rightRotate(node->right);
            cout << "Performing Left Rotation (RL Case) on " << node->key << "\n";
            rotated = true;
            return leftRotate(node);
        }

        return node;
    }



    void deleteNode(string key)
    {
        root = deleteNode(root, key);
    }

    Node *deleteNode(Node *node, string key)
    {
        if (!node)
            return nullptr;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else
        {
            if (!node->left && !node->right)
                return nullptr;

            else if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;
                return temp;
            }

            Node *succ = inorderSuccessor(node);
            node->key = succ->key;
            node->meaning = succ->meaning;
            node->right = deleteNode(node->right, succ->key);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        if (balance > 1 && getBalance(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        if (balance < -1 && getBalance(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node *inorderSuccessor(Node *node)
    {
        Node *curr = node->right;
        while (curr && curr->left)
            curr = curr->left;
        return curr;
    }

    void search(string key)
    {
        int comparisons = 0;
        Node *temp = root;

        while (temp)
        {
            comparisons++;
            if (key < temp->key)
                temp = temp->left;
            else if (key > temp->key)
                temp = temp->right;
            else {
                cout << "Found: " << temp->key << " = " << temp->meaning << "\n";
                cout << "Comparisons: " << comparisons << "\n";
                return;
            }
        }
        cout << "Key not found!\n";
        cout << "Comparisons: " << comparisons << "\n";
    }

    void ascending(Node *node)
    {
        if (!node)
            return;
        ascending(node->left);
        cout << node->key << ": " << node->meaning << "\n";
        ascending(node->right);
    }

    void descending(Node *node)
    {
        if (!node)
            return;
        descending(node->right);
        cout << node->key << ": " << node->meaning << "\n";
        descending(node->left);
    }

    void display(Node *node)
    {
        if (!node)
            return;
        cout << "Key: " << node->key << ", Meaning: " << node->meaning << ", Balance Factor: " << getBalance(node) << endl;
        if (node->left)
            display(node->left);
        if (node->right)
            display(node->right);
    }

    Node *getroot()
    {
        return root;
    }
};

int main() {
    AVL tree;
    int opt;
    string key, meaning;

    do
    {
        cout << "\nAVL Dictionary Menu:"<<endl;
        cout << "1. Insert\n2. Delete\n3. Display\n4. Ascending\n5. Descending\n6. Search\n7. Exit\n";
        cin >> opt;
        cin.ignore();

        switch (opt)
        {
        case 1:
            cout << "Enter key: ";
            cin >> key;
            cin.ignore();
            cout << "Enter meaning: ";
            getline(cin, meaning);
            tree.insert(key, meaning);
            break;
        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            tree.deleteNode(key);
            break;
        case 3:
            tree.display(tree.getroot());
            break;
        case 4:
            cout << "\nAscending Order:\n";
            tree.ascending(tree.getroot());
            break;
        case 5:
            cout << "\nDescending Order:\n";
            tree.descending(tree.getroot());
            break;
        case 6:
            cout << "Enter key to search: ";
            cin >> key;
            tree.search(key);
            break;
        default:
            cout<<"Enter Valid Option!!!"<<endl;
            break;
        }
    }while(opt!=7);

    return 0;
}
