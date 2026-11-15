#include <iostream>
#include <string>
#include "Set.h"
using namespace std;

Set unionSets(Set& A, Set& B) {
    Set result;
    for (SNode* cur = A.getList().head; cur != nullptr; cur = cur->next) {
        result.add(cur->value);
    }
    for (SNode* cur = B.getList().head; cur != nullptr; cur = cur->next) {
        result.add(cur->value); 
    }
    return result;
}

Set intersectSets(Set& A, Set& B) {
    Set result;
    for (SNode* cur = A.getList().head; cur != nullptr; cur = cur->next) {
        if (B.incl(cur->value)) {
            result.add(cur->value);
        }
    }
    return result;
}

Set differenceSets(Set& A, Set& B) {
    Set result;
    for (SNode* cur = A.getList().head; cur != nullptr; cur = cur->next) {
        if (!B.incl(cur->value)) {
            result.add(cur->value);
        }
    }
    return result;
}

void processCommands() {
    Set A, B;
    string cmd, val1;

    while (true) {
        cout << "> ";
        cin >> cmd;

        if (cmd == "exit") break;
        
        if (cmd == "addA") {
            cin >> val1;
            A.add(val1);
        } 
        else if (cmd == "addB") {
            cin >> val1;
            B.add(val1);
        }
        else if (cmd == "printA") A.print();
        else if (cmd == "printB") B.print();
        
        else if (cmd == "union") {
            Set C = unionSets(A, B);
            cout << "A U B: "; C.print();
        }
        else if (cmd == "inter") {
            Set C = intersectSets(A, B);
            cout << "A n B: "; C.print();
        }
        else if (cmd == "diff") {
            Set C = differenceSets(A, B);
            cout << "A \\ B: "; C.print();
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
}

int main() {
    processCommands();
    return 0;
}