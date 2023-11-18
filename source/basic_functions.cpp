#include "basic_functions.h"
#include <string>

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
