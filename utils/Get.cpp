#include "../Includes/Parser.hpp"

bool ft_strchr(std::string str, char c)
{
    size_t i = 0;

    while(i < str.length())
    {
        if(str[i] == c)
            return true;
        i++;
    }
    return false;
}

char get_next_char(std::string line, std::string str)
{
    size_t i = 0;
    size_t j = 0;

    bool save = false;

    while(i < line.length())
    {
        while(line[i] == str[j] && j < line.length())
        {
            save = true;
            j++;
            i++;
        }
        if(save)
        {
            while(!is_char(line[i]) && i < line.length())
                i++;
            return(line[i]);
        }
        i++;
    }
    return '\0';

}

std::vector<std::string> get_all_string_space(std::string line)
{
    std::vector<std::string> strings = {};
    size_t i = 0;
    std::string str = "";

    while (i < line.length())
    {
        if (is_char(line[i]))
        {
            if (line[i] == '"')
            {
                i++;
                while (i < line.length() && line[i] != '"')
                {
                    str += line[i];
                    i++;
                }
                if (i < line.length())
                    str += line[i];
            }
            else
            {
                while (i < line.length() && is_char(line[i]))
                {
                    str += line[i];
                    i++;
                }
            }
            strings.push_back(str);
            str = "";
        }
        i++;
    }
    return strings;
}


std::vector<std::string> get_all_string_func(std::string line)
{
    std::vector<std::string> strings;
    size_t i = 0;
    std::string str = "";
    std::vector<std::string> space_strings = get_all_string_space(line);

    while(i < space_strings.size())
    {
        if(ft_strchr(space_strings[i], '('))
        {
            size_t j = 0;
            while(j < space_strings[i].length())
            {
                if(space_strings[i][j] == '(')
                {
                    strings.push_back(str);
                    str = "";
                }
                else if(space_strings[i][j] == ')')
                {
                    strings.push_back(str);
                    str = "";
                }
                else
                    str += space_strings[i][j];
                j++;
            }
        }
        else
            strings.push_back(space_strings[i]);
        i++;
    }
    return strings;
}

bool is_str_in_str(std::string line, std::string string)
{
    std::vector<std::string> strings = get_all_string_func(line);
    size_t i = 0;

    while(i < strings.size())
    {
        if(ft_strcmp(strings[i], string))
            return true;
        i++;
    }
    return false;
}

std::string get_first_string(std::string line)
{
    std::string first_string = "";
    size_t i = 0;

    while(!is_char(line[i]) && i < line.length())
        i++;
    while(is_char(line[i]))
    {
        first_string += line[i];
        i++;
    }
    return first_string;
}

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
        while(is_char(line[i]))
        {
            next_string += line[i];
            i++;
        }
    }
    else
    {
        std::vector<std::string> strings = get_all_string_space(line);
        while(i < strings.size())
        {
            if(ft_strcmp(strings[i], string))
                return strings[i + 1];
            i++;
        }
    }
    return next_string;
}

std::string get_previous_string(std::string line, std::string string)
{
    std::vector<std::string> strings = get_all_string_space(line);
    size_t i = 0;

    while(i < strings.size())
    {
        if(ft_strcmp(strings[i], string))
            return strings[i - 1];
        i++;
    }
    return "";
}

std::string get_value_string(std::string line, Hash_Map *variables)
{
    std::string value = "";
    size_t i = 0;
    while(line[i] != '"' && i < line.length())
        i++;
    if(i == line.length())
    {
        std::string key = "";
        key = get_next_string(line, "=");

        value = variables->get(key);
        if(key == "" || value == "")
            ft_error(line, 8);
        return value;
    }
    i++;
    while(line[i] != '"')
    {
        value += line[i];
        i++;
    }
    return value;
}

std::string get_value_int(std::string line, Hash_Map *variables)
{
    std::string value = "";
    std::string key = "";
    size_t i = 0;
    
    key = get_next_string(line, "=");
    if(key == "")
        ft_error(line, 8);
    
    if(!(is_digit(key[0]) || key[0] == '-'))
    {
        value = variables->get(key);
        if(value == "")
            ft_error(line, 8);
    }
    else
    {
        while(i < key.length())
        {
            if(is_digit(key[i]) || key[i] == '-')
                value += key[i];
            i++;
        }
    }
    return value;
}