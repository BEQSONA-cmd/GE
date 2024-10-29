#include "Includes/Parser.hpp"
#include "Includes/Executer.hpp"
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

bool parsing(std::vector<std::string> lines, std::vector<Object> &objects)
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

        if (words[0] == FUNC)
        {
            Object object(lines, &i);
            objects.push_back(object);
        }
        i++;
    }
    return 0;
}

int main(int ac, char** av) 
{
    if (ac < 2) 
    {
        std::cout << "Usage: " << av[0] << " <source-file.ge>" << std::endl;
        return 1;
    }
    if(!check_source_file(av))
        return 1;
    std::vector<std::string> Lines = get_all_lines(av);

    std::vector<Object> objects;

    if(parsing(Lines, objects))
        return 1;

    Excecuter excecuter(objects[0].get_instructions());
    excecuter.execute();
    
    return 0;
}
