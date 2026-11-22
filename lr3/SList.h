#pragma once
#include <iostream>
#include <string>

struct SNode {
    std::string value;
    SNode* next;
    SNode(const std::string& v);
};

class SinglyLinkedList {
private:
    SNode* head = nullptr;
public:
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

    int findVal(const std::string& val) const;  
    void getVal(int index) const; 

    void print() const; 
    void printReverseRec(SNode* cur); 
    void printReverse(); 
    void getHead() const;
    void getTail() const;
    std::string ToString() const;
};