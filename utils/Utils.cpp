#include "../Includes/Utils.hpp"

void ft_error(std::string line, int errnum, Parser *parser)
{
    if(errnum == 1)
        std::cout << "Error: qoute number error. There should be 2 qoutes in the line." << std::endl;
    else if(errnum == 2)
        std::cout << "Error: string converting error. String should be in qoutes." << std::endl;
    else if(errnum == 3)
        std::cout << "Error: int converting error. Int should not be in qoutes." << std::endl;
    else if(errnum == 4)
        std::cout << "Error: string should be first." << std::endl;
    else if(errnum == 5)
        std::cout << "Error: int should be first." << std::endl;
    else if(errnum == 6)
        std::cout << "Error: incorrect syntax." << std::endl;
    else if(errnum == 7)
        std::cout << "Error: no '=' found." << std::endl;
    std::cout << "Error at line: " << line << std::endl;
    delete parser;
    exit(1);
}
