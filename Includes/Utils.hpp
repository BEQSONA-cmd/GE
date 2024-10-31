#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include "Parser.hpp"

class Object;

void ft_error(std::string line, int errnum);
std::vector<std::string> ft_split(const std::string &a, char c);
bool is_char(char c);
bool is_digit(char c);
long long ft_atoi(std::string str);
bool ft_strcmp(std::string str1, std::string str2);
std::string ft_trim_func(std::string str);
void free_hash_map(std::map<std::string, Object>& objects);

#endif