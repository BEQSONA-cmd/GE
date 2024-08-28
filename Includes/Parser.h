#include "Lexer.h"

struct ASTNode 
{
    Token token;
    ASTNode* left;
    ASTNode* right;

    ASTNode(Token token)
    {
        this->token = token;
        this->left = NULL;
        this->right = NULL;
    }
};

class Parser 
{
    private:
        std::vector<Token> tokens;
        size_t iter;

        Token currentToken();
        ASTNode* makeNode(Token token);
        ASTNode* parseExpression();
        ASTNode* parsePrintStatement();
        ASTNode* parseString();
        ASTNode* parseIdentifier();

        Token makeToken(TokenType type, const std::string& value = "");

    public:
        // constructor
        Parser(std::vector<Token>& tokens);

        ASTNode* parse();
        void print_ast(ASTNode* node);
};