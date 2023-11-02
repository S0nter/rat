#include "basic_functions.h"

#include <string>
#include <iostream>


bool isMathOperator(char character)
{
    if (
        character == '+' ||
        character == '-' ||
        character == '*' ||
        character == '/') {
        std::cout << character << "math operator" << std::endl;

        return true;

        }
    std::cout << character << "not math operator" << std::endl;
    return false;
}

std::string Red(std::string text)
{
    return "\33[1;91m" + text + "\33[0m";
}

std::string Green(std::string text)
{
    return "\033[1m\033[32m" + text + "\033[0m";
}
