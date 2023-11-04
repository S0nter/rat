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
    struct Token* left;
    struct Token* right;
};

Token AddToken(string value)
{
    Token token;
    token.value = value;

    if (IsOperator(value))
        token.type = Type::_operator;
    else if (value == "exit")
        token.type = Type::_keyword;
    else if (value == ";" || value == "\n")
        token.type = Type::_linebreak;
    else if (IsNumber(value))
        token.type = Type::_number;
    return token;
}

vector<Token> Tokenize(string text)
{
    vector<Token> tokens;

    int id = 0;
    char character;
    string buffer;
    while (id < int(text.size()))
    {
        character = text.at(id);
        if (std::isalpha(character))
        {
            while (std::isalnum(character))
            {
                buffer.push_back(character);
                if (id + 1 < int(text.size()))
                    character = text.at(++id);
                else
                    break;
            }
            // else if (character != ' ') // FIXME: doesn't exist in c++
            //     tokens.push_back(AddToken(character));

            tokens.push_back(AddToken(buffer));
            buffer.clear();
        }
        else if (character != ' ')
            tokens.push_back(AddToken(std::string(1, character)));
        id++;
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

Token Parse(vector<Token> line)
{
    Token root;
    for (Token token : line)
    {
        if (token.type == Type::_keyword)
            root = token;
    }
    return root;
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
        trees.push_back(Parse(lines));
    
    string output = Convert(trees);
    return output;
}
