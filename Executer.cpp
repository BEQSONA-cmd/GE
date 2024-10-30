#include "Includes/Executer.hpp"

Excecuter::Excecuter(std::map<std::string, Object> functions)
{
    this->functions = functions;
}

void Excecuter::execute(Hash_Map *instructions)
{
    Hash_Map_Enter *current = instructions->head;
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
        else if (current->key == FUNC_CALL)
            call_function(current->value);
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

void Excecuter::call_function(std::string value)
{
    if (this->functions.find(value) != this->functions.end())
    {
        Object obj = this->functions[value];
        Hash_Map *func_instructions = obj.get_instructions();
        
        execute(func_instructions);
    }
}