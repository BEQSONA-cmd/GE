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
    if(line.find(FUNC_PRINT) != std::string::npos)
    {
        std::string value = "";
        i = line.find(FUNC_PRINT) + FUNC_PRINT.length();
        while(line[i] != '"')
        {
            i++;
        }
        i++;
        while(line[i] != '"')
        {
            value += line[i];
            i++;
        }
        this->instructions->insert(FUNC_PRINT, value, Type::T_FUNC);
    }
    else if(line.find(FUNC_INPUT) != std::string::npos)
    {
        std::string value = "";
        i = line.find(FUNC_INPUT) + FUNC_INPUT.length();
        while(line[i] != '"')
        {
            i++;
        }
        i++;
        while(line[i] != '"')
        {
            value += line[i];
            i++;
        }
        this->instructions->insert(FUNC_INPUT, value, Type::T_FUNC);
    }
}

void Parser::check_variable(std::string line)
{
    if(line.find(STRING) != std::string::npos)
    {
        if(line.find('=') == std::string::npos)
        {
            std::cout << "Error: Syntax error" << std::endl;
            return;
        }

        std::string key = "";
        std::string value = "";

        key = get_next_string(line, STRING);
        value = get_value_string(line);
        this->variables->insert(key, value, Type::T_STRING);


    }
    else if(line.find(INT) != std::string::npos)
    {
        if(line.find('=') == std::string::npos)
        {
            std::cout << "Error: Syntax error" << std::endl;
            return;
        }
        std::string key = "";
        std::string value = "";

        key = get_next_string(line, INT);
        value = get_next_string(line, "=");
        this->variables->insert(key, value, Type::T_INT);
    }
}

void Parser::parse()
{
    size_t i = 0;
    while(i < this->lines.size())
    {
        std::string line = this->lines[i];
        check_instruction(line);
        check_variable(line);
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
