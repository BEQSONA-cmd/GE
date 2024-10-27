#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <iostream>
#include <string>

// enum types will be func, string and int

enum Type
{
    T_INT, // integer is 0
    T_STRING, // string is 1
    T_FUNC // function is 2
};

// key must be FUNC_PRINT or FUNC_INPUT
// value must be the string that will be printed or the variable that will be inputted
struct Hash_Map_Enter
{
    std::string key;
    std::string value;

    Type type;

    Hash_Map_Enter *next;
};

class Hash_Map
{
    public:
        Hash_Map_Enter *head;

        Hash_Map();
        void insert(std::string key, std::string value, Type type);
        std::string get(std::string key);
};

#endif