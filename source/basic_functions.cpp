#include "basic_functions.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>  // std::find

bool IsOperator(std::string value)
{
    std::vector<std::string> operators = {
        "+",
        "-",
        "*",
        "/",
        "+=",
        "-=",
        "*=",
        "/=",
        "==",
        ">",
        ">=",
        "<",
        "<=",
        "||",
        "&&",
    };
    // if value in operators
    if (std::find(operators.begin(), operators.end(), value) != operators.end())
        return true;
    return false;
}

bool IsOperatorCharacter(char value)
{
    std::vector<char> characters = {
        '+',
        '-',
        '*',
        '/',
        '=',
        '>',
        '<',
        '|',
        '&',
    };
    // if value in characters
    if (std::find(characters.begin(), characters.end(), value) != characters.end())
        return true;
    return false;
}

int GetOperatorPriority(std::string value)
{
    if (value == "*" || value == "/")
        return 1;
    else if (value == "+" || value == "-")
        return 2;
    else if (value == "=")
        return 3;
    
    return 1;
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
