#include "../Includes/Parser.hpp"

bool check_if_statement(std::string line)
{
    if(line.find(IF) != std::string::npos)
    {
        if(get_next_char(line, IF) == '(')
            return true;
    }
    return false;
}

bool check_else_statement(std::string line)
{
    if(line.find(ELSE) != std::string::npos)
        return true;
    return false;
}

void Object::else_statement(std::string line, size_t *i)
{
    if (!check_else_statement(line))
        return;
    Scope else_scope = Scope(this->lines, i);

    while (*i < this->lines.size() && !else_scope.is_end_of_scope(*i))
        (*i)++;
}

void Object::if_statement(std::string line, size_t *i) 
{
    if (!check_if_statement(line))
        return;
    Scope if_scope = Scope(this->lines, i);

    if (check_condition(line))
        return;
    else 
    {
        while (*i < this->lines.size() && !if_scope.is_end_of_scope(*i))
            (*i)++;
        (*i)++;
        if(check_else_statement(this->lines[*i]))
        {
            if(this->lines[*i].find("{") == std::string::npos)
                (*i)++;
        }
    }
}