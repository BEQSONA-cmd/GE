#include "../Includes/Parser.hpp"


        // if(is_func_call(lines[i]))
        // {
        //     std::string func_name = get_first_string(lines[i]);
        //     if (functions.find(func_name) != functions.end())
        //     {
        //         Object obj = functions[func_name];
        //         Hash_Map *func_instructions = obj.get_instructions();
                
        //         while(func_instructions->head != NULL)
        //         {
        //             std::string key = func_instructions->head->key;
        //             std::string value = func_instructions->head->value;
        //             Type type = func_instructions->head->type;

        //             this->instructions->insert(key, value, type);

        //             func_instructions->head = func_instructions->head->next;
        //         }
        //     }
        // }

void Parser::check_instruction(std::string line, std::map<std::string, Object> funcs)
{
    size_t i = 0;
    (void)funcs;
    bool skip = false;

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
    else if (is_func_call(line))
    {
        std::string func_name = get_first_string(line);
        func = FUNC_CALL;
        value = func_name;   
        skip = true;
    }
    else
        return;
    
    if(line[i] == '"' && !skip)
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
    else if(!skip)
    {
        std::string key = "";
        while(is_char(line[i]) && line[i] != ')')
        {
            key += line[i];
            i++;
        }
        value = this->variables->get(key);
    }
    if(value == "")
        ft_error(line, 8);
    this->instructions->insert(func, value, Type::T_FUNC);
}
