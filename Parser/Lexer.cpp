#include "../Includes/Lexer.h"

Lexer::Lexer(const std::string& source) : sourceCode(source), currentPosition(0) {}

char Lexer::currentChar() 
{
    if (currentPosition >= sourceCode.length()) 
        return '\0';
    return sourceCode[currentPosition];
}

void Lexer::advance() 
{
    currentPosition++;
}

Token Lexer::makeToken(TokenType type, const std::string& value) 
{
    return { type, value };
}

std::vector<Token> Lexer::tokenize() 
{
    std::vector<Token> tokens;

    while (currentChar() != '\0') 
    {
        if (isspace(currentChar()))
            advance();
        else if (isalpha(currentChar())) 
            tokens.push_back(tokenizeIdentifier());
        else if (isdigit(currentChar())) 
            tokens.push_back(tokenizeNumber());
        else if (currentChar() == '+') 
        {
            tokens.push_back(makeToken(TokenType::PLUS));
            advance();
        } 
        else if (currentChar() == '-') 
        {
            tokens.push_back(makeToken(TokenType::MINUS));
            advance();
        } 
        else if (currentChar() == '*') 
        {
            tokens.push_back(makeToken(TokenType::MULT));
            advance();
        } 
        else if (currentChar() == '/') 
        {
            tokens.push_back(makeToken(TokenType::DIV));
            advance();
        } 
        else if (currentChar() == '(') 
        {
            tokens.push_back(makeToken(TokenType::LPAREN));
            advance();
        } 
        else if (currentChar() == ')') 
        {
            tokens.push_back(makeToken(TokenType::RPAREN));
            advance();
        } 
        else 
        {
            tokens.push_back(makeToken(TokenType::UNKNOWN, std::string(1, currentChar())));
            advance();
        }
    }

    tokens.push_back(makeToken(TokenType::END_OF_FILE));
    return tokens;
}

Token Lexer::tokenizeIdentifier() 
{
    std::string result;
    while (isalpha(currentChar())) 
    {
        result += currentChar();
        advance();
    }
    return makeToken(TokenType::IDENTIFIER, result);
}

Token Lexer::tokenizeNumber() 
{
    std::string result;
    while (isdigit(currentChar())) 
    {
        result += currentChar();
        advance();
    }
    return makeToken(TokenType::NUMBER, result);
}
