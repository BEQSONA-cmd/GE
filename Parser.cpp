#include "Includes/Parser.hpp"

Hash_Map *Parser::get_instructions()
{
    return this->instructions;
}

Hash_Map::Hash_Map()
{
    this->head = NULL;
}

void Hash_Map::insert(std::string key, std::string value)
{
    Hash_Map_Enter *new_node = new Hash_Map_Enter();
    new_node->key = key;
    new_node->value = value;
    new_node->next = this->head;
    this->head = new_node;
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
}

void Parser::check_instruction(std::string line)
{
    size_t i = 0;
    if(line.find(FUNC_PRINT) != std::string::npos)
    {
        // we well go each character and find " and while we are in the " we will add the character to the string
        std::string value = "";
        i = line.find(FUNC_PRINT) + FUNC_PRINT.length();
        // next it willbe ( and " 
        // ბეჭდვა("გამარჯობა სამყარო")
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
        this->instructions->insert(FUNC_PRINT, value);
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
        this->instructions->insert(FUNC_INPUT, value);
    }
}

void Parser::parse()
{
    size_t i = 0;
    while(i < this->lines.size())
    {
        std::string line = this->lines[i];
        check_instruction(line);
        i++;
    }
}

void Parser::print_instructions()
{
    Hash_Map_Enter *current = this->instructions->head;
    while (current != NULL)
    {
        std::cout << "Key: " << current->key << " Value: " << current->value << std::endl;
        current = current->next;
    }
}
