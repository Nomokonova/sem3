#include "Tree.h"
using namespace std;

TNode::TNode(const string& v):value(v),left(nullptr),right(nullptr){}
TQueue::TQueue():head(nullptr), tail(nullptr) {}
TQueue::~TQueue() {
	while (head != nullptr) {
		TQNode* tmp = head;
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}
void TQueue::push(TNode* val) {
	TQNode* n = new TQNode(val);
	if (head == nullptr) {
		head = n;
		tail = n;
	}
	else {
		tail->next = n;
		tail = n;
	}
}
void TQueue::pop() {
	if (head == nullptr) return;
	TQNode* tmp = head;
	head = head->next;
	delete tmp;
	if (head == nullptr)
		tail = nullptr;
}
TNode* TQueue::front() {
	if (head == nullptr) return nullptr;
	return head->value;
}
bool TQueue::empty() {
	return head == nullptr;
}
//создание
CompleteBinaryTree::CompleteBinaryTree() :size(0),root(nullptr){}
//деструктор
CompleteBinaryTree::~CompleteBinaryTree() {
	clear(root);
}
void CompleteBinaryTree::clear(TNode* node) {
	if (node == nullptr) return;
	clear(node->left);
	clear(node->right);
	delete node;
}
//добавление
void CompleteBinaryTree::insert(const string& value) {
	TNode* node = new TNode(value);
	if (root == nullptr) {
		root = node;
		++size;
		return;
	}
	TQueue q;
	q.push(root);
	while (q.empty() == false) {
		TNode* cur = q.front();
		q.pop();
		if (cur->left == nullptr) {
			cur->left = node;
			++size;
			return;
		}
		else {
			q.push(cur->left);
		}
		if (cur->right == nullptr) {
			cur->right = node;
			++size;
			return;
		}
		else {
			q.push(cur->right);
		}
	}
}
bool CompleteBinaryTree::isComplete() {
	if (root == nullptr)
		return true;
	TQueue q;
	q.push(root);
	bool seenEmpty = false;
	while (q.empty() == false) {
		TNode* cur = q.front();
		q.pop();
		if (cur->left != nullptr) {
			if (seenEmpty)
				return false;
			q.push(cur->left);
		}
		else {
			seenEmpty = true;
		}
		if (cur->right != nullptr) {
			if (seenEmpty)
				return false;
			q.push(cur->right);
		}
		else {
			seenEmpty = true;
		}
	}
	return true;
}
//поиск
bool CompleteBinaryTree::search(const string& value) {
	return searchRec(root, value);
}
bool CompleteBinaryTree::searchRec(TNode* node,const string& value) {
	if (node == nullptr) return false;
	if (node->value == value) return true;
	return searchRec(node->left, value) || searchRec(node->right, value);
}
//вывод
void CompleteBinaryTree::print() {
	if (root == nullptr) {
		cout << "tree is empty" << endl;
		return;
	}
	PrintTreeRec(root, 0);
}
void CompleteBinaryTree::PrintTreeRec(TNode* node, int level) {
    if (node == nullptr) return;
    PrintTreeRec(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        cout << "    "; 
    }
    cout << node->value << endl;
    PrintTreeRec(node->left, level + 1);
}
//размер
int CompleteBinaryTree::getsize() {
	return size;
}

string CompleteBinaryTree::ToString(){
	string res;
    if (root == nullptr) return res;
    
    TQueue q;
    q.push(root);
    while (!q.empty()) {
        TNode* cur = q.front();
        q.pop();
        if (!res.empty()) res += " ";
        res += cur->value;
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return res;
}
