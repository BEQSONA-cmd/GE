#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Hash_Map.hpp"

// functions
const std::string FUNC_PRINT = "print";
const std::string FUNC_INPUT = "input";
const std::string FUNC_IF = "if";
const std::string FUNC_FUNCTION = "function";

// data types
const std::string STRING = "string";
const std::string INT = "int";
const std::string FUNC = "function";

// parser will parse the code and create a hash map
class Parser
{
    private:
        std::vector<std::string> lines;
        Hash_Map *instructions;
        Hash_Map *variables;
    public:
        Parser(std::vector<std::string> lines);
        bool parse();

        bool check_instruction(std::string line);
        void print_instructions();
        Hash_Map *get_instructions();

        bool check_variable(std::string line);
        void print_variables();

        ~Parser();
};

std::string get_next_string(std::string line, std::string string);
std::string get_first_string(std::string line);
std::string get_value_string(std::string line);
bool is_str_in_str(std::string line, std::string string);
std::vector<std::string> get_all_string_space(std::string line);
std::vector<std::string> get_all_string_func(std::string line);
size_t string_count(std::string line);
bool ft_strcmp(std::string str1, std::string str2);
bool is_char(char c);

#endif