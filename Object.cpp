#include "Includes/Parser.hpp"

Hash_Map *Object::get_instructions()
{
    return this->instructions;
}

Hash_Map *Object::get_variables()
{
    return this->variables;
}

Object::Object(std::vector<std::string> lines, size_t *iter, bool main)
{
    this->lines = lines;
    this->instructions = new Hash_Map();
    this->variables = new Hash_Map();

    if(!main)
    {
        Scope obj_scope = Scope(lines, iter);
        size_t i = *iter;

        std::vector<std::string> obj_lines;
        
        while (i < lines.size() && !obj_scope.is_end_of_scope(i))
        {
            obj_lines.push_back(lines[i]);
            i++;
        }

        *iter = i;
        this->lines = obj_lines;
    }
    
    try 
    {
        this->parse();
    } 
    catch (std::exception &e) 
    {
        std::cerr << e.what() << std::endl;
    }

    // this->print_instructions();
    // this->print_variables();
}

void Object::parse_variables(std::vector<std::string> words, std::string line)
{
    if(words[0] == STRING || words[0] == INT)
        this->create_variable(line);

    if (words.size() > 2 && ((words[1] == "=") || (words[2] == "=")))
    {
        std::string key = get_previous_string(line, "=");
        Type type = this->variables->get_type(key);

        if(type == T_STRING)
            this->assign_string(line);
        else if(type == T_INT)
            this->assign_int(line);
        else
            ft_error(line, 8);
    }
    else if (words.size() > 2 && ((words[1] == "+=") || (words[2] == "+=")))
    {
        std::string key = get_previous_string(line, "+=");
        Type type = this->variables->get_type(key);

        if(type == T_STRING)
            this->append_string(line);
        else if(type == T_INT)
            this->add_int(line);
        else
            ft_error(line, 8);
    }
    else if (words.size() > 2 && ((words[1] == "-=") || (words[2] == "-=")))
    {
        std::string key = get_previous_string(line, "-=");
        Type type = this->variables->get_type(key);

        if(type == T_INT)
            this->sub_int(line);
        else
            ft_error(line, 9);
    }
}

void Object::parse()
{
    size_t iter = 0;

    while(iter < this->lines.size())
    {
        std::string line = this->lines[iter];
        if(!is_two_qoute(line))
            ft_error(line, 1);

        std::vector<std::string> words = get_all_string_space(this->lines[iter]);
        
        if(words.size() == 0)
        {
            iter++;
            continue;
        }
        else_statement(line, &iter);
        if_statement(line, &iter);
        parse_variables(words, line);
        check_instruction(line);
        iter++;
    }
}

