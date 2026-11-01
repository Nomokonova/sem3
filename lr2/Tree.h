#pragma once
#include <iostream>
#include <string>

struct TNode {
    std::string value; 
    TNode* left;
    TNode* right;
    TNode(const std::string& v);
};

struct TQueue {
    struct TQNode {
        TNode* value;
        TQNode* next;
        TQNode(TNode* val) : value(val), next(nullptr) {}
    };
    TQNode* head;
    TQNode* tail;
    TQueue();
    ~TQueue();
    void push(TNode* val);
    void pop();
    TNode* front();
    bool empty();
};

struct CompleteBinaryTree {
    size_t size;
    TNode* root;

    CompleteBinaryTree();
    ~CompleteBinaryTree();
    void clear(TNode* node);

    void insert(const std::string& value);               
    bool isComplete();                                   
    bool search(const std::string& value);               
    bool searchRec(TNode* node, const std::string& value); 
    void print();  
    void PrintTreeRec(TNode* node, int level);                                       
    int getsize();  
    
    std::string ToString();
};