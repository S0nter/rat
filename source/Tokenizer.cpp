#include <string>
#include <vector>
//#include <./rat.h>
#include "Tokenizer.h"
using namespace std;

bool IsOperator(string value)
{
    if (value == "+" ||
        value == "-" ||
        value == "*" ||
        value == "/")
        return true;
    return false;
}

bool IsNumber(string value)
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

Token AddToken(string value)
{
    Token token;
    token.value = value;

    if (IsOperator(value))
    {
        token.type = Type::_operator;
        token.priority = 2;
    }
    else if (value == "exit")
    {
        token.type = Type::_keyword;
        token.priority = 3;
    }
    else if (value == ";" || value == "\n")
    {
        token.type = Type::_linebreak;
    }
    else if (IsNumber(value))
    {
        token.type = Type::_number;
        token.priority = 1;
    }
    return token;
}

vector<Token> Tokenize(string text)
{
    vector<Token> tokens;
    string buffer;
    for (char character : text)
    {
        if (std::isalnum(character)) // check weather character is alpha-numeric (a, b, c, d... or 1, 2, 3, 4...)
        {
            buffer.push_back(character);
            continue;
        }
        else if (!buffer.empty()) // convert buffer
        {
            tokens.push_back(AddToken(buffer));
            buffer.clear();
        }
        if (character != ' ')
        {
            buffer.push_back(character);
            tokens.push_back(AddToken(buffer));
            buffer.clear();
        }
    }
    if (!buffer.empty()) // add last token
    {
        tokens.push_back(AddToken(buffer));
        buffer.clear();
    }
    return tokens;
}

vector<vector<Token>> Divide(vector<Token> tokens) // divides vector of tokens on lines by linebreaks
{
    vector<vector<Token>> lines;
    vector<Token> line;
    for (Token token : tokens)
    {
        if (token.type == Type::_linebreak)
        {
            if (!line.empty()) // add line
            {
                lines.push_back(line);
                line.clear();
            }
        }
        else
            line.push_back(token); // append to line
    }
    if (!line.empty()) // add last line if not empty
    {
        lines.push_back(line);
        line.clear();
    }
    return lines;
}