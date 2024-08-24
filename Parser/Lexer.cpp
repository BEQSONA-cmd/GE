#include "../Includes/Lexer.h"

Lexer::Lexer(std::string& source) : sourceCode(source), iter(0) {}

char Lexer::currentChar() 
{
    if (iter >= sourceCode.length()) 
        return '\0';
    return sourceCode[iter];
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
            iter++;
        else if (isalpha(currentChar())) 
            tokens.push_back(tokenizeIdentifier());
        else if (isdigit(currentChar())) 
            tokens.push_back(tokenizeNumber());
        else if (currentChar() == '+') 
        {
            tokens.push_back(makeToken(TokenType::PLUS));
            iter++;
        } 
        else if (currentChar() == '-') 
        {
            tokens.push_back(makeToken(TokenType::MINUS));
            iter++;
        } 
        else if (currentChar() == '*') 
        {
            tokens.push_back(makeToken(TokenType::MULT));
            iter++;
        } 
        else if (currentChar() == '/') 
        {
            tokens.push_back(makeToken(TokenType::DIV));
            iter++;
        } 
        else if (currentChar() == '(') 
        {
            tokens.push_back(makeToken(TokenType::LPAREN));
            iter++;
        } 
        else if (currentChar() == ')') 
        {
            tokens.push_back(makeToken(TokenType::RPAREN));
            iter++;
        } 
        else 
        {
            tokens.push_back(makeToken(TokenType::UNKNOWN, std::string(1, currentChar())));
            iter++;
        }
    }

    tokens.push_back(makeToken(TokenType::EOF_TOKEN));
    return tokens;
}

Token Lexer::tokenizeIdentifier() 
{
    std::string result;
    while (isalpha(currentChar())) 
    {
        result += currentChar();
        iter++;
    }

    if (result == KEYWORD_FUNCTION)
        return makeToken(TokenType::FUNCTION, result);
    else if (result == KEYWORD_PRINT)
        return makeToken(TokenType::PRINT, result);
    else if (result == KEYWORD_RETURN)
        return makeToken(TokenType::RETURN, result);
    else if (result == KEYWORD_IF)
        return makeToken(TokenType::IF, result);
    else if (result == KEYWORD_WHILE)
        return makeToken(TokenType::WHILE, result);
    else if (result == KEYWORD_MAIN)
        return makeToken(TokenType::IDENTIFIER, result);

    return makeToken(TokenType::IDENTIFIER, result);
}


Token Lexer::tokenizeNumber() 
{
    std::string result;
    while (isdigit(currentChar())) 
    {
        result += currentChar();
        iter++;
    }
    return makeToken(TokenType::NUMBER, result);
}


void Lexer::print_all_tokens(std::vector<Token>& tokens) 
{
    int i = 0;
    while(tokens[i].type != TokenType::EOF_TOKEN)
    {
        if(tokens[i].type == TokenType::IDENTIFIER)
            std::cout << "IDENTIFIER: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::NUMBER)
            std::cout << "NUMBER: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::PLUS)
            std::cout << "PLUS" << std::endl;
        else if(tokens[i].type == TokenType::MINUS)
            std::cout << "MINUS" << std::endl;
        else if(tokens[i].type == TokenType::MULT)
            std::cout << "MULT" << std::endl;
        else if(tokens[i].type == TokenType::DIV)
            std::cout << "DIV" << std::endl;
        else if(tokens[i].type == TokenType::LPAREN)
            std::cout << "LPAREN" << std::endl;
        else if(tokens[i].type == TokenType::RPAREN)
            std::cout << "RPAREN" << std::endl;
        else if(tokens[i].type == TokenType::UNKNOWN)
            std::cout << "UNKNOWN: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::FUNCTION)
            std::cout << "FUNCTION: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::RETURN)
            std::cout << "RETURN: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::PRINT)
            std::cout << "PRINT: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::IF)
            std::cout << "IF: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::WHILE)
            std::cout << "WHILE: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::EOF_TOKEN)
            std::cout << "EOF" << std::endl;
        else if(tokens[i].type == TokenType::MAIN)
            std::cout << "MAIN: " << tokens[i].value << std::endl;
        i++;
    }
}