#pragma once
#include <string>
#include <vector>

class Serializer{
public:
    //бинарный формат 
    static void saveBinary(const std::vector<std::string>& data, const std::string& filename);
    static std::vector<std::string> loadBinary(const std::string& filename);
    //текстовый формат
    static void saveText(const std::vector<std::string>& data, const std::string& filename);
    static std::vector<std::string> loadText(const std::string& filename);
};