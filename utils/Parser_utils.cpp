#include "../Includes/Parser.hpp"

bool is_char(char c)
{
    if(c != ' ' && c != '\t' && c != '\n' && c != '\0' && c != '\r' && c != '\v' && c != '\f')
        return true;
    return false;
}

bool is_digit(char c)
{
    if(c >= '0' && c <= '9')
        return true;
    return false;
}

size_t ft_atoi(std::string str)
{
    size_t i = 0;
    size_t res = 0;

    while(i < str.length())
    {
        if(str[i] < '0' || str[i] > '9')
            return 0;

        if(str[i] >= '0' && str[i] <= '9')
            res = res * 10 + str[i] - '0';
        i++;
    }
    return res;
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

bool ft_strcmp(std::string str1, std::string str2)
{
    size_t i = 0;

    if(str1.length() != str2.length())
        return false;

    while(i < str1.length())
    {
        if(str1[i] != str2[i])
            return false;
        i++;
    }
    return true;
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
