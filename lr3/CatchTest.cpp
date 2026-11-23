#include <catch2/catch_all.hpp>
#include <string>
#include "array.h"
#include "SList.h"
#include "DList.h"
#include "stack.h"
#include "Queue.h"
#include "hash.h"
#include "tree.h"
#include "StructureCodec.h"


//тесты для массива
TEST_CASE("Array operations", "[array]") {
    Array arr;

    SECTION("PushBack increases size and adds elements") {
        arr.pushBack("A");
        arr.pushBack("B");
        REQUIRE(arr.getSize() == 2);
        REQUIRE(arr.getString(0) == "A");
        REQUIRE(arr.getString(1) == "B");
    }

    SECTION("Insert places element at correct index") {
        arr.pushBack("A");
        arr.pushBack("C");
        arr.insert(1, "B"); 
        REQUIRE(arr.getSize() == 3);
        REQUIRE(arr.getString(1) == "B");
    }

    SECTION("Erase removes element and returns it") {
        arr.pushBack("A");
        arr.pushBack("B");
        std::string removed = arr.erase(0);
        REQUIRE(removed == "A");
        REQUIRE(arr.getSize() == 1);
        REQUIRE(arr.getString(0) == "B");
    }

    SECTION("ToString returns correct string") {
        arr.pushBack("A");
        arr.pushBack("B");
        REQUIRE(arr.ToString() == "A B");
    }
    SECTION("EmptyAndErrors") {
        Array arr;
        arr.print();             
        arr.get(10);             
        arr.erase(10);           
        arr.set(10, "X");   
    }
}

//тесты для односвязного списка 
TEST_CASE("SinglyLinkedList operations", "[slist]") {
    SinglyLinkedList list;

    SECTION("PushFront and PushBack") {
        list.pushFront("A");
        list.pushBack("B");
        list.pushBack("C");
        REQUIRE(list.findVal("A") == 0);
        REQUIRE(list.findVal("B") == 1);
        REQUIRE(list.findVal("C") == 2);
    }

    SECTION("Delete element") {
        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        REQUIRE(list.deleteValue("B") == "B"); 
        REQUIRE(list.findVal("B") == -1);      
        REQUIRE(list.findVal("C") == 1);
        REQUIRE(list.popFront() == "A");       
        REQUIRE(list.findVal("A") == -1);
    }

    SECTION("ToStringCheck") {
        list.pushBack("apple");
        list.pushBack("banana");
        REQUIRE(list.ToString() == "apple banana");
    }
    
    SECTION("EdgeCasesAndErrors") {
        list.print();           
        list.printReverse();    
        list.getHead();         
        list.getTail();         
        list.popFront();        
        list.popBack();         
        list.deleteValue("Z");  
        list.deleteBefore("Z"); 
        list.deleteAfter("Z"); 

        list.insertBefore("Z", "A"); 
        list.insertAfter("Z", "A");  
        list.getVal(10); 
    }

    SECTION("AllMethods") {
        list.pushBack("A");
        list.pushBack("C");
        
        list.insertBefore("C", "B"); 
        list.insertAfter("C", "D");  
        REQUIRE(list.findVal("B") == 1);
        REQUIRE(list.findVal("D") == 3);

        REQUIRE(list.deleteBefore("C") == "B"); 
        REQUIRE(list.deleteAfter("C") == "D");  
        list.getVal(0); 
        list.getHead(); 
        list.getTail(); 
        list.print();   
        list.printReverse(); 
        REQUIRE(list.popBack() == "C");
        REQUIRE(list.popFront() == "A");
    }
    SECTION("PopBackEl") {
        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        list.pushBack("D");

        REQUIRE(list.popBack()=="D");
        REQUIRE(list.findVal("D")==-1);

        REQUIRE(list.popBack()=="C");
        REQUIRE(list.findVal("C")==-1);

        REQUIRE(list.popBack()=="B");
        REQUIRE(list.popBack()=="A");

        REQUIRE(list.popBack()=="");
    }
}

