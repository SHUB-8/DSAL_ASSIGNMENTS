
#include <bits/stdc++.h>
using namespace std;

class Node
{
    private:
    string city;
    bool visit;
    vector <Node*> adj;
    public:
    Node(string val) : city(val) , visit(false) {}
    friend class Graph;
};  

class Graph
{
    private:
    vector <Node*> v;
    public:
    Graph() {}

    void add_node(string val)
    {
        Node *temp = new Node(val);
        v.push_back(temp);
    }

    void add_edge(string from, string to)
    {
        Node* fromNode = nullptr;
        Node* toNode = nullptr;
        
        for (auto i : v)
        {
            if (i->city == from)
                fromNode = i;
            if (i->city == to)
                toNode = i;
        }

        if (fromNode && toNode)
        {
            fromNode->adj.push_back(toNode);
            toNode->adj.push_back(fromNode);
        }
        else
        {
            cout << "Error: One or both nodes not found!" << endl;
        }
    }

    void display()
    {
        for (auto node : v)
        {
            cout << node->city << " City is connected to: ";
            for (auto adjNode : node->adj)
            {
                cout << adjNode->city<< " ";
            }
            cout << endl;
        }
    }

    void bfs_trav()
    {
        if(v.empty())
        {
            cout<<"Graph has 0 nodes!!!";
            return;
        }

        queue<Node*> q;
        for(auto i : v)
        {
            if (!i->visit)
            {
                q.push(i);
                i->visit = true;

                while (!q.empty())
                {
                    Node* curr = q.front();
                    q.pop();
                    cout << curr->city << " -> ";
                    for (auto neighbor : curr->adj)
                    {
                        if (!neighbor->visit)
                        {
                            neighbor->visit = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        cout<<" END \n";
        for (auto node : v)
        {
            node->visit = false;
        }
    }

    void dfs_trav()
    {
        if(v.empty())
        {
            cout<<"Graph has 0 nodes!!!";
            return;
        }

        stack<Node*> s;
        for(auto i : v)
        {
            if(!i->visit)
            {
                s.push(i);
                i->visit=true;

                while (!s.empty())
                {
                    Node* curr = s.top();
                    s.pop();
                    cout << curr->city << " -> ";
                    for (auto neighbor : curr->adj)
                    {
                        if (!neighbor->visit)
                        {
                            neighbor->visit = true;
                            s.push(neighbor);
                        }
                    }
                }
            }
        }
        cout<<" END \n";
        for (auto node : v)
        {
            node->visit = false;
        }
    }

    void degree()
    {
        for (auto i : v)
        {
            cout<<"Degree of Vertice "<<i->city<<" is: "<<i->adj.size()<<endl;
        }
    }
};

int main()
{
    Graph g;
    int n;
    string s1;
    string s2;
    do{
        cout<<"\nEnter Operation: \n1.Add Node \n2.Add Edge \n3.Display Graph \n4.BFS Traversal \n5.DFS Traversal \n6.Find Degree of a Vertice \n";
        cin>>n;
        switch(n)
        {
            case 1: cout<<"Enter the City: ";
                    cin>>s1;
                    g.add_node(s1);
                    break;
            
            case 2: cout<<"Enter first city: ";
                    cin>>s1;
                    cout<<"Enter second city: ";
                    cin>>s2;
                    g.add_edge(s1,s2);
                    break;
            
            case 3: cout<<"Graph:\n";
                    g.display();
                    break;
            
            case 4: cout<<"BFS Traversal: ";
                    g.bfs_trav();
                    break;

            case 5: cout<<"DFS Traversal: ";
                    g.dfs_trav();
                    break;
            
            case 6: g.degree();
                    break;
        }
    }while(n>0 && n<7);
    return 0;
}