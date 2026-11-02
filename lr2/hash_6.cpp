#include <iostream>
#include <string>
#include <ctime>
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

double msSince(clock_t start) {
    return (double)(clock() - start) * 1000 / CLOCKS_PER_SEC;
}
// Линейное апробирование 
int insertLinear(HashTable* ht, int key, string value) {
    int index = hashFunc(key) % ht->capacity;
    int startIndex = index;
    int steps = 0;
    while (ht->table->getString(index) != "") {
        size_t pos = ht->table->getString(index).find(':');
        int existingKey = stoi(ht->table->getString(index).substr(0, pos));
        if (existingKey == key) {
            ht->table->set(index, to_string(key) + ":" + value);
            return steps;
        }
        index = (index + 1) % ht->capacity; 
        steps++;
        if (index == startIndex) 
            return -1;
    }
    ht->table->set(index, to_string(key) + ":" + value);
    return steps;
}

// Двойное хеширование 
int insertDouble(HashTable* ht, int key, string value) {
    int index = hashFunc(key) % ht->capacity;
    int step = secondHash(key, ht->capacity);
    int startIndex = index;
    int steps = 0;
    while (ht->table->getString(index) != "") {
        size_t pos = ht->table->getString(index).find(':');
        int existingKey = stoi(ht->table->getString(index).substr(0, pos));
        if (existingKey == key) {
            ht->table->set(index, to_string(key) + ":" + value);
            return steps;
        }
        index = (index + step) % ht->capacity; 
        steps++;
        if (index == startIndex) 
            return -1;
    }
    ht->table->set(index, to_string(key) + ":" + value);
    return steps;
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
        
        if (existingKey == key) return entry.substr(pos + 1); 
        
        index = (index + step) % ht->capacity;
        if (index == startIndex) break;
    }
    return ""; 
}
string toRoman(int num, HashTable* romanTable) {
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string result = "";
    for (int i = 0; i < 13; i++) {
        string symbol = search(romanTable, values[i], false); 
        while (num >= values[i]) {
            result += symbol;
            num -= values[i];
        }
    }
    return result;
}

int main() {
    cout << "6.1 Эмпирический анализ" << endl;
    cout << "N\tLinear(ms)\tDouble(ms)\tLinear(Steps)\tDouble(Steps)" << endl;

    int sizes[] = {100, 1000, 5000}; 

    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        HashTable* htLin = createTable(n);
        HashTable* htDbl = createTable(n);
        
        int stepsLin = 0, stepsDbl = 0;

        //замер линейного
        clock_t start = clock();
        for (int i = 0; i < n; i++) {
            stepsLin += insertLinear(htLin, i * 10, "x"); 
        }
        double timeLin = msSince(start);

        //замер двойного
        start = clock();
        for (int i = 0; i < n; i++) {
            stepsDbl += insertDouble(htDbl, i * 10, "x");
        }
        double timeDbl = msSince(start);

        cout << n << "\t" << timeLin << "\t\t" << timeDbl << "\t\t" << stepsLin << "\t\t" << stepsDbl << endl;
    }

    cout << "\n6.2 Римские цифры" << endl;
    HashTable* romanTable = createTable(20);
    
    insertLinear(romanTable, 1000, "M");
    insertLinear(romanTable, 900, "CM");
    insertLinear(romanTable, 500, "D");
    insertLinear(romanTable, 400, "CD");
    insertLinear(romanTable, 100, "C");
    insertLinear(romanTable, 90, "XC");
    insertLinear(romanTable, 50, "L");
    insertLinear(romanTable, 40, "XL");
    insertLinear(romanTable, 10, "X");
    insertLinear(romanTable, 9, "IX");
    insertLinear(romanTable, 5, "V");
    insertLinear(romanTable, 4, "IV");
    insertLinear(romanTable, 1, "I");
    HashTable* cache = createTable(10);
    int num;
    while (true) {
        cout << "Введите целое число: ";
        cin >> num;
        if (num == 0) break;
        string cachedRoman = search(cache, num, false); 
        if (cachedRoman != "") {
            cout << "Из кэша: " << cachedRoman << endl;
        } else {
            string roman = toRoman(num, romanTable);
            cout << "Результат: " << roman << endl;
            insertLinear(cache, num, roman);
            insertDouble(cache, num, roman);
        }
    }
    return 0;
}