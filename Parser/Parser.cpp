#include "../Includes/Parser.h"

Parser::Parser(std::vector<Token>& tokens)
{
    this->tokens = tokens;
    iter = 0;
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
    return parsePrintStatement();
}

ASTNode* Parser::parsePrintStatement() 
{
    Token token = currentToken();
    if (token.type != TokenType::PRINT) 
    {
        std::cerr << "Error: Expected print statement" << std::endl;
        return NULL;
    }

    iter++;
    ASTNode* node = makeNode(token);
    node->left = parseExpression();
    return node;
}

ASTNode* Parser::parseExpression() 
{
    Token token = currentToken();
    if (token.type == TokenType::STRING) 
    {
        iter++;
        return makeNode(token);
    } 
    else if (token.type == TokenType::IDENTIFIER) 
    {
        iter++;
        return makeNode(token);
    } 
    else if (token.type == TokenType::LEFT_PAREN) 
    {
        iter++;
        ASTNode* node = makeNode(token);
        node->left = parseExpression();
        token = currentToken();
        if (token.type != TokenType::RIGHT_PAREN) 
        {
            std::cerr << "Error: Expected right parenthesis" << std::endl;
            return NULL;
        }
        iter++;
        return node;
    } 
    return NULL;
}

Token Parser::makeToken(TokenType type, const std::string& value) 
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

void Parser::print_ast(ASTNode* node) 
{
    if (node == NULL) 
        return;

    if (node->token.type == TokenType::PRINT)
    {
        std::cout << "function print (";
        std::cout << node->token.value;
        std::cout << ") " << std::endl;
        // if token is print it should have a left child
        
        // this will be '(' 
        node = node->left;
        
        // this will be the string
        node = node->left;
        std::cout << "output string (";
        std::cout << node->token.value;
        std::cout << ") " << std::endl;
    }
    else if (node->token.type == TokenType::IDENTIFIER) 
    {
        std::cout << "identifier (";
        std::cout << node->token.value;
        std::cout << ")" << std::endl;

        node = node->left;
        std::cout << "value (";
        std::cout << node->token.value;
        std::cout << ") " << std::endl;
    }

    print_ast(node->right);
    print_ast(node->left);
}
