#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Lexer.h"

struct ASTNode {
    Token token;
    ASTNode* left;
    ASTNode* right;

    ASTNode(Token token) : token(token), left(nullptr), right(nullptr) {}
};

class Parser {
public:
    Parser(std::vector<Token>& tokens);
    ASTNode* parse();

private:
    std::vector<Token> tokens;
    size_t currentPosition;

    Token currentToken();
    void advance();
    ASTNode* expression();
    ASTNode* term();
    ASTNode* factor();
};

#endif
