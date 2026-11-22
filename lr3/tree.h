#pragma once
#include <iostream>
#include <string>

struct TNode {
    std::string value; 
    TNode* left;
    TNode* right;
    TNode(const std::string& v);
};

class CompleteBinaryTree {
private:
    size_t size;
    TNode* root;

    void clear(TNode* node);
    void PrintTreeRec(TNode* node, int level) const;  
    bool searchRec(TNode* node, const std::string& value) const; 
public:
    CompleteBinaryTree();
    ~CompleteBinaryTree();
    
    void insert(const std::string& value);               
    bool isComplete() const;                                   
    bool search(const std::string& value) const;               
    void print()const;                                       
    int getsize()const;  
    std::string ToString()const;
};