#include "../Includes/Parser.hpp"

bool is_func_call(std::string line)
{
    size_t i = 0;
    size_t count = 0;

    while(i < line.length())
    {
        if(line[i] == '(')
            count++;
        if(line[i] == ')')
            count++;
        i++;
    }
    if(count == 2)
    {
        if(is_str_in_str(line, FUNC))
            return false;
        return true;
    }
    return false;
}

bool is_two_qoute(std::string line)
{
    size_t i = 0;
    size_t count = 0;

    while(i < line.length())
    {
        if(line[i] == '"')
            count++;
        i++;
    }
    if(count == 2 || count == 0)
        return true;
    return false;
}

size_t string_count(std::string line)
{
    size_t i = 0;
    size_t count = 0;

    // skip the first spaces or tabs
    while(i < line.length() && !is_char(line[i]))
        i++;
    if(i == line.length())
        return 0;

    // count the number of strings
    while(i < line.length() && line[i] != '\0')
    {
        if(is_char(line[i]))
        {
            if(line[i] == '"')
            {
                i++;
                while(line[i] != '"')
                    i++;
            }
            // std::cout << static_cast<int>(line[i]) << std::endl;
            count++;
        }
        while(i < line.length() && is_char(line[i]))
            i++;
        i++;
    }
    return count;
}

void Parser::print_instructions()
{
    Hash_Map_Enter *current = this->instructions->head;
    int iter = 0;

    while (current != NULL)
    {
        std::cout << "Instruction (" << iter << ") : { ";
        if(current->type == Type::T_FUNC)
            std::cout << "(type: Function) ";
        std::cout << "(key: " << current->key << ") (value: " << current->value << ") }" << std::endl;
        current = current->next;
        iter++;
    }
}

void Parser::print_variables()
{
    Hash_Map_Enter *current = this->variables->head;
    int iter = 0;

    while (current != NULL)
    {
        std::cout << "Variable (" << iter << ") : { ";
        if(current->type == Type::T_INT)
            std::cout << "(type: Integer) ";
        else if(current->type == Type::T_STRING)
            std::cout << "(type: String) ";
        std::cout << "(key: " << current->key << ") value: (" << current->value << ") }" << std::endl;
        current = current->next;
        iter++;
    }
}
