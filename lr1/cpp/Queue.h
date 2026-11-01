#pragma once
#include <iostream>
#include <string>

struct QNode {
    std::string value; 
    QNode* next;
    QNode(const std::string& v);
};

struct Queue {
    QNode* head;
    QNode* tail;
    Queue();
    ~Queue();
    void push(const std::string& value);
    std::string pop();
    std::string peek(); 
    std::string back(); 
    void print();
    int Qsize();
    std::string ToString();
};