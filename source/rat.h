#pragma once
#include <string>
#include <vector>

enum Type
{
    _none,
    _keyword,
    _number,
    _operator,
    _linebreak,
};

struct Token
{
    Type type = Type::_none;
    std::string value = "";
    int priority = 0;
    struct Token *left = nullptr;
    struct Token *right = nullptr;
};

std::string Compile(std::string text); // converts rat file to assmebly code