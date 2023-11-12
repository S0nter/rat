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

Token AddToken(std::string value); // converts string to a single Token

std::vector<Token> Tokenize(std::string text); // converts text to list of tokens

std::vector<std::vector<Token>> Divide(std::vector<Token> tokens); // divides vector of tokens on lines by linebreaks

Token *Parse(std::vector<Token> *tokens, int from, int to); // converts line to list of token trees

std::string Convert(std::vector<Token*> tokens); // converts list of token trees to assmebly code

std::string Compile(std::string text); // converts rat file to assmebly code
