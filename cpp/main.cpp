#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "array.h"
#include "SList.h" 
#include "DList.h"
#include "stack.h"
#include "Queue.h"
#include "Tree.h"
using namespace std;

bool isNumber(const string& s) {
    int len = s.length();
    int start = 0;
    if (len > 0 && s[0] == '-') {
        start = 1;
    }
    if (len - start < 1 || len - start > 9) {
        return false;
    }
    for (int i = start; i < len; ++i) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

int toIndex(const string& s) {
    if (!isNumber(s)) {
        return -1;
    }
    return stoi(s);
}

int wordsNeeded(const string& cmd) {
    if (cmd == "PRINT" || cmd == "MCREATE" || cmd == "MLEN" ||
        cmd == "FPOPHEAD" || cmd == "FPOPTAIL" || cmd == "FGETHEAD" || cmd == "FGETTAIL" ||
        cmd == "LPOPHEAD" || cmd == "LPOPTAIL" || cmd == "LGETHEAD" || cmd == "LGETTAIL" ||
        cmd == "SPOP" || cmd == "SPEEK" || cmd == "QPOP" || cmd == "QPEEK" ||
        cmd == "TCOMPLETE" || cmd == "TPRINT") {
        return 2;
    }
    if (cmd == "MPUSH" || cmd == "MGET" || cmd == "MDEL" ||
        cmd == "FPUSH" || cmd == "FPUSHHEAD" || cmd == "FPUSHTAIL" ||
        cmd == "FPOP" || cmd == "FDELVAL" || cmd == "FDELBEFORE" || cmd == "FDELAFTER" ||
        cmd == "FGET" || cmd == "FFIND" ||
        cmd == "LPUSH" || cmd == "LPUSHHEAD" || cmd == "LPUSHTAIL" ||
        cmd == "LPOP" || cmd == "LDELVAL" || cmd == "LDELBEFORE" || cmd == "LDELAFTER" ||
        cmd == "LGET" || cmd == "LFIND" ||
        cmd == "SPUSH" || cmd == "QPUSH" ||
        cmd == "TINSERT" || cmd == "TGET") {
        return 3;
    }
    if (cmd == "MINSERT" || cmd == "MSET" ||
        cmd == "FPUSHBEFORE" || cmd == "FPUSHAFTER" ||
        cmd == "LPUSHBEFORE" || cmd == "LPUSHAFTER") {
        return 4;
    }
    return -1;
}

bool isAddCommand(const string& cmd) {
    return cmd == "MCREATE" || cmd == "MPUSH" || cmd == "MINSERT" ||
           cmd == "FPUSH" || cmd == "FPUSHHEAD" || cmd == "FPUSHTAIL" ||
           cmd == "LPUSH" || cmd == "LPUSHHEAD" || cmd == "LPUSHTAIL" ||
           cmd == "SPUSH" || cmd == "QPUSH" || cmd == "TINSERT";
}

bool doArray(const string& cmd, const string& arg1, const string& arg2, string& data) {
    Array arr;
    stringstream ss(data);
    string w;
    while (ss >> w) arr.pushBack(w);
    bool changed = false;

    if (cmd == "MCREATE") {
        cout << "-> empty array created" << endl;
        changed = true;
    } else if (cmd == "MPUSH") {
        arr.pushBack(arg1);
        cout << "-> " << arg1 << endl;
        changed = true;
    } else if (cmd == "MINSERT") {
        int indx = toIndex(arg1);
        if (indx < 0 || indx > arr.getSize()) {
            cout << "Error: invalid index" << endl;
        } else {
            arr.insert(indx, arg2);
            cout << "-> " << arg2 << endl;
            changed = true;
        }
    } else if (cmd == "MGET") {
        int indx = toIndex(arg1);
        if (indx < 0 || indx >= arr.getSize()) {
            cout << "Error: invalid index" << endl;
        } else {
            cout << "-> ";
            arr.get(indx);
        }
    } else if (cmd == "MDEL") {
        int indx = toIndex(arg1);
        if (indx < 0 || indx >= arr.getSize()) {
            cout << "Error: invalid index" << endl;
        } else {
            cout << "-> " << arr.erase(indx) << endl;
            changed = true;
        }
    } else if (cmd == "MSET") {
        int indx = toIndex(arg1);
        if (indx < 0 || indx >= arr.getSize()) {
            cout << "Error: invalid index" << endl;
        } else {
            arr.set(indx, arg2);
            cout << "-> " << arg2 << endl;
            changed = true;
        }
    } else if (cmd == "MLEN") {
        cout << "-> " << arr.getSize() << endl;
    } else if (cmd == "PRINT") {
        arr.print();
    }

    if (changed) data = arr.ToString();
    return changed;
}

bool doList(const string& cmd, const string& arg1, const string& arg2, string& data) {
    SinglyLinkedList flist;
    stringstream ss(data);
    string w;
    while (ss >> w) flist.pushBack(w);
    bool changed = false;

    if (cmd == "FPUSHHEAD") {
        flist.pushFront(arg1);
        cout << "-> " << arg1 << endl;
        changed = true;
    } else if (cmd == "FPUSHTAIL" || cmd == "FPUSH") {
        flist.pushBack(arg1);
        cout << "-> " << arg1 << endl;
        changed = true;
    } else if (cmd == "FPUSHBEFORE") {
        flist.insertBefore(arg1, arg2);
        changed = true;
    } else if (cmd == "FPUSHAFTER") {
        flist.insertAfter(arg1, arg2);
        changed = true;
    } else if (cmd == "FPOPHEAD" || cmd == "FPOP") {
        cout << "-> " << flist.popFront() << endl;
        changed = true;
    } else if (cmd == "FPOPTAIL") {
        cout << "-> " << flist.popBack() << endl;
        changed = true;
    } else if (cmd == "FDELVAL") {
        cout << "-> " << flist.deleteValue(arg1) << endl;
        changed = true;
    } else if (cmd == "FDELBEFORE") {
        cout << "-> " << flist.deleteBefore(arg1) << endl;
        changed = true;
    } else if (cmd == "FDELAFTER") {
        cout << "-> " << flist.deleteAfter(arg1) << endl;
        changed = true;
    } else if (cmd == "FGET") {
        int indx = toIndex(arg1);
        flist.getVal(indx);
    } else if (cmd == "FFIND") {
        cout << "-> " << flist.findVal(arg1) << endl;
    } else if (cmd == "FGETHEAD") {
        flist.getHead();
    } else if (cmd == "FGETTAIL") {
        flist.getTail();
    } else if (cmd == "PRINT") {
        flist.print();
    }

    if (changed) data = flist.ToString();
    return changed;
}

bool doDoublyList(const string& cmd, const string& arg1, const string& arg2, string& data) {
    DoublyLinkedList dlist;
    stringstream ss(data);
    string w;
    while (ss >> w) dlist.pushBack(w);
    bool changed = false;

    if (cmd == "LPUSHHEAD") {
        dlist.pushFront(arg1);
        cout << "-> " << arg1 << endl;
        changed = true;
    } else if (cmd == "LPUSHTAIL" || cmd == "LPUSH") {
        dlist.pushBack(arg1);
        cout << "-> " << arg1 << endl;
        changed = true;
    } else if (cmd == "LPUSHBEFORE") {
        dlist.insertBefore(arg1, arg2);
        changed = true;
    } else if (cmd == "LPUSHAFTER") {
        dlist.insertAfter(arg1, arg2);
        changed = true;
    } else if (cmd == "LPOPHEAD" || cmd == "LPOP") {
        cout << "-> " << dlist.popFront() << endl;
        changed = true;
    } else if (cmd == "LPOPTAIL") {
        cout << "-> " << dlist.popBack() << endl;
        changed = true;
    } else if (cmd == "LDELVAL") {
        cout << "-> " << dlist.deleteValue(arg1) << endl;
        changed = true;
    } else if (cmd == "LDELBEFORE") {
        cout << "-> " << dlist.deleteBefore(arg1) << endl;
        changed = true;
    } else if (cmd == "LDELAFTER") {
        cout << "-> " << dlist.deleteAfter(arg1) << endl;
        changed = true;
    } else if (cmd == "LGET") {
        int indx = toIndex(arg1);
        dlist.findInd(indx);
    } else if (cmd == "LFIND") {
        cout << "-> " << dlist.findVal(arg1) << endl;
    } else if (cmd == "LGETHEAD") {
        dlist.getHead();
    } else if (cmd == "LGETTAIL") {
        dlist.getTail();
    } else if (cmd == "PRINT") {
        dlist.print();
    }

    if (changed) data = dlist.ToString();
    return changed;
}

bool doStack(const string& cmd, const string& arg1, string& data) {
    Stack st;
    stringstream ss(data);
    string w;
    while (ss >> w) st.push(w);
    bool changed = false;

    if (cmd == "SPUSH") {
        st.push(arg1);
        cout << "-> " << arg1 << endl;
        changed = true;
    } else if (cmd == "SPOP") {
        cout << "-> " << st.pop() << endl;
        changed = true;
    } else if (cmd == "SPEEK") {
        cout << "-> " << st.peek() << endl;
    } else if (cmd == "PRINT") {
        st.print();
    }

    if (changed) data = st.ToString();
    return changed;
}

bool doQueue(const string& cmd, const string& arg1, string& data) {
    Queue q;
    stringstream ss(data);
    string w;
    while (ss >> w) q.push(w);
    bool changed = false;

    if (cmd == "QPUSH") {
        q.push(arg1);
        cout << "-> " << arg1 << endl;
        changed = true;
    } else if (cmd == "QPOP") {
        cout << "-> " << q.pop() << endl;
        changed = true;
    } else if (cmd == "QPEEK") {
        cout << "-> " << q.peek() << endl;
    } else if (cmd == "PRINT") {
        q.print();
    }

    if (changed) data = q.ToString();
    return changed;
}

bool doTree(const string& cmd, const string& arg1, string& data) {
    CompleteBinaryTree tree;
    stringstream ss(data);
    string w;
    while (ss >> w) tree.insert(w);
    bool changed = false;

    if (cmd == "TINSERT") {
        tree.insert(arg1);
        changed = true;
    } else if (cmd == "TGET") {
        if (tree.search(arg1)) cout << "-> TRUE" << endl;
        else cout << "-> FALSE" << endl;
    } else if (cmd == "TCOMPLETE") {
        if (tree.isComplete()) cout << "-> TRUE" << endl;
        else cout << "-> FALSE" << endl;
    } else if (cmd == "PRINT" || cmd == "TPRINT") {
        tree.print();
    }

    if (changed) data = tree.ToString();
    return changed;
}

int main(int argc, char* argv[]) {
    string fileName, query;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) { fileName = argv[i + 1]; ++i; }
        else if (arg == "--query" && i + 1 < argc) { query = argv[i + 1]; ++i; }
    }
    if (fileName.empty() || query.empty()) {
        cout << "Usage: ./dbms --file file.data --query 'COMMAND name [args]'" << endl;
        return 1;
    }

    stringstream qs(query);
    string cmd, name, arg1, arg2;
    qs >> cmd >> name;

    int need = wordsNeeded(cmd);
    if (need == -1) {
        cout << "Error: unknown command " << cmd << endl;
        return 1;
    }
    if (need >= 3) qs >> arg1;
    if (need >= 4) qs >> arg2;

    Array lines;
    ifstream fin(fileName);
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) lines.pushBack(line);
    }
    fin.close();

    int found = -1;
    string fileType, data;
    for (int i = 0; i < lines.getSize(); ++i) {
        string currentLine = lines.getString(i);
        stringstream ls(currentLine);
        string t, n;
        ls >> t >> n;
        if (n == name) {
            found = i;
            fileType = t;
            string w;
            while (ls >> w) {
                if (!data.empty()) data += " ";
                data += w;
            }
            break;
        }
    }

    if (found == -1 && !isAddCommand(cmd)) {
        cout << "Error: structure " << name << " not found" << endl;
        return 1;
    }

    string type;
    if (cmd == "PRINT" || cmd == "TPRINT") type = fileType;
    else if (cmd == "TGET" || cmd == "TCOMPLETE") type = "T";
    else type = cmd.substr(0, 1);

    if (found != -1 && fileType != type) {
        cout << "Error: name " << name << " is already used by another structure type" << endl;
        return 1;
    }
    if (found != -1 && cmd == "MCREATE") {
        cout << "Error: array " << name << " already exists" << endl;
        return 1;
    }

    bool changed = false;
    if (type == "M") changed = doArray(cmd, arg1, arg2, data);
    else if (type == "F") changed = doList(cmd, arg1, arg2, data);
    else if (type == "L") changed = doDoublyList(cmd, arg1, arg2, data);
    else if (type == "S") changed = doStack(cmd, arg1, data);
    else if (type == "Q") changed = doQueue(cmd, arg1, data);
    else if (type == "T") changed = doTree(cmd, arg1, data);
    else {
        cout << "Error: unknown structure type" << endl;
        return 1;
    }

    if (changed) {
        string newLine = type + " " + name;
        if (!data.empty()) newLine += " " + data;
        
        if (found == -1) lines.pushBack(newLine);
        else lines.set(found, newLine);

        ofstream fout(fileName);
        for (int i = 0; i < lines.getSize(); ++i) {
            fout << lines.getString(i) << endl;
        }
        fout.close();
    }

    return 0;
}