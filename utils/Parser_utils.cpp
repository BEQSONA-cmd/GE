#include "../includes/Parser.hpp"

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

