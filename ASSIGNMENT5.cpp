// Implement all the functions of a dictionary (ADT) using open hashing
// technique: separate chaining using linked list Data: Set of (key, value)
// pairs, Keys are mapped to values, Keys must be comparable, and Keys must
// be unique. Standard Operations: Insert(key, value), Find(key), De-
// lete(key)

#include <iostream>
using namespace std;

class Node
{
private:
    string key;
    string meaning;
    Node* next;

public:
    Node(string val, string mean) : key(val), meaning(mean), next(nullptr) {}
    friend class Linklist;
};

class Linklist
{
private:
    int n;
    Node** arr;

public:
    Linklist()
    {
        cout << "Enter hash table size: ";
        cin >> n;
        arr = new Node*[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = nullptr;
        }
    }

    int folding(string val)
    {
        int sum = 0;
        for (char c : val)
        {
            sum += int(c);
        }
        return sum % n;
    }

    void insert(string val, string mean)
    {
        int index = folding(val);
        Node* newNode = new Node(val, mean);

        if (arr[index] == nullptr)
        {
            arr[index] = newNode;
        }
        else
        {
            Node* temp = arr[index];
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void find(string val)
    {
        int index = folding(val);
        Node* temp = arr[index];
        int compar = 0;
        while (temp != nullptr)
        {
            if (temp->key == val)
            {
                cout <<"Element found in "<<compar+1<<" comparisions\n";
                cout <<"[" <<temp->key<<" : "<<temp->meaning<<"]\n";
                return;
            }
            temp = temp->next;
            compar+=1;
        }
        cout << "Element not found!!!\n";
    }

    void del(string val)
    {
        int index = folding(val);
        Node* temp = arr[index];
        Node* prev = nullptr;

        while (temp != nullptr && temp->key != val)
        {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr)
        {
            cout << "Element not found!!!\n";
            return;
        }

        if (prev == nullptr)
        {
            arr[index] = temp->next;
        }
        else
        {
            prev->next = temp->next;
        }

        delete temp;
        cout << "Element deleted!\n";
        return;
    }

    void display()
    {
        cout << "\nDatabase:\n";
        for (int i = 0; i < n; i++)
        {
            cout << "[" << i << "]: ";
            Node* temp = arr[i];

            if (temp==nullptr)
            {
                cout << "NULL\n";
                continue;
            }

            while (temp != nullptr)
            {
                cout << "[" << temp->key << " : " << temp->meaning << "] -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }
};

int main()
{
    Linklist l1;
    int k;
    string val1,val2;
    do{
        cout<<"\nEnter Operation:\n";
        cout<<"1.Insert Element\n";
        cout<<"2.Delete Element\n";
        cout<<"3.Display Dictionary\n";
        cout<<"4.Search Element\n";
        cin>>k;
        cin.ignore();

        switch(k)
        {
            case 1: cout<<"Enter word: ";
                    getline(cin,val1);
                    cout<<"Enter its meaning: ";
                    getline(cin,val2);
                    l1.insert(val1,val2);
                    break;
            
            case 2: cout<<"Enter word to be deleted: ";
                    getline(cin,val1);
                    l1.del(val1);
                    break;
            
            case 3: l1.display();
                    break;
            
            case 4: cout<<"Enter word to be searched: ";
                    getline(cin,val1);
                    l1.find(val1);
                    break;
        }
    }while(k>0 && k<4);

    return 0;
}
