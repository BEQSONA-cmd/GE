#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Hash_Map.hpp"

// functions
const std::string FUNC_PRINT = "ბეჭდვა";
const std::string FUNC_INPUT = "შეყვანა";
const std::string FUNC_IF = "თუ";
const std::string FUNC_FUNCTION = "ფუნქცია";

// data types
const std::string STRING = "ფრაზა";
const std::string INT = "რიცხვი";
const std::string FUNC = "ფუნქცია";

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

std::string get_next_string(std::string line, std::string string);
std::string get_value_string(std::string line);

#endif