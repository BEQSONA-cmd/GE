#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// functions
const std::string FUNC_PRINT = "ბეჭდვა";
const std::string FUNC_INPUT = "შეყვანა";
const std::string FUNC_IF = "თუ";
const std::string FUNC_FUNCTION = "ფუნქცია";

// data types
const std::string STRING = "ფრაზა";
const std::string INT = "რიცხვი";
const std::string FUNC = "ფუნქცია";

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

// parser will parse the code and create a hash map
class Parser
{
    private:
        std::vector<std::string> lines;
        Hash_Map *instructions;
        Hash_Map *variables;
    public:
        Parser(std::vector<std::string> lines);
        void parse();

        void check_instruction(std::string line);
        void print_instructions();
        Hash_Map *get_instructions();

        void check_variable(std::string line);
        void print_variables();

        ~Parser();
};

#endif