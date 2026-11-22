#define BOOST_TEST_MODULE Lab3Tests
#include <boost/test/included/unit_test.hpp>
#include <string>
#include "array.h"
#include "SList.h"
#include "DList.h"
#include "stack.h"
#include "Queue.h"
#include "hash.h"
#include "tree.h"

//---------------тесты для массива
BOOST_AUTO_TEST_CASE(ArrayPushBack) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("B");
    BOOST_TEST(arr.getSize()==2);
    BOOST_TEST(arr.getString(0)=="A");
    BOOST_TEST(arr.getString(1)=="B");
}

BOOST_AUTO_TEST_CASE(ArrayInsert) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("C");
    arr.insert(1, "B"); 
    BOOST_TEST(arr.getSize()==3);
    BOOST_TEST(arr.getString(1)=="B");
}

BOOST_AUTO_TEST_CASE(ArrayErase) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("B");
    std::string removed = arr.erase(0);
    BOOST_TEST(removed=="A");
    BOOST_TEST(arr.getSize()==1);
    BOOST_TEST(arr.getString(0)=="B");
}

BOOST_AUTO_TEST_CASE(ArrayToString) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("B");
    BOOST_TEST(arr.ToString()=="A B");
}
BOOST_AUTO_TEST_CASE(EdgeCasesAndErrorsArray) {
    Array arr;
    arr.print();             
    arr.get(10);             
    arr.erase(10);           
    arr.set(10, "X"); 
}
//-------------------тесты для односвязного списка
BOOST_AUTO_TEST_CASE(PushFrontAndBack){
    SinglyLinkedList list;
    list.pushFront("A");
    list.pushBack("B");
    list.pushBack("C");
    BOOST_TEST(list.findVal("A")==0);
    BOOST_TEST(list.findVal("B")==1);
    BOOST_TEST(list.findVal("C")==2);
}
BOOST_AUTO_TEST_CASE(Insert) {
    SinglyLinkedList list;
    list.pushBack("A");
    list.pushBack("C");
    list.insertBefore("C", "B"); 
    list.insertAfter("C", "D");  
    BOOST_TEST(list.findVal("B")==1);
    BOOST_TEST(list.findVal("D")==3);
}
BOOST_AUTO_TEST_CASE(Delete){
    SinglyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    list.pushBack("D");

    BOOST_TEST(list.deleteValue("B")=="B"); 
    BOOST_TEST(list.findVal("B")==-1);      
    BOOST_TEST(list.findVal("C")==1);
    BOOST_TEST(list.popFront()=="A");       
    BOOST_TEST(list.findVal("A")==-1);

    list.insertBefore("C", "B");
     
    list.pushFront("A");
    BOOST_TEST(list.deleteBefore("D")=="C");

    SinglyLinkedList list1;
    list1.pushBack("A");
    list1.pushBack("B");
    list1.pushBack("C"); 
    BOOST_TEST(list1.popBack() == "C"); 

    SinglyLinkedList list2;
    list2.pushBack("X");
    list2.pushBack("Y");
    list2.pushBack("Z");
    BOOST_TEST(list2.deleteAfter("X") == "Y"); 

    SinglyLinkedList list3;
    list3.pushBack("A");
    list3.pushBack("B"); 
    list3.pushBack("C"); 
    BOOST_TEST(list3.deleteBefore("B") == "A");
}

BOOST_AUTO_TEST_CASE(ToStringCheckSList) {
    SinglyLinkedList list;
    list.pushBack("apple");
    list.pushBack("banana");
    BOOST_TEST(list.ToString()=="apple banana");
}

BOOST_AUTO_TEST_CASE(EdgeCasesAndErrorsSList) {
    SinglyLinkedList sList;
    sList.print();           
    sList.printReverse();    
    sList.getHead();         
    sList.getTail();
    sList.getVal(0);
    sList.getVal(-1);       
    sList.popFront();        
    sList.popBack();  
    sList.insertBefore("A","B");
    sList.insertAfter("A","C");       
    sList.deleteValue("Z");  
    sList.deleteBefore("Z"); 
    sList.deleteAfter("Z");

    sList.pushFront("A");
    sList.popBack();

    sList.pushFront("A");
    sList.popFront();
}

//------------тесты для двусвязного списка 
BOOST_AUTO_TEST_CASE(InsertBeforeAfter){
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("C");
    list.insertBefore("C", "B"); 
    list.insertAfter("C", "D");  
    BOOST_TEST(list.findVal("B")==1);
    BOOST_TEST(list.findVal("D")==3);
}

BOOST_AUTO_TEST_CASE(PopFrontBack){
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    BOOST_TEST(list.popFront()=="A");
    BOOST_TEST(list.popBack()=="C");
    BOOST_TEST(list.findVal("B")==0); 
}

