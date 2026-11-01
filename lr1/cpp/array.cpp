#include "array.h"
using namespace std;

//создание
Array::Array() : data(nullptr), capacity (0), size (0){}
Array::~Array() {
    delete[] data;
}

void Array::resize() {
    if (size < capacity) return;
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    string* newData = new string[newCapacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}
//добавление по индексу
void Array::insert(int index, const string& value) {
    if (index > size || index < 0){
        cout<< "Error"<< endl;
        return;
    }
    if (size == capacity) resize();
    for (int i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}
//добавление в конец
void Array::pushBack(const string& value) {
    if (size == capacity) resize();
    data[size] = value;
    size++;
}
//получение по индексу
void Array::get(int index) {
    if (index < 0 || index >= size){
        cout<< "error" << endl;
        return;
    }
    cout << data[index] << endl;
}
//удаление по индексу
string Array::erase(int index) {
    if (index < 0 || index >= size){
        cout << "error" << endl;
        return "";
    }
    string remVal = data[index];
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
    return remVal;
}
//замена элемента по индексу
void Array::set(int index, const string& value) {
    if (index < 0 || index >= size){
        cout << "error" << endl;
        return;
    }
    data[index] = value;
}
//длина массива
int Array::getSize() {
    return size;
}
//чтение
void Array::print() {
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}
string Array::ToString(){
    string res = "";
    for (int i = 0; i < size; ++i) {
        if (i > 0) res += " ";
        res += data[i];
    }
    return res;
}
string Array::getString(int index) {
    if (index < 0 || index >= size) return "";
    return data[index];
}
