#ifndef COMPILER_H
#define COMPILER_H

#include "Parser.h"

class Compiler 
{
    public:
        void compile(ASTNode* root);

    private:
        int evaluate(ASTNode* node);
};

#endif
