#include <string>
#include <vector>

#include "basic_functions.h"

using namespace std;

enum Type
{
    _none,
    _number,
    _operator,
    _end,
    _exit,
};

struct TokenTree
{
    Type type = Type::_none;
    string value;
    struct Token* left;
    struct Token* right;
};

struct Token
{
    Type type = Type::_none;
    string value;
};

Token AddToken(string value, Type type = Type::_none)
{
    Token token;
    token.type = type;
    token.value = value;
    if (value == "exit") // keyword handling
    {
        token.type = Type::_exit;
    }
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
        if (std::isalpha(character))
        {
            std::cout << character << " isalpha" << std::endl;
            do
            {
                std::cout << character << " isalnum" << std::endl;
                buffer.push_back(character);
                if (++id < text.size())
                    character = text.at(id);
            }
            while (std::isalnum(character));

            std::cout << "Adding buffer: " << buffer << std::endl;

            tokens.push_back(AddToken(buffer)); // adding string token
            buffer.clear();
        }
        else if (std::isdigit(character))
        {
            std::cout << character << " isdigit" << std::endl;
            do
            {
                buffer.push_back(character);
                if (++id < text.size())
                    character = text.at(id);
            }
            while (std::isdigit(character));

            std::cout << "endNumberValue: " << buffer << std::endl;

            tokens.push_back(AddToken(buffer, Type::_number));
            buffer.clear();
        }
        else if (isMathOperator(character))
        {
            std::cout << character << " isarithmetic" << std::endl;

            buffer.push_back(character);
            tokens.push_back(AddToken(buffer, Type::_operator));
            buffer.clear();
        }
        else if (character == '\n' || character == ';')
        {
            tokens.push_back(AddToken("", Type::_end));
        }
        
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
        if (token.type == Type::_exit)
        {
            root = token;
        }
    }
    return root;
}

string Convert(vector<TokenTree> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";

    for (TokenTree token : tokens)
    {
        if (token.type == Type::_exit)
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
    vector<TokenTree> token_tree;
    vector<Token> lines = Tokenize(text);
    // for (vector<Token> line : lines)
    // {
        // token_tree = Parse(lines); // FIXME
    // }
    string output = Convert(token_tree);
    return output;
}
