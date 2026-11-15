#pragma once
#include <string>
#include "SList.h"

class Set {
private:
    SinglyLinkedList list;
public:
    void add(const std::string& val);
    void del(const std::string& val);
    bool incl(const std::string& val);
    void print();
    std::string ToString() const; 
    SinglyLinkedList& getList() { return list; }
};