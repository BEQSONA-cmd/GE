#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.hpp"

#define FUNC_PRINT "ბეჭდვა"
#define FUNC_INPUT "შეყვანა"
#define FUNC_IF "თუ"
#define FUNC_FUNCTION "ფუნქცია"


class Excecuter
{
    private:
        Hash_Map *instructions;
    public:
        Excecuter(Hash_Map *instructions);
        void execute();
};


#endif