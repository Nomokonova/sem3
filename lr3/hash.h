#pragma once
#include <iostream>
#include <string>
#include "array.h" 

class HashTable {
private:
    friend class StructureCodec;
    
    Array* table; 
    int capacity; 

    int hashFunc(int key) const; 
    int secondHash(int key) const; 

public:
    HashTable(int cap); 
    ~HashTable();       
    int insert(int key, const std::string& value);
    std::string search(int key) const;
    void print() const;
    std::string ToString() const;
    bool remove(int key);
};