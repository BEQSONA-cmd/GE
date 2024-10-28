#include "../Includes/Parser.hpp"

void Parser::assign_string(std::string line)
{
    std::string value = "";
    value = get_value_string(line, variables);

    if(value == "")
        ft_error(line, 8);
    
    std::string key = get_previous_string(line, "=");

    variables->replace(key, value);
}

void Parser::append_string(std::string line)
{
    std::string value = "";
    value = get_value_string(line, variables);

    if(value == "")
        ft_error(line, 8);
    std::string key = get_previous_string(line, "+=");

    std::string new_value = variables->get(key) + value;
    variables->replace(key, new_value);
}

void Parser::assign_int(std::string line)
{
    std::string value = "";
    value = get_value_int(line, variables);

    if(value == "")
        ft_error(line, 8);
    std::string key = get_previous_string(line, "=");

    variables->replace(key, value);
}

void Parser::add_int(std::string line)
{
    std::string value = "";
    value = get_value_int(line, variables);

    if(value == "")
        ft_error(line, 8);
    std::string key = get_previous_string(line, "+=");

    int new_value = ft_atoi(variables->get(key)) + ft_atoi(value);
    variables->replace(key, std::to_string(new_value));
}

void Parser::sub_int(std::string line)
{
    std::string value = "";
    value = get_value_int(line, variables);

    if(value == "")
        ft_error(line, 8);
    std::string key = get_previous_string(line, "-=");

    int new_value = ft_atoi(variables->get(key)) - ft_atoi(value);
    variables->replace(key, std::to_string(new_value));
}

void Parser::create_variable(std::string line)
{
    if(line.find(STRING) != std::string::npos)
    {
        if(!ft_strcmp(get_first_string(line) , STRING))
            return;
        if(string_count(line) < 2)
            ft_error(line, 6);
        std::string key = get_next_string(line, STRING);
        if(key == "")
            ft_error(line, 8);
        this->variables->insert(key, "", Type::T_STRING);
    }
    else if(line.find(INT) != std::string::npos)
    {
        if(!ft_strcmp(get_first_string(line) , INT))
            return;
        if(string_count(line) < 2)
            ft_error(line, 6);
        std::string key = get_next_string(line, INT);
        if(key == "")
            ft_error(line, 8);
        this->variables->insert(key, "0", Type::T_INT);
    }
}