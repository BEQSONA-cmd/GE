#include "../Includes/Parser.hpp"

Object::Object(std::vector<std::string> lines, size_t *iter, std::map<std::string, Object> functions) : Parser(lines)
{
    size_t i = *iter;
    // size_t save = i;

    std::vector<std::string> obj_lines;

    if (lines[i] != "{")
        i++;

    while (i < lines.size() && get_first_string(lines[i]) != "}")
    {
        obj_lines.push_back(lines[i]);
        i++;
    }

    *iter = i;
    this->lines = obj_lines;
    try 
    {
        this->parse(functions);
    } 
    catch (std::exception &e) 
    {
        std::cerr << e.what() << std::endl;
    }

    // this->print_instructions();
    // this->print_variables();
}
