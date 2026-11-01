#include "Stack.h"
using namespace std;

template <typename T>
StackNode<T>::StackNode(const T& v): value(v),next(nullptr){} 

template <typename T>
Stack<T>::Stack():top(nullptr){}

template <typename T>
Stack<T>::~Stack(){
    while(top != nullptr){
        StackNode<T>* tmp = top;
        top = top->next;
        delete tmp;
    }
}

template <typename T>
void Stack<T>::push(const T& val){
    StackNode<T>* n = new StackNode<T>(val);
    n->next = top;
    top = n;
}

template <typename T>
T Stack<T>::pop(){
    if(top == nullptr) return T();
    T rem = top -> value;
    StackNode<T>* tmp = top;
    top = top->next;
    delete tmp;
    return rem;
}

template <typename T>
T Stack<T>::peek(){
    if (top == nullptr) return T();
    return top->value;
}

template <typename T>
bool Stack<T>::empty(){
    return top == nullptr;
}

template struct Stack<int>;
template struct Stack<char>;