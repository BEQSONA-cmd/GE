#include "../Includes/Compiler.h"
#include <iostream>

void Compiler::compile(ASTNode* root) 
{
    if(root == nullptr) 
        return;
    int result = evaluate(root);
    std::cout << "Result: " << result << std::endl;
}

int Compiler::evaluate(ASTNode* node) 
{
    if (node->token.type == TokenType::NUMBER)
        return std::stoi(node->token.value);

    int leftValue = evaluate(node->left);
    int rightValue = evaluate(node->right);

    switch (node->token.type) 
    {
        case TokenType::PLUS:
            return leftValue + rightValue;
        case TokenType::MINUS:
            return leftValue - rightValue;
        case TokenType::MULT:
            return leftValue * rightValue;
        case TokenType::DIV:
            return leftValue / rightValue;
        default:
            return 0;
    }
}
