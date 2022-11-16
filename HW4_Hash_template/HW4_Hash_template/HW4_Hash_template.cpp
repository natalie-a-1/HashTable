//
// In HW4, we implement a hash table class that
// addresses collision using separate chaining.
//
// We will use the modular hash function, whose
// base equals to the hash table size (input as `size').
//
// The table will store student nodes.
// The student class is defined for you. Do not change it (unless there are typos
//to fix).
// The table class is partly defined. Do not change the private members.
//
// Your task is to complete five public member functions, including
// 1. Add_Head()
// 2. Add_Order()
// 3. Remove()
// 4. Search()
// 5. Print()
//
// Detailed instructions are given below.
//
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
int HashTable::Hash(int key) {
    return key % size;
};
// ---------------------
// Add_Head(Student x)
// ---------------------
// This function add a new student s to the head of the list at table[x.SID].
// For example, suppose the hash function is key%3
// and if the current hash table is
// table[0] -> 3 -> 9
// table[1] -> 1 -> 4
// table[2] -> 2 -> 5
// if we add a new student with SID=6, the new table should be
// table[0] -> 6 -> 3 -> 9
// table[1] -> 1 -> 4
// table[2] -> 2 -> 5
// ......
// ......
// ......

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

// ---------------------
// Add_Order(Student x)
// ---------------------
// This function add a new student x to the list at table[x.SID]
// such that the list remains sorted in an ascending order.
// For example, suppose the hash function is key%3
// and if the current hash table is
// table[0] -> 3 -> 9
// table[1] -> 1 -> 4
// table[2] -> 2 -> 5
// if we add a new student with SID=6, the new table should be
// table[0] -> 3 -> 6 -> 9
// table[1] -> 1 -> 3
// table[2] -> 2 -> 5
// ......
// ......
// ......

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

};// ---------------------
// Remove(int key)
// ---------------------
// This function removes a student x from the table if x.SID == key.
// If the student is not in the table, do nothing.
// For example, if the current hash table is
// table[0] -> 6 -> 3
// table[1] -> 4 -> 1
// table[2] -> 5 -> 2
// if we run Remove(4), the new table will be
// table[0] -> 6 -> 3
// table[1] -> 1
// table[2] -> 5 -> 2
// if we further run Remove(7), the new table will remain the same, i.e.,
// table[0] -> 6 -> 3
// table[1] -> 1
// table[2] -> 5 -> 2
// ......
// ......
// ......

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
// ---------------------
// Search(int key)
// ---------------------
// This function returns the major of student x in the table if x.SID == key.
// If the student is not in the table, return NA.
// For example, if the current hash table is
// table[0] -> 6 -> 3
// table[1] -> 4 -> 1
// table[2] -> 5 -> 2
// if we run Search(4), student 4's major should be returned.
// if we run Search(7), 'NA' should be returned.
// ......
// ......
// ......

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
// ---------------------
// Print()
// ---------------------
// This function prints all SIDs in the table row by row and head-to-tail per row.
// For example, if the current hash table is
// table[0] -> 6 -> 3
// table[1] -> 4 -> 1
// table[2] -> 5 -> 2
// if we run Print(), we should see "6 3 4 1 5 2" (vertically)
// For Gradescope to grade correctly, please strictly follow the given output
//format.
void HashTable::Print() {
    for (int i = 0; i < size; i++) {
        Student* temp = table[i]; // used to store the node we want to print
        // now implement your print function
        while (temp != NULL) {
            cout << temp->SID << endl;
            temp = temp->next;
        }
    }
    // whenever you get a node to print, assign its address to temp
    // and print its SID using "cout << temp->SID << endl;"
    // do not add any other cout otherwise gradescope will fail to grade it
//correctly
};
int main()
{
    int mode, size, key, sid, maj;
    vector<Student> input;
    Student temp;
    // Input test mode, table size, search key.
    cin >> mode >> size >> key;
    // Store input nodes in a vector for now.
    // However, we should not vectors to stored
    // collided students in the hash table.
    // We should use linked list instead.
    while (cin >> sid >> maj) {
        temp.SID = sid;
        temp.MAJ = static_cast<major>(maj);
        input.push_back(temp);
    };
    // Now construct and test the hash table.
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
