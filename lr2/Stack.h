#pragma once

template <typename T>
struct StackNode {
    T value;
    StackNode* next;
    StackNode(const T& v);
};

template <typename T>
struct Stack {
    StackNode<T>* top;
    Stack();
    ~Stack();
    void push(const T& value); 
    T pop();                   
    T peek();                  
    bool empty();
};