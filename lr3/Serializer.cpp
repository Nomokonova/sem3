#include "Serializer.h"

#include <fstream>
#include <iomanip>
#include <cstdint>
#include <stdexcept>
using namespace std;
//бинарный формат 
void Serializer::saveBinary(const vector<string>& data, const string& filename){
    ofstream file(filename,ios::binary);

    if(!file){
        throw runtime_error("Cannot open file");
    }

    uint32_t count = data.size();

    file.write((char*)&count, sizeof(count));
    
    for(const string& value : data){
        uint32_t length = value.size();

        file.write((char*)&length, sizeof(length)); //длина строки
        file.write(value.data(), length); //сама строка
    }
    if(!file){
        throw runtime_error("Write error");
    }
}
vector<string> Serializer::loadBinary(const string& filename){
    ifstream file(filename, ios::binary);

    if(!file){
        throw runtime_error("Cannot open file");
    }

    uint32_t count = 0;

    if(!file.read((char*)&count, sizeof(count))){
        throw runtime_error("Invalid file");
    }

    if(count > 1000000){
        throw runtime_error("Too many elements");
    }

    vector<string> data;

    for(uint32_t i = 0; i < count; i++){
        uint32_t lenght = 0;

        if(!file.read((char*)&lenght, sizeof(lenght))){
            throw runtime_error("Invalid file");
        }

        if(lenght > 1000000){
            throw runtime_error("String too long");
        }

        string value(lenght, '\0');

        if(!file.read(value.data(),lenght)){
            throw runtime_error("Invalid file");
        }

        data.push_back(value);
    }
    return data;
}

//текстовый формат
void Serializer::saveText(const vector<string>& data, const string& filename) {
    ofstream file(filename);

    if (!file) {
        throw runtime_error("Cannot open file");
    }

    file << data.size() << '\n';

    for (const string& value : data) {
        file << quoted(value) << '\n';
    }

    if (!file) {
        throw runtime_error("Write error");
    }
}
vector<string> Serializer::loadText(
    const string& filename
) {
    ifstream file(filename);

    if (!file) {
        throw runtime_error("Cannot open file");
    }

    size_t count = 0;

    if (!(file >> count)) {
        throw runtime_error("Invalid file");
    }

    if (count > 1000000) {
        throw runtime_error("Too many elements");
    }

    vector<string> data;

    for (size_t i = 0; i < count; i++) {
        string value;

        if (!(file >> quoted(value))) {
            throw runtime_error("Invalid file");
        }

        data.push_back(value);
    }

    return data;
}