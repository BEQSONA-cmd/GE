#include "../Includes/Parser.h"

Parser::Parser(std::vector<Token>& tokens)
{
    this->tokens = tokens;
    iter = 0;
}

Token Parser::makeToken(TokenType type, const std::string& value) 
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

Token Parser::currentToken() 
{
    if (iter >= tokens.size()) 
        return makeToken(TokenType::EOF_TOKEN);
    return tokens[iter];
}

ASTNode* Parser::makeNode(Token token) 
{
    return new ASTNode(token);
}

ASTNode* Parser::parse() 
{
    return parseExpression();
}


ASTNode* Parser::parseExpression() 
{
    Token token = currentToken();
    if (token.type == TokenType::PRINT) 
    {
        iter++;
        return parsePrintStatement();
    } 
    else if (token.type == TokenType::STRING) 
    {
        iter++;
        return parseString();
    } 
    else if (token.type == TokenType::IDENTIFIER) 
    {
        iter++;
        return parseIdentifier();
    } 
    else 
    {
        std::cerr << "Error: Unexpected token " << token.value << std::endl;
        return NULL;
    }
}

ASTNode* Parser::parsePrintStatement() 
{
    ASTNode* node = makeNode(currentToken());
    iter++;
    node->left = parseExpression();
    return node;
}

ASTNode* Parser::parseString() 
{
    ASTNode* node = makeNode(currentToken());
    iter++;
    return node;
}

ASTNode* Parser::parseIdentifier() 
{
    ASTNode* node = makeNode(currentToken());
    iter++;
    return node;
}

void Parser::print_ast(ASTNode* node) 
{
    if (node == NULL) 
        return;
    
    std::cout << node->token.value << std::endl;
    print_ast(node->left);
    print_ast(node->right);
}