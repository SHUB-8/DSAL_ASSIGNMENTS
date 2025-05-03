#include <bits/stdc++.h>
using namespace std;

class Node
{
    string key;
    int freq;
    Node *left, *right;
public:
    Node(string data, int val) : key(data), freq(val), left(nullptr), right(nullptr) {}
    friend class OBST;
};

class OBST
{
    Node *root;

public:
    OBST() : root(nullptr) {}

    Node *constructTree(vector<vector<int>> &rootMatrix, vector<pair<string, int>> &v, int i, int j)
    {
        if (i > j)
            return nullptr;
        int r = rootMatrix[i][j];
        Node *node = new Node(v[r].first, v[r].second);
        node->left = constructTree(rootMatrix, v, i, r - 1);
        node->right = constructTree(rootMatrix, v, r + 1, j);
        return node;
    }

    void createOBST(int n, vector<pair<string, int>> &v)
    {
        vector<vector<int>> cost(n, vector<int>(n, 0));
        vector<vector<int>> rootMatrix(n, vector<int>(n, 0));
        vector<int> prefixSum(n + 1, 0);

        for (int i = 0; i < n; i++)
            prefixSum[i + 1] = prefixSum[i] + v[i].second;

        for (int i = 0; i < n; i++)
            cost[i][i] = v[i].second, rootMatrix[i][i] = i;

        for (int len = 2; len <= n; len++)
        {
            for (int i = 0; i <= n - len; i++)
            {
                int j = i + len - 1;
                cost[i][j] = INT_MAX;

                for (int r = i; r <= j; r++)
                {
                    int leftCost = (r>i) ? cost[i][r-1] : 0;
                    int rightCost = (r<j) ? cost[r+1][j] : 0;
                    int totalCost = leftCost + rightCost + (prefixSum[j+1]-prefixSum[i]);
                    if (totalCost < cost[i][j])
                        cost[i][j] = totalCost, rootMatrix[i][j] = r;
                }
            }
        }
        root = constructTree(rootMatrix,v,0,n-1);
    }

    void inorder(Node *node)
    {
        if (!node)
            return;
        inorder(node->left);
        cout<<node->key<<" ";
        inorder(node->right);
    }

    void print(Node *root)
    {
        if(!root)
        {
            return;
        }
        cout<<"Root: "<<root->key<<" of Freq="<<root->freq<<endl;
        if(root->left)
        {
            cout<<"Root's left->"<<root->left->key<<":"<<root->left->freq<<endl;
        }
        if(root->right)
        {
            cout<<"Root's right->"<<root->right->key<<":"<<root->right->freq<<endl;
        }
        cout<<endl<<endl;
        print(root->left);
        print(root->right);
    }

    int total_cost(Node *root,int lvl)
    {
        if(root==nullptr)
        {
            return 0;
        }
        int count=0;
        count +=(root->freq)*lvl;
        return count + total_cost(root->left,lvl+1) + total_cost(root->right,lvl+1) ;
    }

    Node *getroot()
    {
        return root;
    }
};

int main()
{

    int n, m;
    cout << "Enter no. of keys: ";
    cin >> n;
    OBST o;
    vector<pair<string,int>> v(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter key: ";
        cin >> v[i].first;
        cout << "Enter its frequency: ";
        cin >> v[i].second;
    }
    o.createOBST(n, v);
    cout<<"Inorder Traversal of Keys: ";
    o.inorder(o.getroot());
    cout<<endl<<"Total Cost: "<<o.total_cost(o.getroot(),1)<<endl;
    o.print(o.getroot());
    return 0;
}