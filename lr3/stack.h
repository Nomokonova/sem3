#pragma once
#include <iostream>
#include <string>

struct StackNode {
    std::string value;
    StackNode* next;
    StackNode(const std::string& v);
};

class Stack {
private:
    StackNode* top;
public:
    Stack();
    ~Stack();
    void push(const std::string& value); 
    std::string pop();                   
    std::string peek() const;                  
    void print() const;                        
    int StackSize() const;    
    std::string ToString() const;
};