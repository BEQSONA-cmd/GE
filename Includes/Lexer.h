#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iostream>

#define KEYWORD_FUNCTION "ფუნქცია"
#define KEYWORD_PRINT "ბეჭდვა"
#define KEYWORD_RETURN "დააბრუნე"
#define KEYWORD_IF "თუ"
#define KEYWORD_WHILE "სანამ"
#define KEYWORD_MAIN "მთავარი"

enum class TokenType 
{
    IDENTIFIER,
    NUMBER,
    PLUS,
    MINUS,
    MULT,
    DIV,
    LPAREN,
    RPAREN,
    EQUALS,
    LESS_THAN,
    GREATER_THAN,
    IF,
    WHILE,
    FUNCTION,
    RETURN,
    PRINT,
    EOF_TOKEN,
    UNKNOWN,
    MAIN
};

struct Token 
{
    TokenType type;
    std::string value;
};

class Lexer
{
    public:
        Lexer(std::string& source);
        std::vector<Token> tokenize();
        void print_all_tokens(std::vector<Token>& tokens);

    private:
        std::string sourceCode;
        size_t iter;
        char currentChar();


        Token makeToken(TokenType type, const std::string& value = "");
        Token tokenizeIdentifier();
        Token tokenizeNumber();
};

#endif
