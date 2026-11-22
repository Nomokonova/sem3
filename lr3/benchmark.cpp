#include <iostream>
#include <chrono>
#include "array.h"
#include "SList.h"
#include "DList.h"
#include "hash.h"
#include "tree.h"
#include "stack.h"
#include "Queue.h"
using namespace std;
using namespace std::chrono;

int main(){
    int N = 10000; 
    int N_tree = 1000; 
    //массив
    {
        Array arr;
        auto start = high_resolution_clock::now();
        for(int i=0; i < N; i++) arr.pushBack("test");
        auto end = high_resolution_clock::now();
        double insertTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for(int i=0; i < N; i++) arr.getString(i);
        end = high_resolution_clock::now();
        double searchTime = duration<double, milli>(end - start).count();
        
        start = high_resolution_clock::now();
        for(int i=0; i < N; i++) arr.erase(0);
        end = high_resolution_clock::now();
        double eraseTime = duration<double, milli>(end - start).count();

        cout << "Array (10k)\t" << insertTime << "\t\t"
        << searchTime << "\t\t" << eraseTime << endl;
    } 
    //односвязный список 
    {
        SinglyLinkedList SList;
        auto start = high_resolution_clock::now();
        for(int i=0; i < N; i++) SList.pushFront("test");
        auto end = high_resolution_clock::now();
        double insertTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for(int i=0; i < N; i++) SList.findVal("test");
        end = high_resolution_clock::now();
        double searchTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for(int i=0; i < N; i++) SList.popFront();
        end = high_resolution_clock::now();
        double eraseTime = duration<double, milli>(end - start).count();
        cout << "SList (10k)\t" << insertTime << "\t\t"
        << searchTime << "\t\t" << eraseTime << endl;
    }
    //двусвязный список 
    {
        DoublyLinkedList DList;
        auto start = high_resolution_clock::now();
        for(int i=0; i < N; i++) DList.pushFront("test");
        auto end = high_resolution_clock::now();
        double insertTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for(int i=0; i < N; i++) DList.findVal("test");
        end = high_resolution_clock::now();
        double searchTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for(int i=0; i < N; i++) DList.popFront();
        end = high_resolution_clock::now();
        double eraseTime = duration<double, milli>(end - start).count();
        cout << "DList (10k)\t" << insertTime << "\t\t"
        << searchTime << "\t\t" << eraseTime << endl;
    }
    //хэш таблица 
    {
        HashTable ht(N);
        auto start = high_resolution_clock::now();
        for(int i=0; i < N; i++) ht.insert(i, "test");
        auto end = high_resolution_clock::now();
        double insertTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for(int i=0; i < N; i++) ht.search(i);
        end = high_resolution_clock::now();
        double searchTime = duration<double, milli>(end - start).count();

        cout << "HashTable\t" << insertTime << "\t\t" 
        << searchTime << "\t\t-" << endl;
    }
    //дерево 
    {
        CompleteBinaryTree tree;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N_tree; i++) tree.insert("test");
        auto end = high_resolution_clock::now();
        double insertTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (int i = 0; i < N_tree; i++) tree.search("test");
        end = high_resolution_clock::now();
        double searchTime = duration<double, milli>(end - start).count();

        cout << "Tree (1k)\t" << insertTime << "\t\t" << searchTime
         << "\t\t-" << endl;
    }
    //стек 
    {
        Stack st;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) st.push("test");
        auto end = high_resolution_clock::now();
        double insertTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) st.pop();
        end = high_resolution_clock::now();
        double eraseTime = duration<double, milli>(end - start).count();

        cout << "Stack (10k)\t" << insertTime << "\t\t-\t\t"
        << eraseTime << endl;
    }
    //очередь
    {
        Queue<std::string> q;
        auto start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) q.push("test");
        auto end = high_resolution_clock::now();
        double insertTime = duration<double, milli>(end - start).count();

        start = high_resolution_clock::now();
        for (int i = 0; i < N; i++) q.pop();
        end = high_resolution_clock::now();
        double eraseTime = duration<double, milli>(end - start).count();

        cout << "Queue (10k)\t" << insertTime << "\t\t-\t\t"
        << eraseTime << endl;
    }
    return 0;
}