#include "StructureCodec.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void require(bool ok, const string& message) {
    if (!ok) throw runtime_error("Test failed: " + message);
}

template<class T>
void roundTrip(const T& original, const string& name) {
    const string prefix = "serialization_output/" + name;
    StructureCodec::saveBinary(original, prefix + ".bin");
    StructureCodec::saveText(original, prefix + ".txt");

    T fromBinary;
    T fromText;
    StructureCodec::loadBinary(fromBinary, prefix + ".bin");
    StructureCodec::loadText(fromText, prefix + ".txt");
    require(StructureCodec::pack(original) == StructureCodec::pack(fromBinary), name + " binary");
    require(StructureCodec::pack(original) == StructureCodec::pack(fromText), name + " text");
    cout << name << ": binary OK, text OK\n";
}

void testHash() {
    HashTable original(10);
    original.insert(1, "a:b");
    original.insert(11, "hello world");
    original.insert(21, "Привет");
    StructureCodec::saveBinary(original, "serialization_output/hash.bin");
    StructureCodec::saveText(original, "serialization_output/hash.txt");

    HashTable fromBinary(10), fromText(10);
    StructureCodec::loadBinary(fromBinary, "serialization_output/hash.bin");
    StructureCodec::loadText(fromText, "serialization_output/hash.txt");
    require(StructureCodec::pack(original) == StructureCodec::pack(fromBinary), "hash binary slots");
    require(StructureCodec::pack(original) == StructureCodec::pack(fromText), "hash text slots");
    require(fromBinary.search(11) == "hello world", "hash search binary");
    require(fromText.search(1) == "a:b", "hash search text");
    cout << "hash: binary OK, text OK\n";

    HashTable wrongCapacity(11);
    bool rejected = false;
    try { StructureCodec::loadBinary(wrongCapacity, "serialization_output/hash.bin"); }
    catch (const runtime_error&) { rejected = true; }
    require(rejected, "hash wrong capacity rejected");
}

int main() {
    try {
        filesystem::create_directories("serialization_output");
        Array array;
        for (const auto& s : {string(""), string("hello world"), string("a:b"), string("Привет"), string("line1\nline2"), string("\"quoted\"")}) array.pushBack(s);
        roundTrip(array, "array");

        SinglyLinkedList slist;
        for (const char* s : {"one", "two words", "three"}) slist.pushBack(s);
        roundTrip(slist, "slist");

        DoublyLinkedList dlist;
        for (const char* s : {"one", "two words", "three"}) dlist.pushBack(s);
        roundTrip(dlist, "dlist");

        Queue<string> queue;
        queue.push("one"); queue.push("two words"); queue.push("three");
        roundTrip(queue, "queue");

        Stack stack;
        stack.push("bottom"); stack.push("middle"); stack.push("TOP");
        roundTrip(stack, "stack");

        CompleteBinaryTree tree;
        for (const char* s : {"1", "2", "3", "4", "5", "6", "7", "8"}) tree.insert(s);
        require(tree.isComplete(), "original tree is complete");
        roundTrip(tree, "tree");
        testHash();

        Array emptyArray;
        roundTrip(emptyArray, "array_empty");
        Stack emptyStack;
        roundTrip(emptyStack, "stack_empty");
        CompleteBinaryTree emptyTree;
        roundTrip(emptyTree, "tree_empty");

        //нельзя загрузить файл массива в объект стека
        Stack incompatible;
        bool rejected = false;
        try { StructureCodec::loadText(incompatible, "serialization_output/array.txt"); }
        catch (const runtime_error&) { rejected = true; }
        require(rejected, "type mismatch rejected");

        //нельзя загрузить в уже заполненный объект
        Array nonEmpty;
        nonEmpty.pushBack("existing");
        rejected = false;
        try { StructureCodec::loadBinary(nonEmpty, "serialization_output/array.bin"); }
        catch (const runtime_error&) { rejected = true; }
        require(rejected && nonEmpty.getString(0) == "existing", "non-empty destination rejected");

        cout << "ALL TESTS PASSED\n";
        return 0;
    } catch (const exception& e) {
        cerr << e.what() << '\n';
        return 1;
    }
}
