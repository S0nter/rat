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
    _end_of_line
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
        token.type = Type::_end_of_line;
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
    while (id + 1 < text.size())
    {
        character = text.at(++id);
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
    }

    for (int i = 0; i < tokens.size(); i++) // visualise tokens
    {
        std::cout << i << ":\"" << tokens[i].value << "\""
                       << "|\"" << tokens[i].type  << "\"" << std::endl;
    }

    return tokens;
}

vector<vector<Token>> Divide(vector<Token> tokens)
{
    ; // FIXME
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
    vector<Token> tokens = Tokenize(text);
    vector<vector<Token>> lines = Divide(tokens);

    vector<Token> trees;
    for (vector<Token> lines : lines)
        trees.push_back(Parse(lines));
    
    string output = Convert(trees);
    return output;
}
