#include <iostream>
#include <string>
#include "array.h" 
using namespace std;

struct HashTable {
    Array* table; 
    int capacity;
};
HashTable* createTable(int capacity) {
    HashTable* ht = new HashTable;
    ht->capacity = capacity;
    ht->table = new Array(); 
    for (int i = 0; i < capacity; i++) {
        ht->table->pushBack("");
    }
    return ht;
}
int hashFunc(int key) {
    return key % 100; 
}
int secondHash(int key, int capacity) {
    return 1 + (key % (capacity - 1));
}

string toRoman(int num) {
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    string result = "";
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            result += symbols[i];
            num -= values[i];
        }
    }
    return result;
}

// Линейное апробирование 
void insertLinear(HashTable* ht, int key, string value) {
    int index = hashFunc(key) % ht->capacity;
    int startIndex = index;
    
    while (ht->table->getString(index) != "") {
        size_t pos = ht->table->getString(index).find(':');
        int existingKey = stoi(ht->table->getString(index).substr(0, pos));
        if (existingKey == key) {
            ht->table->set(index, to_string(key) + ":" + value);
            return;
        }
        index = (index + 1) % ht->capacity; 
        if (index == startIndex) {
            cout << "Таблица заполнена!" << endl;
            return;
        }
    }
    ht->table->set(index, to_string(key) + ":" + value);
}

// Двойное хеширование 
void insertDouble(HashTable* ht, int key, string value) {
    int index = hashFunc(key) % ht->capacity;
    int step = secondHash(key, ht->capacity);
    int startIndex = index;
    
    while (ht->table->getString(index) != "") {
        size_t pos = ht->table->getString(index).find(':');
        int existingKey = stoi(ht->table->getString(index).substr(0, pos));
        if (existingKey == key) {
            ht->table->set(index, to_string(key) + ":" + value);
            return;
        }
        index = (index + step) % ht->capacity; 
        if (index == startIndex) {
            cout << "Таблица заполнена!" << endl;
            return;
        }
    }
    ht->table->set(index, to_string(key) + ":" + value);
}

// Поиск в таблице
string search(HashTable* ht, int key, bool isDouble) {
    int index = hashFunc(key) % ht->capacity;
    int step = isDouble ? secondHash(key, ht->capacity) : 1;
    int startIndex = index;

    while (ht->table->getString(index) != "") {
        string entry = ht->table->getString(index);
        size_t pos = entry.find(':');
        int existingKey = stoi(entry.substr(0, pos));
        
        if (existingKey == key) {
            return entry.substr(pos + 1); 
        }
        index = (index + step) % ht->capacity;
        if (index == startIndex) break;
    }
    return ""; 
}

int main() {
    int capacity = 10;
    HashTable* htLinear = createTable(capacity);
    HashTable* htDouble = createTable(capacity);
    cout << "6.1 эмпирический анализ ( 10, 15, 20, 25)" << endl;

    insertLinear(htLinear, 10, "x");
    insertDouble(htDouble, 10, "x");

    insertLinear(htLinear, 15, "x"); 
    insertDouble(htDouble, 15, "x");

    insertLinear(htLinear, 20, "x"); 
    insertDouble(htDouble, 20, "x");

    insertLinear(htLinear, 25, "x"); 
    insertDouble(htDouble, 25, "x");
    cout << "Результат распределения в Линейной таблице " << endl;
    for (int i = 0; i < capacity; i++) {
        if (htLinear->table->getString(i) != "") 
            cout << "[" << i << "]: " << htLinear->table->getString(i) << endl;
    }
    
    cout << "Результат распределения в Двойной таблице" << endl;
    for (int i = 0; i < capacity; i++) {
        if (htDouble->table->getString(i) != "") 
            cout << "[" << i << "]: " << htDouble->table->getString(i) << endl;
    }
    int num;
    cout << "Введите целое число для перевода в римскую систему: ";
    cin >> num;
    string cachedRoman = search(htLinear, num, false);
    if (cachedRoman != "") {
        cout << "Из кэша: " << cachedRoman << endl;
    } else {
        string roman = toRoman(num);
        cout << "Результат: " << roman << endl;

        insertLinear(htLinear, num, roman);
        insertDouble(htDouble, num, roman);
    }
}