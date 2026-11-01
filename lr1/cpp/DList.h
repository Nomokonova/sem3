#pragma once
#include <iostream>
#include <string>

struct DNode {
    std::string value; 
    DNode* prev;
    DNode* next;
    DNode(const std::string& v = "", DNode* p = nullptr, DNode* n = nullptr);
};

struct DoublyLinkedList {
    DNode* head;
    DNode* tail;

    DoublyLinkedList();
    ~DoublyLinkedList();

    void pushFront(const std::string& value);
    void pushBack(const std::string& value);
    void insertBefore(const std::string& base, const std::string& value);
    void insertAfter(const std::string& base, const std::string& value);

    std::string popFront();
    std::string popBack();
    std::string deleteBefore(const std::string& base);
    std::string deleteAfter(const std::string& base);
    std::string deleteValue(const std::string& value);

    int findVal(const std::string& value); 
    void findInd(int index);              

    void getHead();
    void getTail();
    void print();
    void printReverse();
    
    std::string ToString();
};