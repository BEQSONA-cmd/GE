#include "../Includes/Parser.hpp"

Scope::Scope(std::vector<std::string> lines, size_t *iter)
{
    size_t i = *iter;

    size_t scope = 0;

    this->end = 0;

    if (lines[i].find('{') != std::string::npos)
        i++;

    while (i < lines.size())
    {
        std::string line = lines[i];
        if(line.find('{') != std::string::npos)
            scope++;
        
        if(line.find('}') != std::string::npos)
        {
            scope--;
            if(scope == 0)
            {
                this->end = i;
                break;
            }
        }
        i++;
    }
}

bool Scope::is_end_of_scope(size_t i)
{
    return i == this->end;
}
