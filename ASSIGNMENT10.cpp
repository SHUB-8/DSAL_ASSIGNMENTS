#include <bits/stdc++.h>
using namespace std;

class Node
{
private:
    int data;
    Node *left;
    Node *right;
public:
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
    friend class Heap;
};

class Heap
{
private:
    vector<Node*> arr;
public:
    Heap()
    {
        int n,m;
        cout << "Enter the number of elements: ";
        cin >> n;
        for (int i=0;i<n;i++)
        {
            cout<<"Enter data: ";
            cin>>m;
            arr.push_back(new Node(m));
        }
    }

    void create_CBT()
    {
        int n = arr.size();
        for(int i=0; i<n; i++)
        {
            if(2*i + 1 < n)
                arr[i]->left = arr[2*i + 1];
            
            if(2*i + 2 < n)
                arr[i]->right = arr[2*i + 2];
        }
    }

    void heapify(int i, int n)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left<n && arr[left]->data > arr[largest]->data)
            largest = left;

        if(right<n && arr[right]->data > arr[largest]->data)
            largest = right;

        if(largest != i)
        {
            swap(arr[i]->data, arr[largest]->data);
            heapify(largest, n);
        }
    }

    void buildMaxHeap()
    {
        int n = arr.size();
        for(int i=n/2 - 1; i>= 0; i--)
        {
            heapify(i, n);
        }
    }

    void min_heapify(int i, int n)
    {
        int lowest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left<n && arr[left]->data < arr[lowest]->data)
            lowest = left;

        if(right<n && arr[right]->data < arr[lowest]->data)
            lowest = right;

        if(lowest != i)
        {
            swap(arr[i]->data, arr[lowest]->data);
            min_heapify(lowest, n);
        }
    }

    void buildMinHeap()
    {
        int n = arr.size();
        for(int i=n/2 - 1; i>= 0; i--)
        {
            min_heapify(i, n);
        }
    }

    void printHeap()
    {
        for(auto node : arr)
        {
            cout << node->data << " ";
        }
        cout<<"\n";
    }

    void heap_sort_max()
    {
        vector<int> sorted;
        int count = 1;
        int n = arr.size();
    
        buildMaxHeap();
    
        for (int i = n - 1; i >= 1; i--)
        {
            swap(arr[0]->data, arr[i]->data);
            sorted.push_back(arr[i]->data);
            heapify(0, i);
    
            cout << "Pass " << count << " : ";
            for (int j = 0; j < i; j++)
                cout << arr[j]->data << " ";
            cout << "\n";
            count++;
        }
    
        sorted.push_back(arr[0]->data);
        cout << "\nSorted Array is: ";
        for (int i = sorted.size() - 1; i >= 0; i--)
            cout << sorted[i] << " ";
        cout << "\n";
    }

    void heap_sort_min()
    {
        vector<int> sorted;
        int count = 1;
        int n = arr.size();
    
        buildMinHeap();
    
        for (int i = n - 1; i >= 1; i--)
        {
            swap(arr[0]->data, arr[i]->data);
            sorted.push_back(arr[i]->data);
            min_heapify(0, i);
    
            cout << "Pass " << count << " : ";
            for (int j = 0; j < i; j++)
                cout << arr[j]->data << " ";
            cout << "\n";
            count++;
        }
    
        sorted.push_back(arr[0]->data);
        cout << "\nSorted Array is: ";
        for (int val : sorted)
            cout << val << " ";
        cout << "\n";
    }

};

int main()
{
    Heap heap;
    heap.create_CBT();
    cout<<"\nHeap before Heapify: ";
    heap.printHeap();
    heap.buildMaxHeap();
    cout<<"Max Heap after Heapify: ";
    heap.printHeap();
    cout<<"\n";
    heap.heap_sort_max();
    return 0;
}