//тесты для двусвязного списка 
TEST_CASE("DoublyLinkedList operations", "[dlist]") {
    DoublyLinkedList list;

    SECTION("InsertBefore and InsertAfter") {
        list.pushBack("A");
        list.pushBack("C");
        list.insertBefore("C", "B"); 
        list.insertAfter("C", "D");  
        REQUIRE(list.findVal("B") == 1);
        REQUIRE(list.findVal("D") == 3);
    }

    SECTION("PopFront and PopBack") {
        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        REQUIRE(list.popFront() == "A");
        REQUIRE(list.popBack() == "C");
        REQUIRE(list.findVal("B") == 0); 
    }

    SECTION("ToStringCheck") {
        list.pushBack("A");
        list.pushBack("B");
        REQUIRE(list.ToString() == "A B");
    }

    SECTION("AllMethods") {
        list.pushFront("B");
        list.pushBack("C");
        list.insertBefore("B", "A"); 
        list.insertAfter("C", "D");

        REQUIRE(list.findVal("C") == 2);
        list.findInd(1); 

        REQUIRE(list.deleteBefore("B") == "A"); 
        REQUIRE(list.deleteAfter("C") == "D");  
        REQUIRE(list.deleteValue("B") == "B");  

        list.getHead();
        list.getTail();
        list.print();
        list.printReverse();
        list.popFront(); 
    }

    SECTION("CoverageBoost") {
        DoublyLinkedList list2;
        list2.pushBack("A");
        list2.pushBack("B");

        list2.insertBefore("Z", "C");
        list2.insertAfter("Z", "C");

        list2.insertAfter("A", "X"); 
        REQUIRE(list2.findVal("X") == 1); 

        list2.pushFront("Start");
        REQUIRE(list2.findVal("Start") == 0); 
    }
    
    SECTION("CoverageBoostDelete") {
        DoublyLinkedList list;
        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        list.pushBack("D");

        REQUIRE(list.deleteBefore("D") == "C");
        REQUIRE(list.deleteAfter("B") == "D");
        
        list.deleteBefore("Z");
        list.deleteAfter("Z");
    }
}

//тесты для стека 
TEST_CASE("Stack operations", "[stack]") {
    Stack st;

    SECTION("Push, Pop and Peek") {
        st.push("A");
        st.push("B");
        REQUIRE(st.peek() == "B");
        REQUIRE(st.StackSize() == 2);
        REQUIRE(st.pop() == "B");
        REQUIRE(st.peek() == "A");
        REQUIRE(st.StackSize() == 1);

        st.print();
    }

    SECTION("EmptyPop") {
        REQUIRE(st.pop() == "");
        REQUIRE(st.StackSize() == 0);
        st.print();
    }

    SECTION("ToStringCheck") {
        st.push("A");
        st.push("B");
        REQUIRE(st.ToString() == "A B");
    }
}

//тесты для очереди
TEST_CASE("Queue operations", "[queue]") {
    Queue<std::string> q;

    SECTION("Push and Pop") {
        q.push("first");
        q.push("second");
        REQUIRE(q.Qsize() == 2);
        REQUIRE(q.peek() == "first");
        REQUIRE(q.pop() == "first");
        REQUIRE(q.Qsize() == 1);
        REQUIRE(q.back() == "second");
    }

    SECTION("ToStringCheck") {
        q.push("A");
        q.push("B");
        REQUIRE(q.ToString() == "A B");
    }

    SECTION("EmptyAndErrors") {
        q.pop();                 
        q.peek();                
        q.back();                
        q.print(); 
    }
    SECTION("PrintNonEmpty") {
        q.push("A");
        q.push("B");
        q.push("C");

        q.print();

        REQUIRE(q.Qsize()==3);
        REQUIRE(q.peek()=="A");
        REQUIRE(q.back()=="C");
    }
    
}

