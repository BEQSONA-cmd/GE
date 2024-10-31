#include "../Includes/Parser.hpp"

bool Object::check_condition(std::string line)
{
    size_t start = line.find('(');
    size_t end = line.find(')');

    bool is_int = false;

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
        is_int = true;
    }
    else if(left_str.find("\"") != std::string::npos)
    {
        left_str = left_str.substr(1, left_str.length() - 2);
        is_int = false;
    }   
    else
    {
        Type type = this->variables->get_type(left_str);
        if(type == T_INT)
        {
            left = ft_atoi(this->variables->get(left_str));
            is_int = true;
        }
        else if(type == T_STRING)
        {
            left_str = this->variables->get(left_str);
            is_int = false;
        }
        else
        {
            std::cerr << "Invalid variable: " << left_str << std::endl;
            return false;
        }
    }
    if(is_digit(right_str[0]) || right_str[0] == '-')
    {
        right = ft_atoi(right_str);
        is_int = true;
    }
    else if(right_str.find("\"") != std::string::npos)
    {
        right_str = right_str.substr(1, right_str.length() - 2);
        is_int = false;
    }
    else
    {
        Type type = this->variables->get_type(right_str);
        if(type == T_INT)
        {
            right = ft_atoi(this->variables->get(right_str));
            is_int = true;
        }
        else if(type == T_STRING)
        {
            right_str = this->variables->get(right_str);
            is_int = false;
        }
        else
        {
            std::cerr << "Invalid variable: " << right_str << std::endl;
            return false;
        }
    }

    // if(!is_int)
    // {
    //     std::cout << "left_str" << ": " << left_str << std::endl;
    //     std::cout << "right_str" << ": " << right_str << std::endl;
    // }
    // else
    // {
    //     std::cout << "left: " << left << std::endl;
    //     std::cout << "right: " << right << std::endl;
    //     std::cout << "op: " << op << std::endl;
    // }


    if(!is_int)
    {
        if (op == EQUAL)
            return left_str == right_str;
        else if (op == NOT_EQUAL)
            return left_str != right_str;
        else 
        {
            std::cerr << "Unsupported operator: " << op << std::endl;
            return false;
        }
    }
    else
    {
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
}