BOOST_AUTO_TEST_CASE(ToStringCheckDList){
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    BOOST_TEST(list.ToString()=="A B");
}
BOOST_AUTO_TEST_CASE(AllMethodsDList) {
    DoublyLinkedList list;
    list.pushFront("B");
    list.pushBack("C");
    list.insertBefore("B", "A"); 
    list.insertAfter("C", "D");

    BOOST_TEST(list.findVal("C")==2);
    list.findInd(1); 

    BOOST_TEST(list.deleteBefore("B")=="A"); 
    BOOST_TEST(list.deleteAfter("C")=="D");  
    BOOST_TEST(list.deleteValue("B")=="B");  

    list.getHead();
    list.getTail();
    list.print();
    list.printReverse();
    
    list.popFront(); 
}

BOOST_AUTO_TEST_CASE(EdgeCasesAndErrorsDList) {
    DoublyLinkedList dList;
    dList.print();           
    dList.printReverse();    
    dList.getHead();         
    dList.getTail();         
    dList.popFront();        
    dList.popBack();         
    dList.deleteValue("Z");  
    dList.deleteBefore("Z"); 
    dList.deleteAfter("Z");
}

//-------------тесты для стека
BOOST_AUTO_TEST_CASE(PushPopPeek){
    Stack st;
    st.push("A");
    st.push("B");
    BOOST_TEST(st.peek()=="B");
    BOOST_TEST(st.StackSize()==2);
    BOOST_TEST(st.pop()=="B");
    BOOST_TEST(st.peek()=="A");
    BOOST_TEST(st.StackSize()==1);
}

BOOST_AUTO_TEST_CASE(EmptyPop){
    Stack st;
    BOOST_TEST(st.pop()=="");
    BOOST_TEST(st.StackSize()==0);
}

BOOST_AUTO_TEST_CASE(PrintStack){
    Stack st;
    st.push("A");
    st.push("B");
    st.push("C");
    st.print();
}

BOOST_AUTO_TEST_CASE(ToStringCheckStack){
    Stack st;
    st.push("A");
    st.push("B");
    BOOST_TEST(st.ToString()=="A B");
}

//----------------тесты для очереди
BOOST_AUTO_TEST_CASE(PushPopQueue){
    Queue<std::string> q;
    q.push("first");
    q.push("second");
    BOOST_TEST(q.Qsize()==2);
    BOOST_TEST(q.peek()=="first");
    BOOST_TEST(q.pop()=="first");
    BOOST_TEST(q.Qsize()==1);
    BOOST_TEST(q.back()=="second");
}

BOOST_AUTO_TEST_CASE(ToStringCheckQueue){
    Queue<std::string> q;
    q.push("A");
    q.push("B");
    BOOST_TEST(q.ToString()=="A B");
}

BOOST_AUTO_TEST_CASE(EmptyAndErrorsQueue){
    Queue<std::string> q;
    q.pop();                 
    q.peek();                
    q.back();                
    q.print(); 
}
//-----------тесты для дерева
BOOST_AUTO_TEST_CASE(InsertAndSearch) {
    CompleteBinaryTree tree;
    tree.insert("A");
    tree.insert("B");
    tree.insert("C");
    BOOST_TEST(tree.search("B"));
    BOOST_TEST(!tree.search("Z"));
    BOOST_TEST(tree.getsize()==3);
}

BOOST_AUTO_TEST_CASE(IsComplete) {
    CompleteBinaryTree tree;
    tree.insert("1");
    tree.insert("2");
    tree.insert("3"); 
    BOOST_TEST(tree.isComplete());
}

BOOST_AUTO_TEST_CASE(ToStringCheckTree) {
    CompleteBinaryTree tree;
    tree.insert("A");
    tree.insert("B");
    tree.insert("C");
    BOOST_TEST(tree.ToString()=="A B C");
}

BOOST_AUTO_TEST_CASE(EmptyAndErrorsTree) {
    CompleteBinaryTree tree;
    tree.print();            
    tree.search("Z");        
    tree.isComplete(); 
}
//---------------тесты для хэш таблицы
BOOST_AUTO_TEST_CASE(InsertSearchHash) {
    HashTable ht(10);
    ht.insert(5, "five");
    ht.insert(15, "fifteen");
    BOOST_TEST(ht.search(5)=="five");
    BOOST_TEST(ht.search(15)=="fifteen");
    BOOST_TEST(ht.search(99)==""); 
}

BOOST_AUTO_TEST_CASE(UpdateValue) {
    HashTable ht(10);
    ht.insert(5, "five");
    ht.insert(5, "FIVE_NEW"); 
    BOOST_TEST(ht.search(5)=="FIVE_NEW");
}

BOOST_AUTO_TEST_CASE(ToStringCheckHash) {
    HashTable ht(10);
    ht.insert(1, "A");
    ht.insert(2, "B");
    BOOST_TEST(ht.ToString() == "1:A 2:B");
}
BOOST_AUTO_TEST_CASE(EmptyAndErrorsHash){
    HashTable ht(5);
    ht.search(999);          
    ht.print(); 
}
