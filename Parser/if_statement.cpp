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

void Object::if_statement(std::string line, size_t *i) 
{
    if (!check_if_statement(line))
        return;

    if (check_condition(line))
        return;
    else 
    {
        Scope scope(this->lines, i);

        while (*i < this->lines.size() && !scope.is_end_of_scope(*i))
        {
            (*i)++;
        }
    }
}