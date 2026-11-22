#include "tree.h"
#include "Queue.h" 
using namespace std;

template class Queue<TNode*>;
TNode::TNode(const string& v) : value(v), left(nullptr), right(nullptr) {}

CompleteBinaryTree::CompleteBinaryTree() : size(0), root(nullptr) {}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear(root);
}

void CompleteBinaryTree::clear(TNode* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void CompleteBinaryTree::insert(const string& value) {
    TNode* node = new TNode(value);
    if (root == nullptr) {
        root = node;
        ++size;
        return;
    }
    
    Queue<TNode*> q;
    q.push(root);
    
    while (q.Qsize() > 0) {
        TNode* cur = q.peek();
        q.pop();
        
        if (cur->left == nullptr) {
            cur->left = node;
            ++size;
            return;
        } else {
            q.push(cur->left);
        }
        
        if (cur->right == nullptr) {
            cur->right = node;
            ++size;
            return;
        } else {
            q.push(cur->right);
        }
    }
}

bool CompleteBinaryTree::isComplete() const { 
    if (root == nullptr) return true;
    
    Queue<TNode*> q;
    q.push(root);
    bool seenEmpty = false;
    
    while (q.Qsize() > 0) {
        TNode* cur = q.peek();
        q.pop();
        
        if (cur->left != nullptr) {
            if (seenEmpty) return false;
            q.push(cur->left);
        } else {
            seenEmpty = true;
        }
        
        if (cur->right != nullptr) {
            if (seenEmpty) return false;
            q.push(cur->right);
        } else {
            seenEmpty = true;
        }
    }
    return true;
}

bool CompleteBinaryTree::search(const string& value) const { 
    return searchRec(root, value);
}

bool CompleteBinaryTree::searchRec(TNode* node, const string& value) const { 
    if (node == nullptr) return false;
    if (node->value == value) return true;
    return searchRec(node->left, value) || searchRec(node->right, value);
}

void CompleteBinaryTree::print() const { 
    if (root == nullptr) {
        cout << "tree is empty" << endl;
        return;
    }
    PrintTreeRec(root, 0);
}

void CompleteBinaryTree::PrintTreeRec(TNode* node, int level) const { 
    if (node == nullptr) return;
    PrintTreeRec(node->right, level + 1);
    for (int i = 0; i < level; i++) cout << "    "; 
    cout << node->value << endl;
    PrintTreeRec(node->left, level + 1);
}

int CompleteBinaryTree::getsize() const { 
    return size;
}

string CompleteBinaryTree::ToString() const { 
    string res;
    if (root == nullptr) return res;
    
    Queue<TNode*> q;
    q.push(root);
    
    while (q.Qsize() > 0) {
        TNode* cur = q.peek();
        q.pop();
        
        if (!res.empty()) res += " ";
        res += cur->value;
        
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return res;
}