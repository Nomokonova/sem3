#pragma once
#include <iostream>
#include <string>

template <typename T>
struct QNode {
    T value; 
    QNode* next;
    QNode(const T& v);
};
template <typename T>
class Queue {
private:
    friend class StructureCodec;
    QNode<T>* head;
    QNode<T>* tail;
public:
    Queue();
    ~Queue();
    void push(const T& value);
    T pop();
    T peek() const; 
    T back() const; 
    void print() const;
    int Qsize() const;
    std::string ToString() const;
};
