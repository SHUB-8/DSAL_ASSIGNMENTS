// Consider telephone book database of N clients. Make use of a hash table
// implementation to quickly look up client‘s telephone number. Make use
// of two collision handling techniques and compare them using number of
// comparisons required to find a set of telephone numbers (Note: Use linear
// probing with replacement and without replacement)

#include <iostream>
using namespace std;

class Tel_Database
{
private:
    int n;
    long int* arr;
    string* arr1;

public:
    Tel_Database()
    {
        cout << "Enter no. of Clients: ";
        cin >> this->n;
        arr = new long int[n];
        arr1 = new string[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = 0;
        }
    }

    int folding(long int val)
    {
        string key = to_string(val);
        int sum = 0;
        for (size_t i = 0; i < key.length(); i += 3) {
            sum += stoi(key.substr(i, 3));
        }
        return sum % n;
    }

    void linprob_withoutrep(long int val, string name)
    {
        int index = folding(val);
        
        while (arr[index] != 0)
        {
            index = (index + 1) % n;
        }
        arr[index] = val;
        arr1[index] = name;
    }

    void accept_data()
    {
        for (int i = 0; i < n; i++)
        {
            string temp;
            long int tel_no;
            cout << "Enter name of the Client: ";
            cin >> temp;
            cout << "Enter telephone no. of the Client: ";
            cin >> tel_no;

            linprob_withoutrep(tel_no, temp);
        }
    }

    void display()
    {
        cout << "\nTelephone Book (Hash Table Representation):\n";
        for (int i = 0; i < n; i++)
        {
        }
    }
           

};

int main()
{
    Tel_Database d1;
    d1.accept_data();
    d1.display();
    return 0;
}
