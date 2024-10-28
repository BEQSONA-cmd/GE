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

void Parser::parse()
{
    size_t i = 0;
    while(i < this->lines.size())
    {
        std::string line = this->lines[i];
        if(!is_two_qoute(line))
            ft_error(line, 1);
        
        std::vector<std::string> words = get_all_string_space(this->lines[i]);
        if(words.size() == 0)
        {
            i++;
            continue;
        }
        
        if(words[0] == STRING || words[0] == INT)
            create_variable(line);
        
        if (words.size() > 2 && ((words[1] == "=") || (words[2] == "=")))
        {
            std::string key = get_previous_string(line, "=");
            Type type = this->variables->get_type(key);
            
            if(type == T_STRING)
                assign_string(line);
            else if(type == T_INT)
                assign_int(line);
            else
                ft_error(line, 8);
        }
        if(words.size() > 2 && ((words[1] == "+=") || (words[2] == "+=")))
        {
            std::string key = get_previous_string(line, "+=");
            Type type = this->variables->get_type(key);

            if(type == T_STRING)
                append_string(line);
            else if(type == T_INT)
                add_int(line);
            else
                ft_error(line, 8);
        }

        check_instruction(line);
        i++;
    }
}

