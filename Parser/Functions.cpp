#include "../Includes/Parser.hpp"

void Parser::parse_functions(std::vector<std::string> words, std::string line, size_t *iter)
{
    if(words[0] == FUNC_FUNCTION)
    {
        std::string key = words[1];
        std::vector<std::string> function;
        size_t i = *iter + 1;
        while (i < this->lines.size())
        {
            std::string current_line = this->lines[i];
            std::vector<std::string> current_words = ft_split(current_line, ' ');
            if(get_first_string(current_line) == "{")
            {
                i++;
                continue;
            }
            if(get_first_string(current_line) == "}")
            {
                size_t j = 0;
                while(j < function.size())
                {
                    std::cout << function[j] << std::endl;
                    j++;
                }
                this->functions->insert(key, function, T_FUNC);
                *iter = i;
                return;
            }
            else
                function.push_back(current_line);
            i++;
        }
        ft_error(line, 10);
    }
}
