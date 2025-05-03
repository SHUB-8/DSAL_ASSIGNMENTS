#include <bits/stdc++.h>
using namespace std;

class OBST
{
public:
    int n;
    vector<float> p, q;
    vector<vector<float>> wt, c;
    vector<vector<int>> r;

    void inputProbabilities()
    {
        cout << "\nEnter the number of keys: ";
        cin >> n;
        p.resize(n + 1);
        q.resize(n + 1);
        wt.assign(n + 1, vector<float>(n + 1, 0));
        c.assign(n + 1, vector<float>(n + 1, 0));
        r.assign(n + 1, vector<int>(n + 1, 0));

        cout<<"\nEnter the probability for successful search:\n";
        for(int i = 1; i <= n; i++)
        {
            cout<<"p["<<i<<"]: ";
            cin>>p[i];
        }

        cout<<"\nEnter the probability for unsuccessful search:\n";
        for(int i = 0; i <= n; i++){
            cout<<"q["<<i<<"]: ";
            cin>>q[i];
        }
    }

    void constructOBST()
    {
        for(int i=0; i<n; i++)
        {
            c[i][i] = 0.0;
            r[i][i] = 0;
            wt[i][i] = q[i];
            wt[i][i+1] = q[i] + q[i+1] + p[i+1];
            c[i][i+1] = wt[i][i+1];
            r[i][i+1] = i+1;
        }
        c[n][n] = 0.0;
        r[n][n] = 0;
        wt[n][n] = q[n];

        for(int length = 2; length <= n; length++)
        {
            for(int i=0; i<=n-length; i++)
            {
                int j = i + length;
                wt[i][j] = wt[i][j - 1] + p[j] + q[j];
                c[i][j] = FLT_MAX;
                for (int k = i + 1; k <= j; k++)
                {
                    float cost = c[i][k - 1] + c[k][j];
                    if (cost < c[i][j])
                    {
                        c[i][j] = cost;
                        r[i][j] = k;
                    }
                }
                c[i][j] += wt[i][j];
            }
        }
        cout<<"\nOptimal BST Constructed Successfully!";
        cout<<"\nMinimum Cost of OBST: "<<c[0][n];
        cout<<"\nRoot of OBST: "<<r[0][n]<<endl;
    }

    void printTree(int left, int right)
    {
        if (left >= right)
            return;

        if (r[left][r[left][right] - 1] != 0)
            cout << "\n Left child of " << r[left][right] << " :: " << r[left][r[left][right] - 1];

        if (r[r[left][right]][right] != 0)
            cout << "\n Right child of " << r[left][right] << " :: " << r[r[left][right]][right];

        printTree(left, r[left][right] - 1);
        printTree(r[left][right], right);
    }

    void print_COST()
    {
        int n=c.size();
        int m=c[0].size();
        cout<<"Cost Matrix is: \n";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                cout<<c[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

int main() {
    OBST obst;
    int choice;

    do
    {
        cout << "Enter your choice: \n";
        cout << "1. Enter probabilities\n";
        cout << "2. Display Optimal BST Structure\n";
        cout << "3. Display Cost Matrix\n";
        cout << "4. Exit\n";
        cin >> choice;
        switch (choice)
        {
            case 1:
                obst.inputProbabilities();
                obst.constructOBST();
                break;
            case 2:
                cout << "\nOptimal BST Structure:";
                obst.printTree(0, obst.n);
                cout << endl;
                break;
            case 3:
                obst.print_COST();
                break;
            default:
                cout<<"Invalid Choice!!!\n";
                break;
        }
    }while(choice!=4);
    return 0;
}
