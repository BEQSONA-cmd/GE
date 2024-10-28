#include "Includes/Executer.hpp"

Excecuter::Excecuter(Hash_Map *instructions)
{
    this->instructions = instructions;
}

#include <stack>

void Excecuter::execute()
{
    Hash_Map_Enter *current = this->instructions->head;
    std::stack<Hash_Map_Enter*> nodeStack;
    
    while (current != NULL)
    {
        nodeStack.push(current);
        current = current->next;
    }

    while (!nodeStack.empty())
    {
        current = nodeStack.top();
        nodeStack.pop();

        if (current->key == FUNC_PRINT)
            print_function(current->value);
        else if (current->key == FUNC_INPUT)
            input_function(current->value);
    }
}


// attributes:
void Excecuter::print_function(std::string value)
{
    std::cout << value << std::endl;
}

std::string Excecuter::input_function(std::string value)
{
    std::string input;
    std::cout << value;
    std::cin >> input;
    return input;
}
