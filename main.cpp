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
    while (std::getline(sourceFile, line))
        lines.push_back(line);
    return lines;
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

    // size_t i = 0;
    // while(i < Lines.size())
    // {
    //     std::cout << Lines[i] << std::endl;
    //     i++;
    // }

    Parser parser(Lines);
    parser.parse();
    // parser.print_instructions();
    parser.print_variables();

    // Excecuter excecuter(parser.get_instructions());
    // excecuter.execute();
    


    return 0;
}
