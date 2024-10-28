#include "../Includes/Parser.hpp"

bool is_char(char c)
{
    if(c != ' ' && c != '\t' && c != '\n' && c != '\0' && c != '\r' && c != '\v' && c != '\f')
        return true;
    return false;
}

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

std::vector<std::string> get_all_string_space(std::string line)
{
    std::vector<std::string> strings;
    size_t i = 0;
    std::string str = "";

    while(i < line.length())
    {
        if(is_char(line[i]))
        {
            if(line[i] == '"')
            {
                i++;
                while(line[i] != '"')
                {
                    str += line[i];
                    i++;
                }
                str += line[i];
            }
            else
            {
                while(is_char(line[i]))
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
        while(line[i] != string[0])
            i++;
        while(line[i] == string[i])
            i++;
        while(line[i] == ' ' || line[i] == '\t')
            i++;
        while(is_char(line[i]))
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
    while(line[i] != '"' && i < line.length())
    {
        i++;
    }
    if(i == line.length())
        return "";
    i++;
    while(line[i] != '"')
    {
        value += line[i];
        i++;
    }
    return value;
}

bool ft_strcmp(std::string str1, std::string str2)
{
    size_t i = 0;

    if(str1.length() != str2.length())
        return false;

    while(i < str1.length())
    {
        if(str1[i] != str2[i])
            return false;
        i++;
    }
    return true;
}

size_t string_count(std::string line)
{
    size_t i = 0;
    size_t count = 0;

    // skip the first spaces or tabs
    while(i < line.length() && !is_char(line[i]))
        i++;
    if(i == line.length())
        return 0;

    // count the number of strings
    while(i < line.length() && line[i] != '\0')
    {
        if(is_char(line[i]))
        {
            if(line[i] == '"')
            {
                i++;
                while(line[i] != '"')
                    i++;
            }
            // std::cout << static_cast<int>(line[i]) << std::endl;
            count++;
        }
        while(i < line.length() && is_char(line[i]))
            i++;
        i++;
    }
    return count;
}
