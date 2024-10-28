#include "../Includes/Parser.hpp"

void Parser::check_instruction(std::string line)
{
    size_t i = 0;

    std::string value = "";
    std::string func = "";

    if(line.find(FUNC_PRINT) != std::string::npos)
    {
        if(!is_str_in_str(line, FUNC_PRINT))
            ft_error(line, 6);
        i = line.find(FUNC_PRINT) + FUNC_PRINT.length();
        func = FUNC_PRINT;
        while(line[i] != '(')
            i++;
        i++;
    }
    else if(line.find(FUNC_INPUT) != std::string::npos)
    {
        if(!is_str_in_str(line, FUNC_INPUT))
            ft_error(line, 6);
        i = line.find(FUNC_INPUT) + FUNC_INPUT.length();
        func = FUNC_INPUT;
        while(line[i] != '(')
            i++;
        i++;
    }
    else
        return;
    
    if(line[i] == '"')
    {
        while(line[i] != '"')
            i++;
        i++;
        while(line[i] != '"')
        {
            value += line[i];
            i++;
        }
    }
    else
    {
        std::string key = "";
        while(is_char(line[i]) && line[i] != ')')
        {
            key += line[i];
            i++;
        }
        value = this->variables->get(key);
    }
    this->instructions->insert(func, value, Type::T_FUNC);
}
