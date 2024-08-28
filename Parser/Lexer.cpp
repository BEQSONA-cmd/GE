#include "../Includes/Lexer.h"

Lexer::Lexer(std::string& source)
{
    sourceCode = source;
    iter = 0;
}

char Lexer::currentChar() 
{
    if (iter >= sourceCode.length()) 
        return '\0';
    return sourceCode[iter];
}

Token Lexer::makeToken(TokenType type, const std::string& value) 
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

std::vector<Token> Lexer::tokenize() 
{
    std::vector<Token> tokens;
    
    while (currentChar() != '\0') 
    {
        
        if (currentChar() == '(') 
        {
            tokens.push_back(makeToken(TokenType::LEFT_PAREN, "("));
            iter++;
        } 
        else if (currentChar() == ')') 
        {
            tokens.push_back(makeToken(TokenType::RIGHT_PAREN, ")"));
            iter++;
        }
        else if (currentChar() == '"') 
        {
            iter++; 
            std::string strValue;
            while (currentChar() != '"' && currentChar() != '\0') 
            {
                strValue += currentChar();
                iter++;
            }
            tokens.push_back(makeToken(TokenType::STRING, strValue));
            iter++;
        } 
        else if (sourceCode.substr(iter, std::string(KEYWORD_PRINT).length()) == KEYWORD_PRINT) 
        {
            tokens.push_back(makeToken(TokenType::PRINT, KEYWORD_PRINT));
            iter += std::string(KEYWORD_PRINT).length();
        } 
        else if (currentChar() == ' ' || currentChar() == '\n' || currentChar() == '\t' || currentChar() == '\r')
            iter++;
        else 
        {
            std::string unknownValue;
            unknownValue += currentChar();
            tokens.push_back(makeToken(TokenType::UNKNOWN, unknownValue));
            iter++;
        }
    }
    
    tokens.push_back(makeToken(TokenType::EOF_TOKEN, ""));
    return tokens;
}

void Lexer::print_all_tokens(std::vector<Token>& tokens) 
{
    int i = 0;
    while(tokens[i].type != TokenType::EOF_TOKEN)
    {
        if(tokens[i].type == TokenType::IDENTIFIER)
            std::cout << "IDENTIFIER: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::UNKNOWN)
            std::cout << "UNKNOWN: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::PRINT)
            std::cout << "PRINT: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::STRING)
            std::cout << "STRING: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::LEFT_PAREN)
            std::cout << "LEFT_PAREN: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::RIGHT_PAREN)
            std::cout << "RIGHT_PAREN: " << tokens[i].value << std::endl;
        i++;
    }
    std::cout << "EOF" << std::endl;
}
