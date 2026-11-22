#include <gtest/gtest.h>
#include <string>
#include "array.h"
#include "SList.h"
#include "DList.h"
#include "stack.h"
#include "Queue.h"
#include "hash.h"
#include "tree.h"

//-------------тесты для массива
TEST(ArrayTest, PushBack) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("B");
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.getString(0), "A");
    EXPECT_EQ(arr.getString(1), "B");
}
TEST(ArrayTest, Insert) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("C");
    arr.insert(1, "B"); 
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr.getString(1), "B");
}
TEST(ArrayTest, Erase) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("B");
    std::string removed = arr.erase(0);
    EXPECT_EQ(removed, "A");
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_EQ(arr.getString(0), "B");
}
TEST(ArrayTest, ToString) {
    Array arr;
    arr.pushBack("A");
    arr.pushBack("B");
    EXPECT_EQ(arr.ToString(), "A B");
}
TEST(ArrayTest, EdgeCasesAndErrors) {
    Array arr;
    arr.print();             
    EXPECT_NO_THROW(arr.get(10));             
    EXPECT_EQ(arr.erase(10), "");           
    EXPECT_NO_THROW(arr.set(10, "X"));        
    EXPECT_EQ(arr.getSize(), 0);
}
//-------------------тесты для односвязного списка
TEST(SListTest, PushFrontAndBack){
    SinglyLinkedList list;
    list.pushFront("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.findVal("A"), 0);
    EXPECT_EQ(list.findVal("B"), 1);
    EXPECT_EQ(list.findVal("C"), 2);
}
TEST(SListTest, Insert) {
    SinglyLinkedList list;
    list.pushBack("A");
    list.pushBack("C");
    //вставки
    list.insertBefore("C", "B"); 
    list.insertAfter("C", "D");  
    EXPECT_EQ(list.findVal("B"), 1);
    EXPECT_EQ(list.findVal("D"), 3);
    //вспомогательные методы
    list.getVal(0); 
    list.getHead(); 
    list.getTail(); 
    list.print();   
    list.printReverse(); 
}
TEST(SListTest, Delete){
    SinglyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    //удаление по значению
    EXPECT_EQ(list.deleteValue("B"), "B"); 
    EXPECT_EQ(list.findVal("B"), -1);      
    EXPECT_EQ(list.findVal("C"), 1);
    //удаление с концов
    EXPECT_EQ(list.popFront(), "A");       
    EXPECT_EQ(list.findVal("A"), -1);
    EXPECT_EQ(list.popBack(), "C");
}
TEST(SListTest, DeleteBeforeAfter) {
    SinglyLinkedList list;
    list.pushBack("A");
    list.pushBack("C");
    list.insertBefore("C", "B"); 
    list.insertAfter("C", "D");  
    //удаление до и после
    EXPECT_EQ(list.deleteBefore("C"), "B"); 
    EXPECT_EQ(list.deleteAfter("C"), "D");  
}
TEST(SListTest, ToStringCheck) {
    SinglyLinkedList list;
    list.pushBack("apple");
    list.pushBack("banana");
    EXPECT_EQ(list.ToString(), "apple banana");
}
TEST(SListTest, EdgeCasesAndErrors) {
    SinglyLinkedList sList;
    sList.print();           
    sList.printReverse();    
    sList.getHead();         
    sList.getTail();         
    sList.popFront();        
    sList.popBack();         
    EXPECT_EQ(sList.deleteValue("Z"), "");  
    sList.deleteBefore("Z"); 
    sList.deleteAfter("Z");  
    EXPECT_EQ(sList.findVal("Z"), -1);
    sList.insertBefore("Z", "A"); 
    sList.insertAfter("Z", "A");  
    sList.getVal(10);  
}
//------------тесты для двусвязного списка 
TEST(DListTest, InsertBeforeAfter){
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("C");
    list.insertBefore("C", "B"); 
    list.insertAfter("C", "D");  
    EXPECT_EQ(list.findVal("B"), 1);
    EXPECT_EQ(list.findVal("D"), 3);
}
TEST(DListTest, PopFrontBack){
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    list.pushBack("C");
    EXPECT_EQ(list.popFront(),"A");
    EXPECT_EQ(list.popBack(), "C");
    EXPECT_EQ(list.findVal("B"),0); 
}
TEST(DListTest, DeleteBeforeAfter) {
    DoublyLinkedList list;
    list.pushFront("B");
    list.pushBack("C");
    list.insertBefore("B", "A"); 
    list.insertAfter("C", "D");
    //удаления
    EXPECT_EQ(list.deleteBefore("B"), "A"); 
    EXPECT_EQ(list.deleteAfter("C"), "D");  
    EXPECT_EQ(list.deleteValue("B"), "B");  
    //вспомогательные методы
    list.getHead();
    list.getTail();
    list.findInd(1); 
    list.print();
    list.printReverse();
    list.popFront(); 
}
TEST(DListTest, ToStringCheck){
    DoublyLinkedList list;
    list.pushBack("A");
    list.pushBack("B");
    EXPECT_EQ(list.ToString(),"A B");
}
TEST(DListTest, EdgeCasesAndErrors) {
    DoublyLinkedList dList;
    dList.print();
    dList.printReverse();
    EXPECT_EQ(dList.findVal("Z"), -1);
    dList.insertBefore("A", "B"); 
    dList.insertAfter("A", "B");
    dList.deleteValue("Z");       
    dList.deleteBefore("Z");      
    dList.deleteAfter("Z");       
    dList.insertBefore("Z", "A"); 
    dList.insertAfter("Z", "A");            
    dList.findInd(10);            
}
//-------------тесты для стека
TEST(Stack, PushPopPeek){
    Stack st;
    st.push("A");
    st.push("B");
    EXPECT_EQ(st.peek(),"B");
    EXPECT_EQ(st.StackSize(),2);
    EXPECT_EQ(st.pop(),"B");
    EXPECT_EQ(st.peek(),"A");
    EXPECT_EQ(st.StackSize(),1);
}
TEST(Stack, EmptyPop){
    Stack st;
    EXPECT_EQ(st.pop(),"");
    EXPECT_EQ(st.StackSize(),0);
}
TEST(Stack, ToStringCheck){
    Stack st;
    st.push("A");
    st.push("B");
    EXPECT_EQ(st.ToString(), "A B");
}
TEST(Stack, EdgeCasesAndErrors) {
    Stack st;
    EXPECT_EQ(st.StackSize(), 0);
    EXPECT_EQ(st.peek(), "");
    st.print(); 
}
//----------------тесты для очереди
TEST(Queue, PushPop){
    Queue<std::string> q;
    q.push("first");
    q.push("second");
    EXPECT_EQ(q.Qsize(),2);
    EXPECT_EQ(q.peek(),"first");
    EXPECT_EQ(q.pop(),"first");
    EXPECT_EQ(q.Qsize(),1);
    EXPECT_EQ(q.back(),"second");
}
TEST(Queue, ToStringCheck){
    Queue<std::string> q;
    q.push("A");
    q.push("B");
    EXPECT_EQ(q.ToString(),"A B");
}
TEST(Queue, EdgeCasesAndErrors) {
    Queue<std::string> q;
    q.pop();                 
    q.peek();                
    q.back();                
    q.print();    
}
//-----------тесты для дерева
TEST(TreeTest, InsertAndSearch) {
    CompleteBinaryTree tree;
    tree.insert("A");
    tree.insert("B");
    tree.insert("C");
    EXPECT_TRUE(tree.search("B"));
    EXPECT_FALSE(tree.search("Z"));
    EXPECT_EQ(tree.getsize(), 3);
}
TEST(TreeTest, IsComplete) {
    CompleteBinaryTree tree;
    tree.insert("1");
    tree.insert("2");
    tree.insert("3"); 
    EXPECT_TRUE(tree.isComplete());
}
TEST(TreeTest, ToStringCheck) {
    CompleteBinaryTree tree;
    tree.insert("A");
    tree.insert("B");
    tree.insert("C");
    EXPECT_EQ(tree.ToString(), "A B C");
}
TEST(TreeTest, EdgeCasesAndErrors) {
    CompleteBinaryTree tree;
    tree.print();            
    EXPECT_FALSE(tree.search("Z"));        
    tree.isComplete();       
}
//---------------тесты для хэш таблицы
TEST(HashTableTest, InsertSearch) {
    HashTable ht(10);
    ht.insert(5, "five");
    ht.insert(15, "fifteen");
    EXPECT_EQ(ht.search(5), "five");
    EXPECT_EQ(ht.search(15), "fifteen");
    EXPECT_EQ(ht.search(99), ""); 
}
TEST(HashTableTest, UpdateValue) {
    HashTable ht(10);
    ht.insert(5, "five");
    ht.insert(5, "FIVE_NEW"); 
    EXPECT_EQ(ht.search(5), "FIVE_NEW");
}
TEST(HashTableTest, ToStringCheck) {
    HashTable ht(10);
    ht.insert(1, "A");
    ht.insert(2, "B");
    EXPECT_FALSE(ht.ToString().empty());
}
TEST(HashTableTest, EdgeCasesAndErrors) {
    HashTable ht(5);
    EXPECT_EQ(ht.search(999), "");          
    ht.print();              
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}