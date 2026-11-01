#include <iostream>
#include "Tree.h"
using namespace std;

TNode* insertBST(TNode* root, int value){
    if(root == nullptr)
        return new TNode(to_string(value));
    int curVal = stoi(root->value);
    if(value < curVal){
        root->left = insertBST(root->left, value);
    }
    else if(value>curVal){
        root->right = insertBST(root->right, value);
    }
    return root;
}
int getHeight(TNode* root){
    if(root == nullptr) return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return max(leftHeight, rightHeight) + 1;   
}
bool isAVL(TNode* root){
    if(root == nullptr) return true;
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    if(abs(leftH-rightH) > 1)
        return false;
    return isAVL(root->left) && isAVL(root->right);
}
void delTree(TNode* root){
    if(root == nullptr) return;
    delTree(root->left);
    delTree(root->right);
    delete root;
}
int main(){
    TNode* root = nullptr;
    int num;
    cout <<  "Enter num (0 to stop) ";
    while(cin >> num && num != 0){
        root = insertBST(root, num);
    }
    if(isAVL(root)){
        cout << "yes" << endl;
    }else{
        cout << "no" << endl;
    }
    delTree(root);
}