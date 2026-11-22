
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include "StructureCodec.h"

using namespace std;

//общая проверка сериализации и десериализации
template <typename T>
void testSerialization(const T& original, const string& name) {
    filesystem::create_directories("serialization_output");

    string binaryFile = "serialization_output/" + name + ".bin";
    string textFile = "serialization_output/" + name + ".txt";

    //бинарная сериализация
    StructureCodec::saveBinary(original, binaryFile);

    //текстовая сериализация
    StructureCodec::saveText(original, textFile);

    //пустые структуры для восстановления
    T restoredBinary;
    T restoredText;

    //бинарная десериализация
    StructureCodec::loadBinary(restoredBinary, binaryFile);

    //текстовая десериализация
    StructureCodec::loadText(restoredText, textFile);

    REQUIRE(
        StructureCodec::pack(original) ==
        StructureCodec::pack(restoredBinary)
    );

    REQUIRE(
        StructureCodec::pack(original) ==
        StructureCodec::pack(restoredText)
    );
}

//----------массив
TEST_CASE("Array serialization", "[serialization]") {
    Array array;

    array.pushBack("apple");
    array.pushBack("hello world");
    array.pushBack("");
    array.pushBack("Привет");
    array.pushBack("a:b");
    array.pushBack("line1\nline2");
    array.pushBack("\"quoted\"");

    testSerialization(array, "array");
}

//----------односвязный список
TEST_CASE("SinglyLinkedList serialization", "[serialization]") {
    SinglyLinkedList list;

    list.pushBack("one");
    list.pushBack("two");
    list.pushBack("three");

    testSerialization(list, "slist");
}

//----------двусвязный список
TEST_CASE("DoublyLinkedList serialization", "[serialization]") {
    DoublyLinkedList list;

    list.pushBack("one");
    list.pushBack("two");
    list.pushBack("three");

    testSerialization(list, "dlist");
}

//----------очередь
TEST_CASE("Queue serialization", "[serialization]") {
    Queue<string> queue;

    queue.push("first");
    queue.push("second");
    queue.push("third");

    testSerialization(queue, "queue");
}

//----------стек
TEST_CASE("Stack serialization", "[serialization]") {
    Stack stack;

    stack.push("bottom");
    stack.push("middle");
    stack.push("top");

    testSerialization(stack, "stack");
}

//----------дерево
TEST_CASE("CompleteBinaryTree serialization", "[serialization]") {
    CompleteBinaryTree tree;

    tree.insert("1");
    tree.insert("2");
    tree.insert("3");
    tree.insert("4");
    tree.insert("5");

    REQUIRE(tree.isComplete());

    testSerialization(tree, "tree");
}

//----------хеш-таблица
TEST_CASE("HashTable serialization", "[serialization]") {
    filesystem::create_directories("serialization_output");

    HashTable original(10);

    original.insert(1, "apple");
    original.insert(11, "banana");
    original.insert(21, "hello:world");

    //сохранение
    StructureCodec::saveBinary(
        original, "serialization_output/hash.bin"
    );

    StructureCodec::saveText(
        original, "serialization_output/hash.txt"
    );

    //восстановление
    HashTable restoredBinary(10);
    HashTable restoredText(10);

    StructureCodec::loadBinary(
        restoredBinary, "serialization_output/hash.bin"
    );

    StructureCodec::loadText(
        restoredText, "serialization_output/hash.txt"
    );

    //проверка полного содержимого таблицы
    REQUIRE(
        StructureCodec::pack(original) ==
        StructureCodec::pack(restoredBinary)
    );

    REQUIRE(
        StructureCodec::pack(original) ==
        StructureCodec::pack(restoredText)
    );

    //дополнительно проверка поиска
    REQUIRE(restoredBinary.search(11) == "banana");
    REQUIRE(restoredText.search(21) == "hello:world");
}

//----------пустые структуры
TEST_CASE("Empty structures serialization", "[serialization]") {
    SECTION("Empty array") {
        Array array;
        testSerialization(array, "empty_array");
    }

    SECTION("Empty stack") {
        Stack stack;
        testSerialization(stack, "empty_stack");
    }

    SECTION("Empty tree") {
        CompleteBinaryTree tree;
        testSerialization(tree, "empty_tree");
    }
}

//----------ошибки десериализации 
TEST_CASE("Serialization errors", "[serialization]") {
    filesystem::create_directories("serialization_output");

    SECTION("Wrong structure type") {
        Array array;
        array.pushBack("test");

        StructureCodec::saveText(
            array, "serialization_output/wrong_type.txt"
        );

        Stack stack;

        //нельзя загружать массив в стек
        REQUIRE_THROWS_AS(
            StructureCodec::loadText(
                stack, "serialization_output/wrong_type.txt"
            ),
            runtime_error
        );
    }

    SECTION("Wrong hash capacity") {
        HashTable original(10);
        original.insert(1, "test");

        StructureCodec::saveBinary(
            original, "serialization_output/wrong_hash.bin"
        );

        HashTable restored(5);

        REQUIRE_THROWS_AS(
            StructureCodec::loadBinary(
                restored, "serialization_output/wrong_hash.bin"
            ),
            runtime_error
        );
    }

    SECTION("Non-empty destination") {
        Array original;
        original.pushBack("saved");

        StructureCodec::saveBinary(
            original, "serialization_output/nonempty.bin"
        );

        Array restored;
        restored.pushBack("existing");

        REQUIRE_THROWS_AS(
            StructureCodec::loadBinary(
                restored, "serialization_output/nonempty.bin"
            ),
            runtime_error
        );

        REQUIRE(restored.getString(0) == "existing");
    }

    SECTION("Missing file") {
        string filename =
            "serialization_output/missing_file_82917.bin";

        filesystem::remove(filename);

        REQUIRE_THROWS_AS(
            Serializer::loadBinary(filename),
            runtime_error
        );
    }

    SECTION("Corrupted binary file") {
        string filename = "serialization_output/corrupted.bin";

        {
            ofstream file(filename, ios::binary);
            file << "bad";
        }

        REQUIRE_THROWS_AS(
            Serializer::loadBinary(filename),
            runtime_error
        );
    }
}
