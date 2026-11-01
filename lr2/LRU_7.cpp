#include <iostream>
#include <string>
#include "DList.h" 
using namespace std;

struct LRUCache {
    int capacity;
    DoublyLinkedList list; 

    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        string prefix = to_string(key) + ":"; 
        DNode* cur = list.head;
        while (cur != nullptr) {
            if (cur->value.find(prefix) == 0) { 
                string full = cur->value;
                int val = stoi(full.substr(prefix.length())); 
                list.deleteValue(full);
                list.pushFront(full);
                return val;
            }
            cur = cur->next;
        }
        return -1; 
    }

    void set(int key, int value) {
        string prefix = to_string(key) + ":";
        DNode* cur = list.head;
        while (cur != nullptr) {
            if (cur->value.find(prefix) == 0) {
                list.deleteValue(cur->value);
                break;
            }
            cur = cur->next;
        }

        string newEntry = prefix + to_string(value);
        list.pushFront(newEntry);

        if (list.getSize() > capacity) {
            list.popBack();
        }
    }
};

int main() {
    int capacity, Q;
    cout << "cap = ";
    cin >> capacity;
    cout << "Q = ";
    cin >> Q;
    LRUCache cache(capacity);
    cout << "Queries =";
    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "SET") {
            int key, value;
            cin >> key >> value;
            cache.set(key, value);
        } 
        else if (cmd == "GET") {
            int key;
            cin >> key;
            cout << cache.get(key) << " "; 
        }
    }
    cout << endl;
    return 0;
}