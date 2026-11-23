#include <iostream>
#include <string>
#include <ctime>
#include "hash.h" 
using namespace std;

HashTable::HashTable(int cap) : capacity(cap) {
    table = new Array();
    for (int i = 0; i < capacity; i++) {
        table->pushBack(""); 
    }
}
HashTable::~HashTable() {
    delete table;
}
int HashTable::hashFunc(int key) const {
    return key % capacity;
}

int HashTable::insert(int key, const string& value) {
    int index = hashFunc(key) % capacity;
    int startIndex = index;
    int steps = 0;
    while (table->getString(index) != "") {
        size_t pos = table->getString(index).find(':');
        int existingKey = stoi(table->getString(index).substr(0, pos));
        if (existingKey == key) {
            table->set(index, to_string(key) + ":" + value);
            return steps;
        }
        index = (index + 1) % capacity; 
        steps++;
        if (index == startIndex) return -1; 
    }
    table->set(index, to_string(key) + ":" + value);
    return steps;
}
string HashTable::search(int key) const {
    int index = hashFunc(key) % capacity;
    int startIndex = index;

    while (table->getString(index) != "") {
        string entry = table->getString(index);
        size_t pos = entry.find(':');
        int existingKey = stoi(entry.substr(0, pos));
        if (existingKey == key) return entry.substr(pos + 1); 
        index = (index + 1) % capacity;
        if (index == startIndex) break;
    }
    return ""; 
}
void HashTable::print() const {
    for (int i = 0; i < capacity; i++) {
        if (table->getString(i) != "") {
            cout << "[" << i << "]: " << table->getString(i) << endl;
        }
    }
}
string HashTable::ToString() const {
    string res = "";
    for (int i = 0; i < capacity; i++) {
        if (table->getString(i) != "") {
            if (!res.empty()) res += " ";
            res += table->getString(i);
        }
    }
    return res;
}


bool HashTable::remove(int key) {
    int index = hashFunc(key);
    int startIndex = index;
    while (table->getString(index) != "") {
        string entry = table->getString(index);
        size_t pos = entry.find(':');
        int existingKey = stoi(entry.substr(0, pos));
        if (existingKey == key) {
            table->set(index, "");
            int next = (index + 1) % capacity;
            while (table->getString(next) != "") {
                string displaced = table->getString(next);
                table->set(next, "");
                size_t delimiter = displaced.find(':');
                int displacedKey = stoi(displaced.substr(0, delimiter));
                string displacedValue = displaced.substr(delimiter + 1);
                insert(displacedKey, displacedValue);
                next = (next + 1) % capacity;
            }
            return true;
        }
        index = (index + 1) % capacity;
        if (index == startIndex) {
            break;
        }
    }
    return false;
}