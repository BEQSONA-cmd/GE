#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iostream>

#define KEYWORD_PRINT "ბეჭდვა"

enum class TokenType 
{
    IDENTIFIER,
    PRINT,
    STRING,
    LEFT_PAREN,
    RIGHT_PAREN,
    QUOTE,
    EOF_TOKEN,
    UNKNOWN,
};

struct Token 
{
    TokenType type;
    std::string value;
};

class Lexer
{
    private:
        size_t iter;
        std::string sourceCode;

        char currentChar();
        Token makeToken(TokenType type, const std::string& value = "");

    public:
        // constructor
        Lexer(std::string& source);

        std::vector<Token> tokenize();
        void print_all_tokens(std::vector<Token>& tokens);
};

#endif
