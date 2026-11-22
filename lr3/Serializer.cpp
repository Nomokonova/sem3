#include "Serializer.h"

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

namespace {
    constexpr uint32_t MAX_ITEMS = 1000000;
    constexpr uint32_t MAX_STRING = 1000000;

    // Запись и чтение uint32 в Little Endian
    void writeU32(ostream& file, uint32_t value) {
        for (int i = 0; i < 4; ++i) {
            file.put(static_cast<char>((value >> (8 * i)) & 255));
        }
    }

    uint32_t readU32(istream& file) {
        uint32_t value = 0;
        for (int i = 0; i < 4; ++i) {
            int byte = file.get();
            if (byte == EOF) throw runtime_error("Invalid binary file");
            value |= static_cast<uint32_t>(byte) << (8 * i);
        }
        return value;
    }

    void checkCount(size_t count) {
        if (count > MAX_ITEMS) throw runtime_error("Too many elements");
    }

    void checkLength(size_t length) {
        if (length > MAX_STRING) throw runtime_error("String too long");
    }

    void checkEnd(istream& file) {
        if (file.peek() != EOF) throw runtime_error("Extra data in file");
    }
} 

void Serializer::saveBinary(const vector<string>& data, const string& filename) {
    checkCount(data.size());
    ofstream file(filename, ios::binary);
    if (!file) throw runtime_error("Cannot open file");

    writeU32(file, static_cast<uint32_t>(data.size()));
    for (const string& value : data) {
        checkLength(value.size());
        writeU32(file, static_cast<uint32_t>(value.size()));
        file.write(value.data(), static_cast<streamsize>(value.size()));
    }
    if (!file) throw runtime_error("Write error");
}

vector<string> Serializer::loadBinary(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) throw runtime_error("Cannot open file");

    uint32_t count = readU32(file);
    checkCount(count);
    vector<string> result;
    result.reserve(count);

    for (uint32_t i = 0; i < count; ++i) {
        uint32_t length = readU32(file);
        checkLength(length);
        string value(length, '\0');
        if (!file.read(value.data(), length)) throw runtime_error("Invalid binary string");
        result.push_back(value);
    }
    checkEnd(file);
    return result;
}

void Serializer::saveText(const vector<string>& data, const string& filename) {
    checkCount(data.size());
    ofstream file(filename, ios::binary);
    if (!file) throw runtime_error("Cannot open file");

    file << data.size() << '\n';
    for (const string& value : data) {
        checkLength(value.size());
        file << quoted(value) << '\n';
    }
    if (!file) throw runtime_error("Write error");
}

vector<string> Serializer::loadText(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) throw runtime_error("Cannot open file");

    size_t count = 0;
    if (!(file >> count)) throw runtime_error("Invalid text file");
    checkCount(count);

    vector<string> result;
    result.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        string value;
        if (!(file >> quoted(value))) throw runtime_error("Invalid quoted string");
        checkLength(value.size());
        result.push_back(value);
    }
    //после последней строки допускаются только пробельные символы.
    file >> ws;
    checkEnd(file);
    return result;
}
