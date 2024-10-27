#include "Includes/Parser.hpp"

std::string get_next_string(std::string line, std::string string)
{
    std::string next_string = "";
    size_t i = 0;

    if(string == "=")
    {
        while(line[i] != '=')
            i++;
        i++;
        while(line[i] == ' ' || line[i] == '\t')
            i++;
        while(isprint(line[i]) && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\0')
        {
            next_string += line[i];
            i++;
        }
    }
    else
    {
        while(line[i] != string[0])
            i++;
        while(line[i] == string[i])
            i++;
        while(line[i] == ' ' || line[i] == '\t')
            i++;
        while(line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\0')
        {
            next_string += line[i];
            i++;
        }
    }
    return next_string;
}

std::string get_value_string(std::string line)
{
    std::string value = "";
    size_t i = 0;
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
    return value;
}

Hash_Map *Parser::get_instructions()
{
    return this->instructions;
}

Hash_Map::Hash_Map()
{
    this->head = NULL;
}

void Hash_Map::insert(std::string key, std::string value , Type type)
{
    Hash_Map_Enter *new_enter = new Hash_Map_Enter();
    new_enter->key = key;
    new_enter->value = value;
    new_enter->type = type;
    new_enter->next = this->head;
    this->head = new_enter;
}

std::string Hash_Map::get(std::string key)
{
    Hash_Map_Enter *current = this->head;
    while (current != NULL)
    {
        if (current->key == key)
            return current->value;
        current = current->next;
    }
    return "";
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
