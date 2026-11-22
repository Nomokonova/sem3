#pragma once

#include "Serializer.h"
#include "array.h"
#include "SList.h"
#include "DList.h"
#include "Queue.h"
#include "stack.h"
#include "hash.h"
#include "tree.h"
#include <string>
#include <vector>

class StructureCodec {
public:
    template <typename T>
    static void saveBinary(const T& object, const std::string& filename) {
        Serializer::saveBinary(pack(object), filename);
    }

    template <typename T>
    static void loadBinary(T& emptyObject, const std::string& filename) {
        unpack(Serializer::loadBinary(filename), emptyObject);
    }

    template <typename T>
    static void saveText(const T& object, const std::string& filename) {
        Serializer::saveText(pack(object), filename);
    }

    template <typename T>
    static void loadText(T& emptyObject, const std::string& filename) {
        unpack(Serializer::loadText(filename), emptyObject);
    }

    static std::vector<std::string> pack(const Array& object);
    static std::vector<std::string> pack(const SinglyLinkedList& object);
    static std::vector<std::string> pack(const DoublyLinkedList& object);
    static std::vector<std::string> pack(const Queue<std::string>& object);
    static std::vector<std::string> pack(const Stack& object);
    static std::vector<std::string> pack(const HashTable& object);
    static std::vector<std::string> pack(const CompleteBinaryTree& object);

    static void unpack(const std::vector<std::string>& data, Array& object);
    static void unpack(const std::vector<std::string>& data, SinglyLinkedList& object);
    static void unpack(const std::vector<std::string>& data, DoublyLinkedList& object);
    static void unpack(const std::vector<std::string>& data, Queue<std::string>& object);
    static void unpack(const std::vector<std::string>& data, Stack& object);
    static void unpack(const std::vector<std::string>& data, HashTable& object);
    static void unpack(const std::vector<std::string>& data, CompleteBinaryTree& object);
};
