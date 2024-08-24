#include "../Includes/Parser.h"

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), currentPosition(0) {}

Token Parser::currentToken() 
{
    if (currentPosition < tokens.size())
        return tokens[currentPosition];
    return { TokenType::END_OF_FILE, "" };
}

void Parser::advance() 
{
    currentPosition++;
}

ASTNode* Parser::parse() 
{
    return expression();
}

ASTNode* Parser::expression() 
{
    ASTNode* node = term();

    while (currentToken().type == TokenType::PLUS || currentToken().type == TokenType::MINUS) 
    {
        Token token = currentToken();
        advance();
        node = new ASTNode(token);
        node->left = node;
        node->right = term();
    }

    return node;
}

ASTNode* Parser::term() 
{
    ASTNode* node = factor();

    while (currentToken().type == TokenType::MULT || currentToken().type == TokenType::DIV) 
    {
        Token token = currentToken();
        advance();
        node = new ASTNode(token);
        node->left = node;
        node->right = factor();
    }

    return node;
}

ASTNode* Parser::factor() 
{
    Token token = currentToken();

    if (token.type == TokenType::NUMBER) 
    {
        advance();
        return new ASTNode(token);
    } 
    else if (token.type == TokenType::LPAREN) 
    {
        advance();
        ASTNode* node = expression();
        if (currentToken().type == TokenType::RPAREN)
            advance();
        return node;
    } 
    else
        return nullptr;
}