//тесты для дерева
TEST_CASE("CompleteBinaryTree operations", "[tree]") {
    CompleteBinaryTree tree;

    SECTION("Insert and Search") {
        tree.insert("A");
        tree.insert("B");
        tree.insert("C");
        REQUIRE(tree.search("B"));
        REQUIRE(tree.getsize() == 3);
    }

    SECTION("Print") {
        tree.insert("A");
        tree.insert("B");
        tree.insert("C");
        tree.print();
    }

    SECTION("IsComplete") {
        tree.insert("1");
        tree.insert("2");
        tree.insert("3"); 
        REQUIRE(tree.isComplete());
    }

    SECTION("ToStringCheck") {
        tree.insert("A");
        tree.insert("B");
        tree.insert("C");
        REQUIRE(tree.ToString() == "A B C");
    }

    SECTION("EmptyAndErrors") {
        tree.print();            
        tree.search("Z");        
        tree.isComplete();  
    }
}
TEST_CASE("Tree empty tostring", "[tree]") {
    CompleteBinaryTree tree;

    REQUIRE(tree.ToString() == "");
    REQUIRE(tree.isComplete());
    REQUIRE_FALSE(tree.search("X"));

    tree.print();
}

//тесты для хэш-таблицы
TEST_CASE("HashTable operations", "[hash]") {
    HashTable ht(10);

    SECTION("Insert and Search") {
        ht.insert(5, "five");
        ht.insert(15, "fifteen");
        REQUIRE(ht.search(5) == "five");
        REQUIRE(ht.search(15) == "fifteen");
        REQUIRE(ht.search(99) == ""); 
    }

    SECTION("UpdateValue") {
        ht.insert(5, "five");
        ht.insert(5, "FIVE_NEW"); 
        REQUIRE(ht.search(5) == "FIVE_NEW");
    }

    SECTION("ToStringCheck") {
        ht.insert(1, "A");
        ht.insert(2, "B");
        REQUIRE(ht.ToString() == "1:A 2:B");
    }

    SECTION("EmptyAndErrors") {        
        ht.search(999);          
        ht.print();
    }
}
// ---------- ХЕШ-ТАБЛИЦА ----------

TEST_CASE("HashTable remove", "[hash]") {
    SECTION("Remove with collisions") {
        HashTable ht(5);

        ht.insert(1, "A");
        ht.insert(6, "B");
        ht.insert(11, "C");

        REQUIRE(ht.remove(1));
        REQUIRE(ht.search(1) == "");

        REQUIRE(ht.search(6) == "B");
        REQUIRE(ht.search(11) == "C");

        REQUIRE(ht.remove(6));
        REQUIRE(ht.search(11) == "C");

        REQUIRE_FALSE(ht.remove(99));
        REQUIRE_FALSE(ht.remove(1));

        REQUIRE(ht.remove(11));
        REQUIRE(ht.ToString() == "");

        REQUIRE(ht.insert(16, "D") >= 0);
        REQUIRE(ht.search(16) == "D");
    }

    SECTION("Remove from full table") {
        HashTable ht(5);

        ht.insert(4, "A");
        ht.insert(9, "B");
        ht.insert(14, "C");
        ht.insert(19, "D");
        ht.insert(24, "E");

        REQUIRE(ht.remove(4));

        REQUIRE(ht.search(9) == "B");
        REQUIRE(ht.search(14) == "C");
        REQUIRE(ht.search(19) == "D");
        REQUIRE(ht.search(24) == "E");

        REQUIRE(ht.insert(29, "hello:world") >= 0);
        REQUIRE(ht.search(29) == "hello:world");
        REQUIRE(ht.remove(29));
    }
}

TEST_CASE("HashTable full table scenarios", "[hash]") {
    SECTION("Full table insert search remove print") {
        HashTable ht(3);

        REQUIRE(ht.insert(0, "A") >= 0);
        REQUIRE(ht.insert(3, "B") >= 0);
        REQUIRE(ht.insert(6, "C") >= 0);

        REQUIRE(ht.insert(9, "D") == -1);

        REQUIRE(ht.search(0) == "A");
        REQUIRE(ht.search(3) == "B");
        REQUIRE(ht.search(6) == "C");

        REQUIRE(ht.search(99) == "");

        ht.print();

        REQUIRE_FALSE(ht.remove(99));
    }

    SECTION("Remove with rehashing") {
        HashTable ht(5);

        ht.insert(1, "A");
        ht.insert(6, "B");
        ht.insert(11, "C");

        REQUIRE(ht.remove(1));
        REQUIRE(ht.search(1) == "");
        REQUIRE(ht.search(6) == "B");
        REQUIRE(ht.search(11) == "C");

        REQUIRE(ht.remove(6));
        REQUIRE(ht.search(11) == "C");

        REQUIRE(ht.remove(11));
        REQUIRE(ht.search(11) == "");
    }
}


