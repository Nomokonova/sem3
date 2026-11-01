#include "DList.h"
using namespace std;

DNode::DNode(const string& v,DNode* p,DNode* n):value(v),prev(p),next(n){ }

//создание
DoublyLinkedList::DoublyLinkedList() :head(nullptr), tail(nullptr){}
//деструктор
DoublyLinkedList::~DoublyLinkedList() {
    while (head != nullptr) {
        DNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}
//добавление
//до
void DoublyLinkedList::insertBefore(const string& base, const string& value) {
    DNode* cur = head;
    while (cur != nullptr && cur->value != base)
        cur = cur->next;
    if (cur == nullptr){
        cout << "error" << endl;
        return;
    }
    DNode* n = new DNode(value);
    n->prev = cur->prev;
    n->next = cur;
    if (cur->prev != nullptr) cur->prev->next = n;
    else head = n;
    cur->prev = n;
}
//после 
void DoublyLinkedList::insertAfter(const string& base, const string& value) {
    DNode* cur = head;
    while (cur != nullptr && cur->value != base)
        cur = cur->next;
    if (cur == nullptr){
        cout << "error" << endl;
        return;
    }
    DNode* n = new DNode(value);
    n->next = cur->next;
    n->prev = cur;
    if (cur->next != nullptr)
        cur->next->prev = n;
    else tail = n;
    cur->next = n;
}
//голова
void DoublyLinkedList::pushFront(const string& value) {
    DNode* n = new DNode(value);
    n->next = head;
    if (head != nullptr)
        head->prev = n;
    else tail = n;
    head = n;
}
//хвост
void DoublyLinkedList::pushBack(const string& value) {
    DNode* n = new DNode(value);
    n->prev = tail;
    if (tail != nullptr)
        tail->next = n;
    else head = n;
    tail = n;
}
//удаление
//до
string DoublyLinkedList::deleteBefore(const string& base) {
    DNode* cur = head;
    while (cur != nullptr && cur->value != base)
        cur = cur->next;
    if (cur == nullptr || cur->prev == nullptr){
        cout << "error" << endl;
        return "";
    }
    DNode* tmp = cur->prev;
    string rem = tmp->value;
    cur->prev = tmp->prev;
    if (tmp->prev != nullptr)
        tmp->prev->next = cur;
    else head = cur;
    delete tmp;
    return rem;
}
string  DoublyLinkedList::deleteAfter(const string& base) {
    DNode* cur = head;
    while (cur != nullptr && cur->value != base)
        cur = cur->next;
    if (cur == nullptr || cur->next == nullptr){
        cout << "error" << endl;
        return "";
    }
    DNode* tmp = cur->next;
    string rem =tmp->value;
    cur->next = tmp->next;
    if (tmp->next != nullptr)
        tmp->next->prev = cur;
    else tail = cur;
    delete tmp;
    return rem;
}
//из начала
string  DoublyLinkedList::popFront() {
    if (head == nullptr){
        cout << "error" << endl;
        return "";
    }
    string rem = head->value;
    DNode* tmp = head;
    head = head->next;
    if (head != nullptr)
        head->prev = nullptr;
    else tail = nullptr;
    delete tmp;
    return rem;
}
//из конца
string  DoublyLinkedList::popBack() {
    if (tail == nullptr){
        cout << "error" << endl;
        return "";
    }
    string rem=tail->value;
    DNode* tmp = tail;
    tail = tail->prev;
    if (tail != nullptr)
        tail->next = nullptr;
    else head = nullptr;
    delete tmp;
    return rem;
}
//по значению
string DoublyLinkedList::deleteValue(const string& value) {
    DNode* tmp = head;
    while (tmp != nullptr && tmp->value != value)
        tmp = tmp->next;
    if (tmp == nullptr){
        cout << "error" << endl;
        return "";
    }
    string rem = tmp->value;
    if (tmp->prev != nullptr)
        tmp->prev->next = tmp->next;
    else head = tmp->next;
    if (tmp->next != nullptr)
        tmp->next->prev = tmp->prev;
    else tail = tmp->prev;
    delete tmp;
    return rem;
}
//поиск по значению
int DoublyLinkedList::findVal(const string& value) {
    DNode* cur = head;
    int ind = 0;
    while (cur != nullptr) {
        if (cur->value == value)
            return ind;
        cur = cur->next;
        ind++;
    }
    return -1;
}
//поиск по индексу
void DoublyLinkedList::findInd(int index) {
    if (index < 0){
        cout << "error" << endl;
        return;
    }
    DNode* cur = head;
    for (int i = 0; i < index; ++i) {
        if (cur == nullptr){
            cout << "error" << endl;
            return;
        }
        cur = cur->next;
    }
    if (cur == nullptr){
        cout << "error" << endl;
        return;
    }
    cout << cur->value << endl;
}
//вывод головы
void DoublyLinkedList::getHead() {
    if (head == nullptr) {
        cout << "list is empty" << endl;
        return;
    }
    cout << head->value << endl;
}
//вывод хвоста
void DoublyLinkedList::getTail() {
    if (tail == nullptr) {
        cout << "list is empty" << endl;
        return;
    }
    cout << tail->value << endl;
}
//прямой вывод
void DoublyLinkedList::print() {
    for (DNode* tmp = head; tmp != nullptr; tmp = tmp->next)
        cout << tmp->value << " ";
    cout << endl;
}
//обратный вывод
void DoublyLinkedList::printReverse() {
    for (DNode* tmp = tail; tmp != nullptr; tmp = tmp->prev)
        cout << tmp->value << " ";
    cout << endl;
}

string DoublyLinkedList::ToString(){
    string res;
    DNode* cur = head;
    while (cur != nullptr) {
        if (!res.empty()) res += " ";
        res += cur->value;
        cur = cur->next;
    }
    return res;
}