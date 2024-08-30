#include "../Includes/Lexer.h"


// if there is source string is like this   " hello my world hello"
// and string is "my" , it will return "world"
// so its looking for the next string after the given string untill it finds a space
std::string next_string(std::string source, std::string string)
{
    std::string result;

    int i = 0;
    while(source[i] != '\0')
    {
        if(source.substr(i, string.length()) == string)
        {
            i += string.length();
            while(source[i] == ' ' || source[i] == '\n' || source[i] == '\t' || source[i] == '\r')
                i++;
            while( source[i] != '\n' && source[i] != '\r' && source[i] != '\0')
            {
                result += source[i];
                i++;
            }
            break;
        }
        i++;
    }
    return result;
}

std::string previous_string(std::string source, std::string string)
{
    std::string result;

    int i = 0;
    while(source[i] != '\0')
    {
        if(source.substr(i, string.length()) == string)
        {
            std::cout << source[i] << std::endl;
            i -= string.length();
            while(source[i] == ' ' || source[i] == '\t')
                i--;
            while( source[i] != ' ' && source[i] != '\t' && source[i] != '\n' && source[i] != '\r' && source[i] != '\0')
            {
                result = source[i] + result;
                i--;
            }
            break;
        }
        i++;
    }
    return result;
}


Lexer::Lexer(std::string& source)
{
    sourceCode = source;
    iter = 0;
}

char Lexer::currentChar() 
{
    if (iter >= sourceCode.length()) 
        return '\0';
    return sourceCode[iter];
}

Token Lexer::makeToken(TokenType type, const std::string& value) 
{
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

// რიცხვი ი = 15

// ფრაზა გამარჯობა = "გამარჯობა სამყარო 1"

// ბეჭდვა("გამარჯობა სამყარო 2\n")

// IDENTIFIER : ი , გამარჯობა
// PRINT : ბეჭდვა
// STRING : გამარჯობა სამყარო 1, გამარჯობა სამყარო 2\n
// LEFT_PAREN : (
// RIGHT_PAREN : )
// QUOTE : " , '
// EQUAL : =
// EOF_TOKEN : \0
// VALUE : 15 , გამარჯობა სამყარო 1

std::vector<Token> Lexer::tokenize() 
{
    std::vector<Token> tokens;
    
    while (currentChar() != '\0') 
    {
        if (currentChar() == '(') 
        {
            tokens.push_back(makeToken(TokenType::LEFT_PAREN, "("));
            iter++;
        }
        else if (currentChar() == ')') 
        {
            tokens.push_back(makeToken(TokenType::RIGHT_PAREN, ")"));
            iter++;
        }
        else if (currentChar() == '"') 
        {
            iter++; 
            std::string strValue;
            while (currentChar() != '"' && currentChar() != '\0') 
            {
                strValue += currentChar();
                iter++;
            }
            tokens.push_back(makeToken(TokenType::STRING, strValue));
            iter++;
        } 
        else if (sourceCode.substr(iter, std::string(KEYWORD_PRINT).length()) == KEYWORD_PRINT) 
        {
            tokens.push_back(makeToken(TokenType::PRINT, KEYWORD_PRINT));
            iter += std::string(KEYWORD_PRINT).length();
        }
        else if (sourceCode.substr(iter, std::string(KEYWORD_PHRASE).length()) == KEYWORD_PHRASE) 
        {
            tokens.push_back(makeToken(TokenType::PHRASE, KEYWORD_PHRASE));
            iter += std::string(KEYWORD_PHRASE).length();
        }
        else if (sourceCode.substr(iter, std::string(KEYWORD_NUMBER).length()) == KEYWORD_NUMBER) 
        {
            tokens.push_back(makeToken(TokenType::NUMBER, KEYWORD_NUMBER));
            iter += std::string(KEYWORD_NUMBER).length();
        }
        else if (currentChar() == '=') 
        {
            tokens.push_back(makeToken(TokenType::EQUAL, "="));
            std::string identifier = previous_string(sourceCode, "=");
            std::string value = next_string(sourceCode, "=");

            tokens.push_back(makeToken(TokenType::IDENTIFIER, identifier));
            tokens.push_back(makeToken(TokenType::VALUE, value));
            iter++;
            iter += identifier.length();
            
        }
        else if (currentChar() == ' ' || currentChar() == '\n' || currentChar() == '\t' || currentChar() == '\r')
            iter++;
        else 
        {
            std::string unknownValue;
            unknownValue += currentChar();
            tokens.push_back(makeToken(TokenType::UNKNOWN, unknownValue));
            iter++;
        }
    }
    
    tokens.push_back(makeToken(TokenType::EOF_TOKEN, ""));
    return tokens;
}

void Lexer::print_all_tokens(std::vector<Token>& tokens) 
{
    int i = 0;
    while(tokens[i].type != TokenType::EOF_TOKEN)
    {
        if(tokens[i].type == TokenType::UNKNOWN)
            std::cout << "UNKNOWN: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::PRINT)
            std::cout << "PRINT: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::STRING)
            std::cout << "STRING: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::LEFT_PAREN)
            std::cout << "LEFT_PAREN: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::RIGHT_PAREN)
            std::cout << "RIGHT_PAREN: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::NUMBER)
            std::cout << "NUMBER: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::PHRASE)
            std::cout << "PHRASE: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::EQUAL)
            std::cout << "EQUAL: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::IDENTIFIER)
            std::cout << "IDENTIFIER: " << tokens[i].value << std::endl;
        else if(tokens[i].type == TokenType::VALUE)
            std::cout << "VALUE: " << tokens[i].value << std::endl;
        i++;
    }
    std::cout << "EOF" << std::endl;
}
