#include "Queue.h"
#include "tree.h"
using namespace std;

template <typename T>
QNode<T>::QNode(const T& v) : value(v), next(nullptr) {}
//создание
template <typename T>
Queue<T>::Queue() : head(nullptr), tail(nullptr) {}
//деструктор
template <typename T>
Queue<T>::~Queue() {
	while (head != nullptr) {
		QNode<T>* tmp = head;
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}
//добавление
template <typename T>
void Queue<T>::push(const T& value) {
	QNode<T>* n = new QNode<T>(value);
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
template <typename T>
T Queue<T>::pop() {
	if (head == nullptr){
		cout << "error" << endl;
		return T();
	}
	T rem = head->value;
	QNode<T>* tmp = head;
	head = head->next;
	delete tmp;
	if (head == nullptr) tail = nullptr;
	return rem;
}
//чтение
template <typename T>
T Queue<T>::peek() const{
	if (head == nullptr) {
		return T();
	}
	return head->value;
}
template <typename T>
T Queue<T>::back() const{
	if (tail == nullptr) {
		return T();
	}
	return tail->value;
}
template <typename T>
void Queue<T>::print() const{
	if (head == nullptr) {
		cout << "queue is empty" << endl;
		return;
	}
	QNode<T>* n = head;
	while (n != nullptr) {
		cout << n->value << " ";
		n = n->next;
	}
	cout << endl;
}
template <typename T>
int Queue<T>::Qsize() const{
	int cnt = 0;
	QNode<T>* n = head;
	while (n != nullptr) {
		++cnt;
		n = n->next;
	}
	return cnt;
}
template <typename T>
string Queue<T>::ToString() const{
	string res;
    QNode<T>* cur = head;
    while (cur != nullptr) {
        if (!res.empty()) res += " ";
        if constexpr (!std::is_pointer_v<T>) {
            res += cur->value;
        }
        cur = cur->next;
    }
    return res;
}
template class Queue<std::string>;
template class Queue<TNode*>;