#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

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
    END_OF_FILE,
    UNKNOWN
};

struct Token 
{
    TokenType type;
    std::string value;
};

class Lexer 
{
    public:
        Lexer(const std::string& source);
        std::vector<Token> tokenize();

    private:
        std::string sourceCode;
        size_t currentPosition;
        char currentChar();

        void advance();
        Token makeToken(TokenType type, const std::string& value = "");
        Token tokenizeIdentifier();
        Token tokenizeNumber();
};

#endif
