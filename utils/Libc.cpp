#include "../Includes/Utils.hpp"

bool is_char(char c)
{
    if(c != ' ' && c != '\t' && c != '\n' && c != '\0' && c != '\r' && c != '\v' && c != '\f')
        return true;
    return false;
}

// it will trim the string and return the trimmed string
// '   hello   ' -> 'hello'

std::string ft_trim(std::string str)
{
    size_t i = 0;
    std::string res = "";

    while(i < str.length() && !is_char(str[i]))
        i++;

    while(i < str.length())
    {
        res += str[i];
        i++;
    }

    i = res.length() - 1;
    while(i > 0 && !is_char(res[i]))
    {
        res.pop_back();
        i--;
    }   

    return res;
}

bool is_digit(char c)
{
    if(c >= '0' && c <= '9')
        return true;
    return false;
}

long long ft_atoi(std::string str)
{
    size_t i = 0;
    long long res = 0;
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
        res = res * -1;
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
        {
            return false;
        }
        i++;
    }
    return true;
}
