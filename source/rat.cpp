#include <string>
#include <vector>
#include "basic_functions.h"

using namespace std;

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
    string value;
    int priority;
    struct Token* left;
    struct Token* right;
};

Token AddToken(string value)
{
    Token token;
    token.value = value;

    if (IsOperator(value))
    {
        token.type = Type::_operator;
        token.priority = 1;
    }
    else if (value == "exit")
    {
        token.type = Type::_keyword;
        token.priority = 2;
    }
    else if (value == ";" || value == "\n")
    {
        token.type = Type::_linebreak;
    }
    else if (IsNumber(value))
    {
        token.type = Type::_number;
        token.priority = 0;
    }
    return token;
}

vector<Token> Tokenize(string text)
{
    vector<Token> tokens;

    int id = 0;
    char character = text.at(id);
    string buffer;
    while (id < text.size())
    {
        if (std::isalnum(character))
        {
            do
            {
                buffer.push_back(character);
                character = text.at(++id);
            }
            while (std::isalnum(character) && id + 1 < text.size());

            tokens.push_back(AddToken(buffer));
            buffer.clear();
        }
        else if (character != ' ')
        {
            buffer.push_back(character);
            tokens.push_back(AddToken(buffer));
            buffer.clear();
        }
        if (++id + 1 < text.size())
            character = text.at(id);
    }

    return tokens;
}

vector<vector<Token>> Divide(vector<Token> tokens)
{
    vector<vector<Token>> lines;
    vector<Token> line;
    for (Token token : tokens)
    {
        if (token.type == Type::_linebreak)
        {
            if (!line.empty())
            {
                lines.push_back(line);
                line.clear();
            }
        }
        else
            line.push_back(token); // add something to line
    }
    if (!line.empty()) // recheck again if something was on line
    {
        lines.push_back(line);
        line.clear();
    }
    return lines;
}

Token Parse(vector<Token> tokens, int from, int to)
{
    Token token = tokens.at(from);
    int last;
    for (int id = from; id < to; id++)
    {
        if (tokens.at(id).priotity > token.priority)
        {
            token = token.at(id);
            last = id;
        }
    }
    token.left = Parse(tokens, 0, last);
    token.right = Parse(tokens, last, tokens.size());
    return token;
}

string Convert(vector<Token> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";

    for (Token token : tokens)
    {
        if (token.type == Type::_keyword && token.value == "exit")
        {
            output += "mov rax, 60\n";
            output += "mov rdi, " + token.right->value + '\n';
            output += "syscall\n";
        }
    }
    return output;
}

string Compile(string text)
{
    vector<Token> tokens = Tokenize(text);
    vector<vector<Token>> lines = Divide(tokens);

    vector<Token> trees;
    for (vector<Token> lines : lines)
        trees.push_back(Parse(line, 0, line.size());
    
    string output = Convert(trees);
    return output;
}
