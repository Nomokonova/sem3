#include "SList.h"
using namespace std;

SNode::SNode (const string& v):value(v), next(nullptr){}
SinglyLinkedList::SinglyLinkedList() : head(nullptr) {}
SinglyLinkedList::~SinglyLinkedList() {
    while (head) {
        SNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}
void SinglyLinkedList::pushFront(const string& value) {
    SNode* n = new SNode(value);
    n->next = head;
    head = n;
}
//в хвост
void SinglyLinkedList::pushBack(const string& value) {
    SNode* n = new SNode(value);
    if (head == nullptr) {
        head = n;
        return;
    }
    SNode* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = n;
}
//до
void SinglyLinkedList:: insertBefore(const string& base, const string& value) {
    if (head == nullptr){
        cout << "error" << endl;
        return;
    }
    if (head->value == base) {
        pushFront(value);
        return;
    }
    SNode* cur = head;
    while (cur->next != nullptr && cur->next->value != base) {
        cur = cur->next;
    }
    if (cur->next == nullptr) {
        cout << "error" << endl;
        return;
    }
    SNode* n = new SNode(value);
    n->next = cur->next;
    cur->next = n;
}
//после
void SinglyLinkedList::insertAfter(const string& base, const string& value) {
    SNode* cur = head;
    while (cur != nullptr && cur->value != base) {
        cur = cur->next;
    }
    if (cur == nullptr){
        cout << "error" << endl;
        return;
    }
    SNode* n = new SNode(value);
    n->next = cur->next;
    cur->next = n;
}
//удаление
//из начала
string SinglyLinkedList::popFront() {
    if (head == nullptr){
        cout << "error" << endl;
        return "";
    }
    string rem=head->value;
    SNode* tmp = head;
    head = head->next;
    delete tmp;
    return  rem;
}
//из конца
string SinglyLinkedList::popBack() {
    if (head == nullptr){
        cout << "error" << endl;
        return "";
    }
    if (head->next == nullptr) {
        string rem=head->value;
        delete head;
        head = nullptr;
        return rem;
    }
    SNode* cur = head;
    while (cur->next->next != nullptr) {
        cur = cur->next;
    }
    string rem=cur->next->value;
    delete cur->next;
    cur->next = nullptr;
    return rem;
}
//удаление до
string SinglyLinkedList::deleteBefore(const string& base) {
    if (head == nullptr || head->value == base) {
        cout << "error" << endl;
        return "";
    }
    if (head->next != nullptr && head->next->value == base) {
        return popFront();
    }
    SNode* cur = head;
    while (cur->next->next != nullptr && cur->next->next->value != base) {
        cur = cur->next;
    }
    if (cur->next->next == nullptr){
        cout << "error" << endl;
        return "";
    }
    SNode* tmp = cur->next;
    string rem=tmp->value;
    cur->next = tmp->next;
    delete tmp;
    return rem;
}
//удаление после
string SinglyLinkedList::deleteAfter(const string& base) {
    SNode* cur = head;
    while (cur && cur->value != base) {
        cur = cur->next;
    }
    if (cur == nullptr || cur->next == nullptr){
        cout << "error" << endl;
        return "";
    }
    SNode* tmp = cur->next;
    string rem = tmp->value;
    cur->next = tmp->next;
    delete tmp;
    return rem;
}
//удаление первого элемента по значению 
string SinglyLinkedList::deleteValue(const string& value) {
    if (head == nullptr)  {
        cout << "Error!" << endl;
        return "";
    }
    if (head->value == value)
        return popFront();
    SNode* cur = head;
    while (cur->next != nullptr && cur->next->value != value)
        cur = cur->next;
    if (cur->next == nullptr) {
        cout << "Error!" << endl;
        return "";
    }
    SNode* tmp = cur->next;
    string rem = tmp->value;
    cur->next = tmp->next;
    delete tmp;
    return rem;
}
//поиск
int SinglyLinkedList::findVal(const string& val) {
    SNode* cur = head;
    int ind = 0;
    while (cur != nullptr) {
        if (cur->value == val)
            return ind;
        cur = cur->next;
        ++ind;
    }
    return -1;
}
//получить значение 
void SinglyLinkedList::getVal(int index) {
    if (index < 0) {
        cout << "Error!" << endl;
        return;
    }
    SNode* cur = head;
    for (int i = 0; i < index; ++i) {
        if (cur == nullptr){
            cout << "Error!" << endl;
            return;
        }
        cur = cur->next;
    }
    if (cur == nullptr){
        cout << "Error!" << endl;
        return;
    }
    cout << cur->value << endl;
}
//вывод
void SinglyLinkedList::print() {
    for (SNode* cur = head; cur != nullptr; cur = cur->next) 
        cout << cur->value << " ";
    cout << endl;
}
//вывод наоборот
void SinglyLinkedList::printReverseRec(SNode* cur) {
    if (cur == nullptr) return;
    printReverseRec(cur->next);
    cout << cur->value << " ";
}
void SinglyLinkedList::printReverse() {
    printReverseRec(head);
    cout << endl;
}
//вывод головы
void SinglyLinkedList::getHead() {
    if (head == nullptr){
        cout << "list is empty" << endl;
        return;
    }
    cout << head->value << endl;
}
//вывод хвоста
void SinglyLinkedList::getTail() {
    if (head == nullptr) {
        cout << "list is empty" << endl;
        return;
    }
    SNode* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cout << cur->value << endl;
}

string SinglyLinkedList::ToString() {
    string res;
    SNode* cur = head;
    while (cur != nullptr) {
        if (!res.empty()) res += " ";
        res += cur->value;
        cur = cur->next;
    }
    return res;
}