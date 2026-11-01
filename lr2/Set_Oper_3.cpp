#include <iostream>
#include <string>
#include "SList.h"
using namespace std;
//объединение
SinglyLinkedList unionSets(SinglyLinkedList& A, SinglyLinkedList& B){
   SinglyLinkedList result;
   SNode* curA = A.head;
   while(curA != nullptr){
        if (result.findVal(curA->value) == -1) 
            result.pushBack(curA->value);
        curA = curA->next;
   }
   SNode* curB = B.head;
    while (curB != nullptr) {
        if(result.findVal(curB->value) == -1)
            result.pushBack(curB->value);
        curB = curB->next;
    }
    return result;
}
//пересечение
SinglyLinkedList intersectSets(SinglyLinkedList& A, SinglyLinkedList& B) {
    SinglyLinkedList result;
    SNode* curA = A.head;
    while (curA != nullptr) {
        if (B.findVal(curA->value) != -1) {
            result.pushBack(curA->value);
        }
        curA = curA->next;
    }
    return result;
}
//разность 
SinglyLinkedList differenceSets(SinglyLinkedList& A, SinglyLinkedList& B) {
    SinglyLinkedList result;
    SNode* curA = A.head;
    while (curA != nullptr) {
        if (B.findVal(curA->value) == -1) {
            result.pushBack(curA->value);
        }
        curA = curA->next;
    }
    return result;
}
int main() {
    SinglyLinkedList A, B;
    string cmd, val1;

    while (true) {
        cout << "> ";
        cin >> cmd;

        if (cmd == "exit") break;
        
        if (cmd == "addA") {
            cin >> val1;
            if (A.findVal(val1) == -1) 
                A.pushBack(val1);
        } 
        else if (cmd == "addB") {
            cin >> val1;
            if(B.findVal(val1)==-1)
                B.pushBack(val1);
        }
        else if (cmd == "printA") A.print();
        else if (cmd == "printB") B.print();
        
        else if (cmd == "union") {
            SinglyLinkedList C = unionSets(A, B);
            cout << "A U B: "; C.print();
        }
        else if (cmd == "inter") {
            SinglyLinkedList C = intersectSets(A, B);
            cout << "A n B: "; C.print();
        }
        else if (cmd == "diff") {
            SinglyLinkedList C = differenceSets(A, B);
            cout << "A \\ B: "; C.print();
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
    return 0;
}