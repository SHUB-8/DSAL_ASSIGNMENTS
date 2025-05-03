#include <bits/stdc++.h>
using namespace std;

class Graph
{
private:
    int v;
    vector<int> arr;
    vector<vector<int>> mat;

public:
    Graph(int ver) : v(ver), arr(ver), mat(ver, vector<int>(ver, 0)) {}

    void add_nodes()
    {
        int m;
        for (int i = 0; i < v; i++)
        {
            cout << "Enter Vertice data: ";
            cin >> m;
            arr[i] = m;
        }
    }

    void add_edges(int val1, int val2, int weight)
    {
        auto it1 = find(arr.begin(), arr.end(), val1);
        auto it2 = find(arr.begin(), arr.end(), val2);

        if (it1 == arr.end() || it2 == arr.end())
        {
            cout << "Error: One or both vertices not found.\n";
            return;
        }

        int idx1 = distance(arr.begin(), it1);
        int idx2 = distance(arr.begin(), it2);
        mat[idx1][idx2] = weight;
        mat[idx2][idx1] = weight;
    }

    void printMatrix()
    {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void primMST()
    {
        vector<int> key(v, INT_MAX);
        vector<bool> inMST(v, false);
        vector<int> parent(v, -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        key[0] = 0;
        pq.push({0, 0});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u]) continue;
            inMST[u] = true;

            for (int v = 0; v < this->v; v++)
            {
                if (mat[u][v] && !inMST[v] && mat[u][v] < key[v])
                {
                    key[v] = mat[u][v];
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }
        int count=0;
        cout << "\nMinimum Spanning Tree (MST) Edges:\n";
        for (int i = 1; i < v; i++)
        {
            cout << arr[parent[i]] << " - " << arr[i] << " (Weight: " << mat[i][parent[i]] << ")\n";
            count+=mat[i][parent[i]];
        }
        cout<<"Minimum Cost is: "<<count<<endl;
    }
};

int main()
{
    int m,n,o,p,q;
    cout<<"Enter no. of vertices: ";
    cin>>n;
    Graph g(n);

    do
    {
        cout<<"\nEnter Operation: \n1.Add Vertice data \n2.Add Edge \n3.Display Graph \n4.Display MST \n";
        cin>>m;
        switch(m)
        {
            case 1: g.add_nodes();
                    break;
            
            case 2: cout<<"Enter first edge: ";
                    cin>>o;
                    cout<<"Enter second edge: ";
                    cin>>p;
                    cout<<"Enter weight:";
                    cin>>q;
                    g.add_edges(o,p,q);
                    break;
            
            case 3: g.printMatrix();
                    break;
            
            case 4: g.primMST();
                    break;
        }
    }while(m>0 && m<5);
    return 0;
}
