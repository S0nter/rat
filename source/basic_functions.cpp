#include "basic_functions.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>  // std::find


bool IsOperator(std::string value)
{
    if (value == "+" ||
        value == "-" ||
        value == "*" ||
        value == "/")
        return true;
    return false;
}

bool IsComparator(std::string value)
{
    std::vector<std::string> comparators = {
        "==",
        ">=",
        "<=",
        ">",
        "<",
        "||",
        "&&",
        "or",
        "and",
    };
    // if value in comparators
    if (std::find(comparators.begin(), comparators.end(), value) != comparators.end())
        return true;
    return false;
}

bool IsNumber(std::string value)
{
    bool result = false;
    for (char character : value)
    {
        if (!isdigit(character))
            return false;
        else
            result = true;
    }
    return result;
}

std::string Red(std::string text)
{
    return "\33[1;91m" + text + "\33[0m";
}

std::string Green(std::string text)
{
    return "\033[1m\033[32m" + text + "\033[0m";
}

std::string Quote(std::string str)
{
    return "\"" + str + "\"";
}

void Error(std::string text)
{
    std::cout << Red("Error: ") << text << std::endl;
    exit(1);
}
