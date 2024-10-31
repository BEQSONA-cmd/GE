#include "../Includes/Parser.hpp"

bool check_while_statement(std::string line)
{
    if(line.find(WHILE) != std::string::npos)
    {
        if(get_next_char(line, WHILE) == '(')
            return true;
    }
    return false;
}

void Object::while_statement(std::string line, size_t *i)
{
    if(!check_while_statement(line))
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
