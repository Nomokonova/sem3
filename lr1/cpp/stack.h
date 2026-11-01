#pragma once
#include <iostream>
#include <string>

struct StackNode {
    std::string value;
    StackNode* next;
    StackNode(const std::string& v);
};

struct Stack {
    StackNode* top;
    Stack();
    ~Stack();
    void push(const std::string& value); 
    std::string pop();                   
    std::string peek();                  
    void print();                        
    int StackSize();    
    std::string ToString();
};