// ---------- ОДНОСВЯЗНЫЙ СПИСОК ----------

TEST_CASE("SinglyLinkedList extra coverage", "[slist]") {
    SECTION("Delete by value") {
        SinglyLinkedList empty;
        REQUIRE(empty.deleteValue("X") == "");

        SinglyLinkedList list;

        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        list.pushBack("D");

        REQUIRE(list.deleteValue("A") == "A");
        REQUIRE(list.ToString() == "B C D");

        REQUIRE(list.deleteValue("D") == "D");
        REQUIRE(list.ToString() == "B C");

        REQUIRE(list.deleteValue("Z") == "");

        REQUIRE(list.deleteValue("B") == "B");
        REQUIRE(list.deleteValue("C") == "C");

        REQUIRE(list.ToString() == "");
    }

    SECTION("Delete before and after") {
        SinglyLinkedList list;

        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        list.pushBack("D");

        REQUIRE(list.deleteBefore("A") == "");
        REQUIRE(list.deleteBefore("B") == "A");
        REQUIRE(list.deleteBefore("D") == "C");

        REQUIRE(list.ToString() == "B D");

        REQUIRE(list.deleteAfter("B") == "D");
        REQUIRE(list.deleteAfter("B") == "");

        list.insertBefore("B", "A");
        list.insertAfter("B", "C");

        REQUIRE(list.ToString() == "A B C");

        list.getVal(2);
        list.getVal(10);
        list.printReverse();
    }

    SECTION("Pop back all cases") {
        SinglyLinkedList list;

        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        list.pushBack("D");

        REQUIRE(list.popBack() == "D");
        REQUIRE(list.popBack() == "C");
        REQUIRE(list.popBack() == "B");
        REQUIRE(list.popBack() == "A");
        REQUIRE(list.popBack() == "");
    }
}


// ---------- ДВУСВЯЗНЫЙ СПИСОК ----------

TEST_CASE("DoublyLinkedList extra coverage", "[dlist]") {
    SECTION("Delete by value") {
        DoublyLinkedList list;

        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        list.pushBack("D");

        REQUIRE(list.deleteValue("B") == "B");
        REQUIRE(list.deleteValue("A") == "A");
        REQUIRE(list.deleteValue("D") == "D");

        REQUIRE(list.ToString() == "C");

        REQUIRE(list.deleteValue("Z") == "");

        REQUIRE(list.deleteValue("C") == "C");
        REQUIRE(list.ToString() == "");

        REQUIRE(list.popBack() == "");
    }

    SECTION("Delete before and after") {
        DoublyLinkedList list;

        list.pushBack("A");
        list.pushBack("B");
        list.pushBack("C");
        list.pushBack("D");

        REQUIRE(list.deleteBefore("A") == "");
        REQUIRE(list.deleteBefore("C") == "B");
        REQUIRE(list.deleteAfter("C") == "D");

        REQUIRE(list.ToString() == "A C");

        list.insertBefore("A", "Z");
        list.insertAfter("C", "E");

        REQUIRE(list.ToString() == "Z A C E");

        REQUIRE(list.popBack() == "E");
        REQUIRE(list.popFront() == "Z");

        list.findInd(1);
        list.getTail();
        list.printReverse();
    }

    SECTION("Pop back single element") {
        DoublyLinkedList list;

        list.pushBack("Only");

        REQUIRE(list.popBack() == "Only");
        REQUIRE(list.popBack() == "");

        REQUIRE(list.ToString() == "");
    }
}