#include "../Includes/Parser.hpp"

// function main()
// {

//     int i = 15
    
//     if(i < 20)
//     {
//         print(i)
//         i += 1
//     }
// }

#include <iostream>
#include <string>
#include <sstream>

bool Object::check_condition(std::string line)
{
    size_t start = line.find('(');
    size_t end = line.find(')');
    if (start == std::string::npos || end == std::string::npos || start >= end)
        return false;
    
    std::string condition = line.substr(start + 1, end - start - 1);
    std::string left_str = "";
    std::string right_str = "";
    std::string op = "";
    size_t i = 0;
    while (i < condition.length() && condition[i] != ' ')
    {
        left_str += condition[i];
        i++;
    }
    while (i < condition.length() && condition[i] == ' ')
        i++;
    while (i < condition.length() && condition[i] != ' ')
    {
        op += condition[i];
        i++;
    }
    while (i < condition.length() && condition[i] == ' ')
        i++;
    while (i < condition.length())
    {
        right_str += condition[i];
        i++;
    }
    if (left_str == "" || right_str == "" || op == "")
    {
        std::cerr << "Invalid condition: " << condition << std::endl;
        return false;
    }

    long long left = 0;
    long long right = 0;

    if (is_digit(left_str[0]) || left_str[0] == '-')
    {
        left = ft_atoi(left_str);
    }
    else
    {
        std::string value = this->variables->get(left_str);
        if (value == "")
        {
            std::cerr << "Variable not found: " << left_str << std::endl;
            return false;
        }
        left = ft_atoi(value);
    }
    if(is_digit(right_str[0]) || right_str[0] == '-')
    {
        right = ft_atoi(right_str);
    }
    else
    {
        std::string value = this->variables->get(right_str);
        if (value == "")
        {
            std::cerr << "Variable not found: " << right_str << std::endl;
            return false;
        }
        right = ft_atoi(value);
    }

    // std::cout << "left: " << left << std::endl;
    // std::cout << "right: " << right << std::endl;
    // std::cout << "op: " << op << std::endl;

    if (op == LESS)
        return left < right;
    else if (op == GREATER)
        return left > right;
    else if (op == EQUAL)
        return left == right;
    else if (op == NOT_EQUAL)
        return left != right;
    else if (op == LESS_EQUAL)
        return left <= right;
    else if (op == GREATER_EQUAL)
        return left >= right;
    else 
    {
        std::cerr << "Unsupported operator: " << op << std::endl;
        return false;
    }
}


bool check_if_statement(std::string line)
{
    if(line.find(IF) != std::string::npos)
    {
        if(get_next_char(line, IF) == '(')
            return true;
    }
    return false;
}

void Object::if_statement(std::string line, size_t *i)
{
    if(!check_if_statement(line))
        return;
    else
    {
        if(check_condition(line))
            return;
        else
        {
            while(get_first_string(this->lines[*i]) != "}")
                (*i)++;
        }
    }
}