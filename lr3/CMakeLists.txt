
cmake_minimum_required(VERSION 3.16)

project(LR3Serialization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Структуры данных и сериализация
add_library(lr3_structures
    array.cpp
    SList.cpp
    DList.cpp
    Queue.cpp
    stack.cpp
    hash.cpp
    tree.cpp
    Serializer.cpp
    StructureCodec.cpp
)

target_include_directories(lr3_structures PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Обычные тесты сериализации
add_executable(serialization_tests
    SerializationTests.cpp
)

target_link_libraries(serialization_tests PRIVATE
    lr3_structures
)

# Тесты сериализации на Catch2
find_package(Catch2 3 REQUIRED)

add_executable(serialization_catch_tests
    SerializationCatchTests.cpp
)

target_link_libraries(serialization_catch_tests PRIVATE
    lr3_structures
    Catch2::Catch2WithMain
)
# Регистрация тестов
enable_testing()

add_test(
    NAME serialization
    COMMAND serialization_tests
)

add_test(
    NAME serialization_catch
    COMMAND serialization_catch_tests
)

# Линтер clang-tidy
find_program(CLANG_TIDY_PROGRAM NAMES clang-tidy)

if(CLANG_TIDY_PROGRAM)
    add_custom_target(lint
        COMMAND ${CLANG_TIDY_PROGRAM}
            -p ${CMAKE_BINARY_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/Serializer.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/StructureCodec.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/SerializationTests.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/SerializationCatchTests.cpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )
endif()
