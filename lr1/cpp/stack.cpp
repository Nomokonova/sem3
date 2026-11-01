#include "stack.h"
using namespace std;

StackNode::StackNode(const string& v): value(v), next(nullptr){}
Stack::Stack() :top(nullptr){}
Stack::~Stack() {
	while (top != nullptr) {
		StackNode* tmp = top;
		top = top->next;
		delete tmp;
	}
}
//добавление
void Stack::push(const string& value) {
	StackNode* n = new StackNode(value);
	n->next = top;
	top = n;
}
//удаление
string Stack::pop() {
	if (top == nullptr){
		cout << "error" << endl;
		return "";
	}
	string rem = top->value;
	StackNode* tmp = top;
	top = top->next;
	delete tmp;
	return rem;
}
//чтение
string Stack::peek() {
	if (top == nullptr)
		return "";
	return top->value;
}
//вывод
void Stack::print() {
	if (top == nullptr) {
		cout << "stack is empty" << endl;
		return;
	}
	StackNode* tmp = top;
	while (tmp != nullptr) {
		cout << tmp->value << " ";
		tmp = tmp->next;
	}
	cout << endl;
}
//размер
int Stack::StackSize() {
	int cnt = 0;
	StackNode* n = top;
	while (n != nullptr) {
		++cnt;
		n = n->next;
	}
	return cnt;
}

string Stack::ToString(){
	string res;
	StackNode* cur = top;
	while(cur!=nullptr){
		if(!res.empty()) res = " " + res;
		res = cur->value + res;
		cur = cur->next;
	}
	return res;
}
