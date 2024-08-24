#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "Includes/Lexer.h"
#include "Includes/Parser.h"
#include "Includes/Compiler.h"

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

    int i = 0;

    // print source code

    while(sourceCode[i] != '\0')
    {
        std::cout << sourceCode[i];
        i++;
    }
    
    // Lexer lexer(sourceCode);
    // auto tokens = lexer.tokenize();
    // lexer.print_all_tokens(tokens);

    // Parser parser(tokens);
    // auto ast = parser.parse();

    // Compiler compiler;
    // compiler.compile(ast);

    return 0;
}

