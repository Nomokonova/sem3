#pragma once
#include <iostream>
#include <string>

struct Array {
    std::string* data;
    int capacity;
    int size;
    void resize();
    Array();
    ~Array();
    void insert(int index, const std::string& value); 
    void pushBack(const std::string& value);
    void get(int index);                              
    std::string erase(int index);                    
    void set(int index, const std::string& value);    
    int getSize();
    void print();
    std::string ToString();
    std::string getString(int index);
};