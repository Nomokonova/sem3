#include "Queue.h"
using namespace std;

QNode::QNode(const string& v):value(v), next(nullptr){}
//создание
Queue::Queue():head(nullptr),tail(nullptr){}
//деструктор
Queue::~Queue() {
	while (head != nullptr) {
		QNode* tmp = head;
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}
//добавление
void Queue::push(const string& value) {
	QNode* n = new QNode(value);
	if (head == nullptr) {
		head = n;
		tail = n;
	}
	else {
		tail->next = n;
		tail = n;
	}
}
//удаление
string Queue::pop() {
	if (head == nullptr){
		cout << "error" << endl;
		return "";
	}
	string rem = head->value;
	QNode* tmp = head;
	head = head->next;
	delete tmp;
	if (head == nullptr) tail = nullptr;
	return rem;
}
//чтение
string Queue::peek() {
	if (head == nullptr) {
		return "";
	}
	return head->value;
}
string Queue::back() {
	if (tail == nullptr) {
		return "";
	}
	return tail->value;
}
void Queue::print() {
	if (head == nullptr) {
		cout << "queue is empty" << endl;
		return;
	}
	QNode* n = head;
	while (n != nullptr) {
		cout << n->value << " ";
		n = n->next;
	}
	cout << endl;
}
int Queue::Qsize() {
	int cnt = 0;
	QNode* n = head;
	while (n != nullptr) {
		++cnt;
		n = n->next;
	}
	return cnt;
}

string Queue::ToString(){
	string res;
    QNode* cur = head;
    while (cur != nullptr) {
        if (!res.empty()) res += " ";
        res += cur->value;
        cur = cur->next;
    }
    return res;
}
