#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student
{
    string name, address;
    int rollNo, div;

public:
    Student()
    {
        name = address = "";
        rollNo = div = 0;
        ofstream file("students.txt", ios::app);
        file.close();
    }

    void getData()
    {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Division: ";
        cin >> div;
        cin.ignore();

        cout << "Enter Address: ";
        getline(cin, address);
    }

    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Roll: " << rollNo << endl;
        cout << "Division: " << div << endl;
        cout << "Address: " << address << endl;
    }


    void addRecord()
    {
        ofstream file("students.txt", ios::app);
        getData();

        file << "Name: " << name << endl;
        file << "Roll: " << rollNo << endl;
        file << "Division: " << div << endl;
        file << "Address: " << address << endl;
        file << endl;
        file.close();
        cout << "Student record added successfully!" << endl;
    }

    void displayRecord(int searchRollNo)
    {
        ifstream file("students.txt");
        bool found = false;
        string line;

        while (getline(file, line))
        {
            if (line.find("Name: ") == 0)
                name = line.substr(6);
            else if (line.find("Roll: ") == 0)
                rollNo = stoi(line.substr(6));
            else if (line.find("Division: ") == 0)
                div = stoi(line.substr(10));
            else if (line.find("Address: ") == 0)
            {
                address = line.substr(9);

                if (rollNo == searchRollNo)
                {
                    cout << "\nStudent Found:\n";
                    display();
                    found = true;
                    break;
                }
            }
        }

        file.close();
        if (!found)
        {
            cout << "Student record not found!" << endl;
        }
    }

    void displayAllRecords()
    {
        ifstream file("students.txt");
        string line;
        bool anyRecord = false;
        cout << "\n----- All Student Records -----\n";
        while (getline(file, line))
        {
            if (line.find("Name: ") == 0)
                name = line.substr(6);
            else if (line.find("Roll: ") == 0)
                rollNo = stoi(line.substr(6));
            else if (line.find("Division: ") == 0)
                div = stoi(line.substr(10));
            else if (line.find("Address: ") == 0)
            {
                address = line.substr(9);
                anyRecord = true;
                cout << "Student Record: \n" << endl;
                display();
            }
        }

        file.close();
        if (!anyRecord)
            cout << "No student records found." << endl;
    }

    void deleteRecord(int deleteRollNo)
    {
        ifstream fin("students.txt");
        ofstream fout("temp.txt");
        bool found = false;
        string line;

        while (getline(fin, line))
        {
            if (line.find("Name: ") == 0)
            {
                name = line.substr(6);
                getline(fin, line);
                rollNo = stoi(line.substr(6));
                getline(fin, line);
                div = stoi(line.substr(10));
                getline(fin, line);
                address = line.substr(9);

                if (rollNo == deleteRollNo)
                {
                    found = true;
                }
                else
                {
                    fout << "Name: " << name << endl;
                    fout << "Roll: " << rollNo << endl;
                    fout << "Division: " << div << endl;
                    fout << "Address: " << address << endl;
                    fout << endl;
                }
            }
        }

        fin.close();
        fout.close();
        remove("students.txt");
        rename("temp.txt", "students.txt");
        if (found)
            cout << "Student record deleted successfully!" << endl;
        else
            cout << "Student record not found!" << endl;
    }

    void updateRecord(int updateRollNo)
    {
        ifstream fin("students.txt");
        ofstream fout("temp.txt");
        bool found = false;
        string line;

        while (getline(fin, line))
        {
            if (line.find("Name: ") == 0)
            {
                name = line.substr(6);
                getline(fin, line);
                rollNo = stoi(line.substr(6));
                getline(fin, line);
                div = stoi(line.substr(10));
                getline(fin, line);
                address = line.substr(9);

                if (rollNo == updateRollNo)
                {
                    cout << "Existing record found. Enter new details:\n";
                    getData();
                    fout << "Name: " << name << endl;
                    fout << "Roll: " << rollNo << endl;
                    fout << "Division: " << div << endl;
                    fout << "Address: " << address << endl;
                    fout << endl;
                    found = true;
                }
                else
                {
                    fout << "Name: " << name << endl;
                    fout << "Roll: " << rollNo << endl;
                    fout << "Division: " << div << endl;
                    fout << "Address: " << address << endl;
                    fout << endl;
                }
            }
        }

        fin.close();
        fout.close();
        remove("students.txt");
        rename("temp.txt", "students.txt");
        if (found)
            cout << "Student record updated successfully!" << endl;
        else
            cout << "Student record not found!" << endl;
    }
};

int main()
{
    Student Stud;
    int choice, roll;
    do
    {
        cout << "\nEnter your choice: " << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Search Student Record" << endl;
        cout << "3. Delete Student Record" << endl;
        cout << "4. Update Student Record" << endl;
        cout << "5. Display All Student Records" << endl;
        cout << "6. Exit" << endl;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            Stud.addRecord();
            break;

        case 2:
            cout << "Enter Roll No to Search: ";
            cin >> roll;
            Stud.displayRecord(roll);
            break;

        case 3:
            cout << "Enter Roll No to delete: ";
            cin >> roll;
            Stud.deleteRecord(roll);
            break;

        case 4:
            cout << "Enter Roll No to update: ";
            cin >> roll;
            Stud.updateRecord(roll);
            break;

        case 5:
            Stud.displayAllRecords();
            break;

        case 6:
            cout << "Exiting Program." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }while (choice != 6);
    return 0;
}
