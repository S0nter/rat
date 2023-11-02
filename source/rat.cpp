#include <string>
#include <vector>
#include "basic_functions.h"
using namespace std;

enum Type
{
    _none,
    _keyword,
    _number,
    _operator
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
    else if (value == ";")
        token.type = Type::_keyword;
    else if (IsNumber(value))
        token.type = Type::_number;
    return token;
}

vector<Token> Tokenize(string text)
{
    vector<Token> tokens;

    int id = 0;
    char character = text.at(id);
    string buffer;
    while (true)
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
        else
        {
            tokens.push_back(AddToken(buffer));
            buffer.clear();
        }

        //check if id is out of range
        if (++id < text.size())
            character = text.at(id);
        else
            break;
    }

    for (int i = 0; i < tokens.size(); i++) // visualise tokens
    {
        std::cout << i << ":\"" << tokens[i].value << "\""
                       << "|\"" << tokens[i].type  << "\"" << std::endl;
    }

    return tokens;
}

Token Parse(vector<Token> line)
{
    Token root;
    for (Token token : line)
    {
        if (token.type == Type::_keyword)
        {
            root = token;
        }
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
        if (token.type == Type::_keyword && token.value == "exit") // exit
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
    vector<Token> token_tree;
    vector<Token> lines = Tokenize(text);
    // for (vector<Token> line : lines)
    // {
        // token_tree = Parse(lines); // FIXME
    // }
    string output = Convert(token_tree);
    return output;
}
