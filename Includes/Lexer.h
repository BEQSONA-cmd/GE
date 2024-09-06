#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <iostream>

#define KEYWORD_PRINT "ბეჭდვა"
#define KEYWORD_PHRASE "ფრაზა"
#define KEYWORD_NUMBER "რიცხვი"

// რიცხვი ი = 15

// ფრაზა გამარჯობა = "გამარჯობა სამყარო 1"

// ბეჭდვა("გამარჯობა სამყარო 2\n")

// IDENTIFIER : ი , გამარჯობა
// PRINT : ბეჭდვა
// STRING : გამარჯობა სამყარო 1, გამარჯობა სამყარო 2\n
// LEFT_PAREN : (
// RIGHT_PAREN : )
// QUOTE : " , '
// EQUAL : =
// EOF_TOKEN : \0
// VALUE : 15 , გამარჯობა სამყარო 1

enum class TokenType 
{
    NUMBER,
    VALUE,
    PHRASE,
    IDENTIFIER,
    PRINT,
    STRING,
    LEFT_PAREN,
    RIGHT_PAREN,
    QUOTE,
    EQUAL,
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
        size_t line_iter; 
        std::string sourceCode;
        std::vector<std::string> Lines;

        // currentline should return the whole line where the iterator is
        std::string currentLine();
        char currentChar();
        Token makeToken(TokenType type, const std::string& value = "");

    public:
        // constructor
        Lexer(std::string& source, std::vector<std::string>& all_lines);

        std::vector<Token> tokenize();
        void print_lines();
        void print_all_tokens(std::vector<Token>& tokens);
};

#endif
