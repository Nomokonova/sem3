#include "StructureCodec.h"
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

namespace {
    vector<string> header(const string& type, int capacity = 0) {
        return {"LR3S1", type, to_string(capacity)};
    }

    void check(const vector<string>& data, const string& type) {
        if (data.size() < 3 || data[0] != "LR3S1" || data[1] != type) {
            throw runtime_error("Invalid structure type or file version");
        }
        if (type != "hash" && data[2] != "0") {
            throw runtime_error("Invalid metadata");
        }
    }

    int checkedCapacity(const vector<string>& data) {
        const string& s = data[2];
        size_t end = 0;
        int cap = 0;
        try {
            cap = stoi(s, &end);
        } catch (const exception&) {
            throw runtime_error("Invalid hash capacity");
        }
        if (end != s.size() || cap <= 0 || cap > 1000000) {
            throw runtime_error("Invalid hash capacity");
        }
        return cap;
    }
}

vector<string> StructureCodec::pack(const Array& object) {
    auto result = header("array");
    for (int i = 0; i < object.getSize(); ++i) {
        result.push_back(object.getString(i));
    }
    return result;
}
void StructureCodec::unpack(const vector<string>& data, Array& object) {
    check(data, "array");
    if (object.getSize() != 0) throw runtime_error("Destination array must be empty");
    for (size_t i = 3; i < data.size(); ++i) object.pushBack(data[i]);
}

vector<string> StructureCodec::pack(const SinglyLinkedList& object) {
    auto result = header("slist");
    for (SNode* n = object.head; n != nullptr; n = n->next) {
        result.push_back(n->value);
    }
    return result;
}
void StructureCodec::unpack(const vector<string>& data, SinglyLinkedList& object) {
    check(data, "slist");
    if (object.head) throw runtime_error("Destination list must be empty");
    for (size_t i = 3; i < data.size(); ++i) object.pushBack(data[i]);
}

vector<string> StructureCodec::pack(const DoublyLinkedList& object) {
    auto result = header("dlist");
    for (DNode* n = object.head; n != nullptr; n = n->next) {
        result.push_back(n->value);
    }
    return result;
}
void StructureCodec::unpack(const vector<string>& data, DoublyLinkedList& object) {
    check(data, "dlist");
    if (object.head) throw runtime_error("Destination list must be empty");
    for (size_t i = 3; i < data.size(); ++i) object.pushBack(data[i]);
}

vector<string> StructureCodec::pack(const Queue<string>& object) {
    auto result = header("queue");
    for (QNode<string>* n = object.head; n != nullptr; n = n->next) {
        result.push_back(n->value);
    }
    return result;
}
void StructureCodec::unpack(const vector<string>& data, Queue<string>& object) {
    check(data, "queue");
    if (object.head) throw runtime_error("Destination queue must be empty");
    for (size_t i = 3; i < data.size(); ++i) object.push(data[i]);
}

vector<string> StructureCodec::pack(const Stack& object) {
    auto result = header("stack");
    // Сохраняем сверху вниз.
    for (StackNode* n = object.top; n != nullptr; n = n->next) {
        result.push_back(n->value);
    }
    return result;
}
void StructureCodec::unpack(const vector<string>& data, Stack& object) {
    check(data, "stack");
    if (object.top) throw runtime_error("Destination stack must be empty");
    for (size_t i = data.size(); i > 3; --i) object.push(data[i - 1]);
}

vector<string> StructureCodec::pack(const HashTable& object) {
    if (object.capacity <= 0) throw runtime_error("Invalid hash capacity");
    auto result = header("hash", object.capacity);
    for (int i = 0; i < object.capacity; ++i) {
        result.push_back(object.table->getString(i));
    }
    return result;
}
void StructureCodec::unpack(const vector<string>& data, HashTable& object) {
    check(data, "hash");
    int cap = checkedCapacity(data);
    if (object.capacity != cap || data.size() != static_cast<size_t>(cap) + 3) {
        throw runtime_error("Hash capacity does not match destination");
    }
    for (int i = 0; i < cap; ++i) {
        if (!object.table->getString(i).empty()) {
            throw runtime_error("Destination hash must be empty");
        }
    }
    for (size_t i = 3; i < data.size(); ++i) {
        if (data[i].empty()) continue;
        size_t pos = data[i].find(':');
        if (pos == string::npos) throw runtime_error("Invalid hash entry");
        size_t end = 0;
        try {
            stoi(data[i].substr(0, pos), &end);
        } catch (const exception&) {
            throw runtime_error("Invalid hash key");
        }
        if (end != pos) throw runtime_error("Invalid hash key");
    }
    for (int i = 0; i < cap; ++i) object.table->set(i, data[i + 3]);
}

vector<string> StructureCodec::pack(const CompleteBinaryTree& object) {
    auto result = header("tree");
    if (!object.root) return result;
    vector<TNode*> nodes{object.root};
    for (size_t i = 0; i < nodes.size(); ++i) {
        TNode* n = nodes[i];
        result.push_back(n->value);
        if (n->left) nodes.push_back(n->left);
        if (n->right) nodes.push_back(n->right);
    }
    return result;
}
void StructureCodec::unpack(const vector<string>& data, CompleteBinaryTree& object) {
    check(data, "tree");
    if (object.root) throw runtime_error("Destination tree must be empty");
    for (size_t i = 3; i < data.size(); ++i) object.insert(data[i]);
}
