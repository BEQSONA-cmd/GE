#include "../Includes/Utils.hpp"

bool is_char(char c)
{
    if(c != ' ' && c != '\t' && c != '\n' && c != '\0' && c != '\r' && c != '\v' && c != '\f')
        return true;
    return false;
}

bool is_digit(char c)
{
    if(c >= '0' && c <= '9')
        return true;
    return false;
}

size_t ft_atoi(std::string str)
{
    size_t i = 0;
    size_t res = 0;
    bool is_negative = false;

    if (str[i] == '-')
    {
        is_negative = true;
        i++;
    }

    while (i < str.length())
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;

        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + str[i] - '0';
        i++;
    }

    if (is_negative)
        return -res;
    return res;
}

std::vector<std::string> ft_split(const std::string &a, char c)
{
    std::vector<std::string> result;
    size_t i = 0;
    size_t j = 0;

    while (i < a.length())
    {
        while (i < a.length() && a[i] == c)
            i++;
        if (i < a.length())
            j++;
        while (i < a.length() && a[i] != c)
            i++;
    }

    i = 0;
    while (i < a.length())
    {
        while (i < a.length() && a[i] == c)
            i++;
        j = i;
        while (i < a.length() && a[i] != c)
            i++;
        if (i > j)
        {
            result.push_back(a.substr(j, i - j));
        }
    }

    return result;
}

bool ft_strcmp(std::string str1, std::string str2)
{
    size_t i = 0;

    if(str1.length() != str2.length())
        return false;

    while(i < str1.length())
    {
        if(str1[i] != str2[i])
            return false;
        i++;
    }
    return true;
}
