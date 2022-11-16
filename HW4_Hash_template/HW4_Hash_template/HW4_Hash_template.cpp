#include <iostream>
#include <vector>
using namespace std;
enum major { CS, CE, NA };
class Student {
public:
    int SID;
    enum major MAJ;
    Student* next;
    Student();
};
Student::Student() {
    SID = -1;
    MAJ = NA;
    next = NULL;
};
class HashTable {
private:
    Student** table;
    int size;
public:
    HashTable(int table_size);
    void Add_Head(Student s);
    void Add_Order(Student s);
    void Remove(int key);
    enum major Search(int key);
    void Print();
    int Hash(int key);
};
HashTable::HashTable(int table_size) {
    size = table_size;
    table = new Student * [size];
    for (int i = 0; i < size; i++) {
        table[i] = NULL;
    }
};
void HashTable::Add_Head(Student s) {
    int hash = Hash(s.SID);
    
    if (table[hash] == NULL) {
        table[hash] = new Student(s);
    }
    else {
        Student* ptr = new Student(s);
        ptr->next = table[hash];
        table[hash] = ptr;
    }
}
void HashTable::Add_Order(Student x) {
    Student* y = new Student(x);
    Student* temp = table[Hash(y->SID)];
    Student* previous = table[Hash(y->SID)];
    
    if (temp == NULL) {
        table[Hash(y->SID)] = y;
        return;
    }
    while (temp != NULL) {
        if (y->SID < temp->SID) {
            if (temp == table[Hash(y->SID)]) {
                y->next = temp;
                table[Hash(y->SID)] = y;
                return;
            }
                else{
                    y->next = temp;
                    previous->next = y;
                    return;
                }
        } else {
            previous = temp;
            temp = temp->next;
            continue;
        }
    }

    previous->next = y;
    return;

};
void HashTable::Remove(int key) {
    int hash = Hash(key);
    Student* current = table[hash];
    if (current->SID == key) {
        table[hash] = current->next;
        return;
    }
    while (current->next != NULL) {
        if (current->next->SID == key) {
            if (current->next->next == NULL) {
                current->next = NULL;
            } else {
                current->next = current->next->next;
            }
            break;
        }
        current = current->next;
    }
}
enum major HashTable::Search(int key) {
    int hash = Hash(key);
    Student* current = table[hash];
    while (current != NULL) {
        if (current->SID == key) {
            return current->MAJ;
        }
            current = current->next;
    }
    return major::NA;
}
void HashTable::Print() {
    for (int i = 0; i < size; i++) {
        Student* temp = table[i]; // used to store the node we want to print
        // now implement your print function
        while (temp != NULL) {
            cout << temp->SID << endl;
            temp = temp->next;
        }
    }
};
int main()
{
    int mode, size, key, sid, maj;
    vector<Student> input;
    Student temp;
    cin >> mode >> size >> key;
    while (cin >> sid >> maj) {
        temp.SID = sid;
        temp.MAJ = static_cast<major>(maj);
        input.push_back(temp);
    };
    HashTable x(size);
    switch (mode) {
        case 1: // check the Add_Head and Print functions
            for (int i = 0; i < input.size(); i++) {
                x.Add_Head(input.at(i));
            }
            x.Print();
            break;
        case 2: // check the Add_Order function
            for (int i = 0; i < input.size(); i++) {
                x.Add_Order(input.at(i));
            }
            x.Print();
            break;
        case 3: // check the Search function (based on Add_Order)
            for (int i = 0; i < input.size(); i++) {
                x.Add_Order(input.at(i));
            }
            switch (x.Search(key)) {
                case 0:
                    cout << "CS" << endl;
                    break;
                case 1:
                    cout << "CE" << endl;
                    break;
                case 2:
                    cout << "NA" << endl;
                    break;
            }
            break;
        case 4: // check the Remove function (based on Add_Order)
            for (int i = 0; i < input.size(); i++) {
                x.Add_Order(input.at(i));
            }
            x.Remove(key);
            x.Print();
            break;
    }
    return 0;
}
