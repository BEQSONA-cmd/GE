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


const std::string IF = "if";
const std::string ELSE = "else";
const std::string WHILE = "while";

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

class Scope
{
    private:
        size_t end;
    public:
        Scope(std::vector<std::string> lines, size_t *iter);
        bool is_end_of_scope(size_t i);
};

// parser will parse the code and create a hash map
class Object
{
    protected:
        std::vector<std::string> lines;
        Hash_Map *instructions;
        Hash_Map *variables;
    public:
        Object() {};
        Object(std::vector<std::string> lines, size_t *iter, bool main = false);

        void parse();
        void parse_variables(std::vector<std::string> words, std::string line);

        std::string value_check(std::string line ,size_t i);

        void if_statement(std::string line, size_t *i);
        void else_statement(std::string line, size_t *i);
        void while_statement(std::string line, size_t *i);
        bool check_condition(std::string line);

        void check_instruction(std::string line);
        void print_instructions();
        Hash_Map *get_instructions();
        Hash_Map *get_variables();

        void create_variable(std::string line);
        void assign_string(std::string line);
        void append_string(std::string line);

        void assign_int(std::string line);
        void add_int(std::string line);
        void sub_int(std::string line);

        void print_variables();
};

std::string get_previous_string(std::string line, std::string string);
std::string get_value_string(std::string line, Hash_Map *variables);
std::string get_value_int(std::string line, Hash_Map *variables);
std::string get_next_string(std::string line, std::string string);
std::vector<std::string> get_all_string_space(std::string line);
std::vector<std::string> get_all_string_func(std::string line);
std::string get_first_string(std::string line);
char get_next_char(std::string line, std::string str);


bool is_str_in_str(std::string line, std::string string);
bool ft_strcmp(std::string str1, std::string str2);
size_t string_count(std::string line);
bool is_func_call(std::string line);
bool is_two_qoute(std::string line);
bool is_char(char c);
bool is_digit(char c);

#endif