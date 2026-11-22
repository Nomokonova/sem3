#pragma once
#include <iostream>
#include <string>

class Array {
private:
    std::string* data;
    int capacity;
    int size;
    void resize();
public:
    Array();
    ~Array();
    void insert(int index, const std::string& value); 
    void pushBack(const std::string& value);
    void get(int index) const;                              
    std::string erase(int index);                    
    void set(int index, const std::string& value);    
    int getSize() const;
    void print() const;
    std::string ToString() const;
    std::string getString(int index) const;
};