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

bool parsing(const std::vector<std::string>& lines, std::map<std::string, Object>& objects)
{
    size_t i = 0;
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
            std::string key = ft_trim(words[1]);
            Object object(lines, &i);
            objects[key] = object;
        }
        i++;
    }
    return false;
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

    if (parsing(lines, objects))
        return 1;

    auto it = objects.find("func2()");
    if (it == objects.end())
        return 1;

    Object object = it->second;

    Excecuter executer(objects);
    
    executer.execute(object.get_instructions());

    return 0;
}