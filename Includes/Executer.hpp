#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.hpp"

class Excecuter
{
    private:
        Hash_Map *instructions;
    public:
        Excecuter(Hash_Map *instructions);
        void execute();

    // attributes:
        void print_function(std::string value);
        std::string input_function(std::string value);
};


#endif