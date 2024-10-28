#include "Includes/Parser.hpp"

Hash_Map *Parser::get_instructions()
{
    return this->instructions;
}

Parser::Parser(std::vector<std::string> lines)
{
    this->lines = lines;
    this->instructions = new Hash_Map();
    this->variables = new Hash_Map();
}

Parser::~Parser()
{
    Hash_Map_Enter *current = this->instructions->head;
    Hash_Map_Enter *next;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }
    delete this->instructions;

    current = this->variables->head;
    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }
    delete this->variables;
}

void Parser::check_instruction(std::string line)
{
    size_t i = 0;

    std::string value = "";
    std::string func = "";

    if(line.find(FUNC_PRINT) != std::string::npos)
    {
        if(!is_str_in_str(line, FUNC_PRINT))
            ft_error(line, 6, this);
        i = line.find(FUNC_PRINT) + FUNC_PRINT.length();
        func = FUNC_PRINT;
        while(line[i] != '(')
            i++;
        i++;
    }
    else if(line.find(FUNC_INPUT) != std::string::npos)
    {
        if(!is_str_in_str(line, FUNC_INPUT))
            ft_error(line, 6, this);
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

void Parser::check_variable(std::string line)
{
    if(line.find(STRING) != std::string::npos)
    {
        if(!ft_strcmp(get_first_string(line) , STRING))
            return;
        if(string_count(line) < 4)
            ft_error(line, 6, this);
        if(line.find('=') == std::string::npos)
            ft_error(line, 7, this);

        std::string key = "";
        std::string value = "";

        key = get_next_string(line, STRING);
        value = get_value_string(line);
        if(key == "" || value == "")
            ft_error(line, 2, this);
        this->variables->insert(key, value, Type::T_STRING);
    }
    else if(line.find(INT) != std::string::npos)
    {
        if(!ft_strcmp(get_first_string(line) , INT))
            return;
        if(string_count(line) < 4)
            ft_error(line, 6, this);
        if(line.find('=') == std::string::npos)
            ft_error(line, 7, this);
        std::string key = "";
        std::string value = "";
        size_t int_value = 0;

        key = get_next_string(line, INT);
        value = get_next_string(line, "=");
        int_value = ft_atoi(value);
        if(key == "" || value == "")
            ft_error(line, 3, this);
        if(int_value == 0 && value != "0")
            ft_error(line, 3, this);
        this->variables->insert(key, value, Type::T_INT);
    }
}

void Parser::parse()
{
    size_t i = 0;
    while(i < this->lines.size())
    {
        std::string line = this->lines[i];
        if(!is_two_qoute(line))
            ft_error(line, 1, this);
        check_variable(line);
        check_instruction(line);
        i++;
    }
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
