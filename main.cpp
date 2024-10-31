#include "Includes/Parser.hpp"
#include "Includes/Executer.hpp"
#include "Includes/Utils.hpp"
#include <vector>

bool check_source_file(char **av)
{
    std::string sourceFile = av[1];
    if (sourceFile.substr(sourceFile.find_last_of(".") + 1) != "ge")
    {
        std::cout << "Invalid file extension. Please provide a file with .ge extension." << std::endl;
        return false;
    }

    std::ifstream file(sourceFile);
    if (!file.is_open())
    {
        std::cout << "Could not open the file. Please check the file path." << std::endl;
        return false;
    }

    return true;
}

std::vector<std::string> get_all_lines(char **av)
{
    std::ifstream sourceFile(av[1]);
    std::string line;
    std::vector<std::string> lines;
    std::string next_line = "";

    while (std::getline(sourceFile, line))
        lines.push_back(line);
    return lines;
}


Object parsing(std::vector<std::string> lines, std::map<std::string, Object> &objects)
{
    size_t i = 0;
    std::vector<std::string> main_lines;

    while (i < lines.size())
    {
        std::string line = lines[i];
        std::vector<std::string> words = ft_split(line, ' ');

        if (words.size() == 0)
        {
            i++;
            continue;
        }
        if (words[0] == FUNC && words.size() > 1)
        {
            std::string key = ft_trim_func(words[1]);
            Object object(lines, &i , false);
            objects[key] = object;
        }
        else
            main_lines.push_back(line);
        i++;
    }

    Object main_object = Object(main_lines, &i, true);

    return main_object;
}

int main(int ac, char** av) 
{
    if (ac < 2) 
    {
        std::cout << "Usage: " << av[0] << " <source-file.ge>" << std::endl;
        return 1;
    }
    if (!check_source_file(av))
        return 1;

    std::vector<std::string> lines = get_all_lines(av);
    std::map<std::string, Object> objects;

    Object main_object = parsing(lines, objects);

    Excecuter executer(objects);
    executer.execute(main_object.get_instructions());
    free_hash_map(objects);
    delete main_object.get_instructions();
    delete main_object.get_variables();

    return 0;
}