#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Record {
    int id;
    char name[30];
};

const char* FILENAME = "records.dat";
const int BASE_ID = 1000;
const int MAX_RECORDS = 1000;

long getPosition(int id) {
    return (id - BASE_ID) * sizeof(Record);
}

void initializeFileIfNeeded() {
    fstream file(FILENAME, ios::in | ios::binary);
    if (!file) {
        ofstream newFile(FILENAME, ios::binary);
        Record blank = {-1, ""};
        for (int i = 0; i < MAX_RECORDS; i++)
            newFile.write(reinterpret_cast<const char*>(&blank), sizeof(Record));
        newFile.close();
    } else {
        file.close();
    }
}

void insertRecord(const Record& rec) {
    if (rec.id < BASE_ID || rec.id >= BASE_ID + MAX_RECORDS) {
        cout << "Invalid roll number.\n";
        return;
    }

    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    file.seekg(getPosition(rec.id));
    Record existing;
    file.read(reinterpret_cast<char*>(&existing), sizeof(Record));

    if (existing.id != -1) {
        cout << "Record with ID " << rec.id << " already exists.\n";
        file.close();
        return;
    }

    file.seekp(getPosition(rec.id));
    file.write(reinterpret_cast<const char*>(&rec), sizeof(Record));
    cout << "Record inserted successfully.\n";
    file.close();
}

void deleteRecord(int id) {
    if (id < BASE_ID || id >= BASE_ID + MAX_RECORDS) {
        cout << "Invalid roll number.\n";
        return;
    }

    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    file.seekg(getPosition(id));
    Record rec;
    file.read(reinterpret_cast<char*>(&rec), sizeof(Record));

    if (rec.id == -1) {
        cout << "Record with ID " << id << " not found.\n";
    } else {
        rec.id = -1;
        strcpy(rec.name, "");
        file.seekp(getPosition(id));
        file.write(reinterpret_cast<const char*>(&rec), sizeof(Record));
        cout << "Record deleted successfully.\n";
    }

    file.close();
}

void updateRecord(int id) {
    if (id < BASE_ID || id >= BASE_ID + MAX_RECORDS) {
        cout << "Invalid roll number.\n";
        return;
    }

    fstream file(FILENAME, ios::in | ios::out | ios::binary);
    file.seekg(getPosition(id));
    Record rec;
    file.read(reinterpret_cast<char*>(&rec), sizeof(Record));

    if (rec.id == -1) {
        cout << "Record with ID " << id << " not found.\n";
    } else {
        cout << "Current name: " << rec.name << endl;
        cout << "Enter new name: ";
        cin >> rec.name;

        file.seekp(getPosition(id));
        file.write(reinterpret_cast<const char*>(&rec), sizeof(Record));
        cout << "Record updated successfully.\n";
    }

    file.close();
}

void displayAll() {
    ifstream file(FILENAME, ios::binary);
    if (!file) {
        cout << "File not found.\n";
        return;
    }

    Record rec;
    bool found = false;
    for (int i = 0; i < MAX_RECORDS; i++) {
        file.read(reinterpret_cast<char*>(&rec), sizeof(Record));
        if (rec.id != -1) {
            cout << "ID: " << rec.id << ", Name: " << rec.name << endl;
            found = true;
        }
    }

    if (!found)
        cout << "No records found.\n";

    file.close();
}

Record inputRecord() {
    Record r;
    cout << "Enter Roll Number (1000–1999): ";
    cin >> r.id;
    cout << "Enter name: ";
    cin >> r.name;
    return r;
}

int main() {
    initializeFileIfNeeded();

    int choice;
    while (true) {
        cout << "\n1. Insert Record\n2. Delete Record\n3. Update Record\n4. Display All\n5. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            Record rec = inputRecord();
            insertRecord(rec);
        }
        else if (choice == 2) {
            int id;
            cout << "Enter Roll Number to delete: ";
            cin >> id;
            deleteRecord(id);
        }
        else if (choice == 3) {
            int id;
            cout << "Enter Roll Number to update: ";
            cin >> id;
            updateRecord(id);
        }
        else if (choice == 4) {
            displayAll();
        }
        else if (choice == 5) {
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
