#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "Parser.hpp"

class Excecuter
{
    private:
        Hash_Map *instructions;
        std::map<std::string, Object> functions;
    public:
        Excecuter(std::map<std::string, Object> functions);
        void execute(Hash_Map *instructions);

    // attributes:
        void print_function(std::string value);
        std::string input_function(std::string value);
        void call_function(std::string value);
};


#endif