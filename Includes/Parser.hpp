#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Hash_Map.hpp"
#include "Utils.hpp"

// functions
const std::string FUNC_PRINT = "print";
const std::string FUNC_INPUT = "input";
const std::string FUNC_CALL = "call";


const std::string FUNC_IF = "if";
const std::string FUNC_WHILE = "while";
const std::string FUNC_FUNCTION = "function";

// data types
const std::string STRING = "string";
const std::string INT = "int";
const std::string FUNC = "function";

// operators
const std::string ASSIGN = "=";
const std::string ADD = "+";
const std::string SUB = "-";
const std::string MUL = "*";
const std::string DIV = "/";

// compare
const std::string EQUAL = "==";
const std::string NOT_EQUAL = "!=";
const std::string GREATER = ">";
const std::string LESS = "<";
const std::string GREATER_EQUAL = ">=";
const std::string LESS_EQUAL = "<=";

class Object;

// parser will parse the code and create a hash map
class Parser
{
    protected:
        std::map<std::string, Object> functions;
        std::vector<std::string> lines;
        Hash_Map *instructions;
        Hash_Map *variables;
    public:
        Parser(std::vector<std::string> lines);
        void parse(std::map<std::string, Object> funcs);
        void parse_variables(std::vector<std::string> words, std::string line);

        void check_instruction(std::string line, std::map<std::string, Object> funcs);
        void print_instructions();
        Hash_Map *get_instructions();

        void create_variable(std::string line);
        void assign_string(std::string line);
        void append_string(std::string line);

        void assign_int(std::string line);
        void add_int(std::string line);
        void sub_int(std::string line);

        void print_variables();
};

class Object : public Parser
{
    public:
        Object() : Parser(std::vector<std::string>()) {}
        Object(std::vector<std::string> lines, size_t *iter, std::map<std::string, Object> functions);
};


std::string get_previous_string(std::string line, std::string string);
std::string get_value_string(std::string line, Hash_Map *variables);
std::string get_value_int(std::string line, Hash_Map *variables);
std::string get_next_string(std::string line, std::string string);
std::vector<std::string> get_all_string_space(std::string line);
std::vector<std::string> get_all_string_func(std::string line);
std::string get_first_string(std::string line);


bool is_str_in_str(std::string line, std::string string);
bool ft_strcmp(std::string str1, std::string str2);
size_t string_count(std::string line);
bool is_func_call(std::string line);
bool is_two_qoute(std::string line);
size_t ft_atoi(std::string str);
bool is_char(char c);
bool is_digit(char c);

#endif