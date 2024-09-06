#include <iostream>
#include <fstream>
#include <string>
#include "Includes/Lexer.h"
#include "Includes/Parser.h"

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

    std::string filename = av[1];
    std::ifstream sourceFile(filename);    

    if (!sourceFile) 
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string sourceCode((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
    std::vector<std::string> Lines;
    Lines = get_all_lines(av);

    Lexer lexer(sourceCode, Lines);
    auto tokens = lexer.tokenize();
    // lexer.print_all_tokens(tokens);

    // Parser parser(tokens);
    // auto ast = parser.parse();
    // parser.print_ast(ast);

    // delete ast;

    return 0;
}

