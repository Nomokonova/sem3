#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SList.h"
using namespace std;

int main(int argc, char* argv[]) {
    string fileName, query;
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) fileName = argv[++i];
        if (arg == "--query" && i + 1 < argc) query = argv[++i];
    }

    if (fileName.empty() || query.empty()) {
        cout << "Error: usage ./dbms --file data --query 'SETADD list apple'" << endl;
        return 1;
    }

    stringstream ss(query);
    string cmd, name, val;
    ss >> cmd >> name;
    if (cmd != "SETPRINT" && cmd != "PRINT") ss >> val;

    SinglyLinkedList list;
    ifstream fin(fileName);
    string word;
    while (fin >> word) {
        if (list.findVal(word) == -1) {
            list.pushBack(word);
        }
    }
    fin.close();

    bool changed = false;

    if (cmd == "SETADD") {
        if (list.findVal(val) == -1) { 
            list.pushBack(val); 
            cout << "-> " << val << endl;
            changed = true;
        } else {
            cout << "-> " << val << " (exists)" << endl;
        }
    } 
    else if (cmd == "SETDEL") {
        if (list.findVal(val) != -1) {
            list.deleteValue(val); 
            cout << "-> " << val << endl;
            changed = true;
        } else {
            cout << "-> " << val << " (not found)" << endl;
        }
    } 
    else if (cmd == "SET_AT") {
        if (list.findVal(val) != -1) cout << "TRUE" << endl;
        else cout << "FALSE" << endl;
    } 
    else if (cmd == "SETPRINT" || cmd == "PRINT") {
        list.print();
    } 
    else {
        cout << "Error: unknown command" << endl;
    }

    if (changed) {
        ofstream fout(fileName);
        fout << list.ToString() << endl;
        fout.close();
    }

    return 0;
}