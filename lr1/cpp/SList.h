#pragma once
#include <iostream>
#include <string>

struct SNode {
    std::string value;
    SNode* next;
    SNode(const std::string& v);
};
struct SinglyLinkedList {
    SNode* head = nullptr;
    SinglyLinkedList();
    ~SinglyLinkedList();

    void pushFront(const std::string& value);
    void pushBack(const std::string& value);
    void insertBefore(const std::string& base, const std::string& value);
    void insertAfter(const std::string& base, const std::string& value);

    std::string popFront();
    std::string popBack();
    std::string deleteBefore(const std::string& base);
    std::string deleteAfter(const std::string& base);
    std::string deleteValue(const std::string& value);

    int findVal(const std::string& val);  
    void getVal(int index);              

    void print();
    void printReverseRec(SNode* cur);
    void printReverse();
    void getHead();
    void getTail();
    std::string ToString();
};