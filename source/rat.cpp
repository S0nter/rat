#include <string>
#include <iostream> // DEBUG
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
    string value = "";
    int priority = 0;
    struct Token *left;
    struct Token *right;
};

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
    /// debug
    cout << "Tokenize:" << endl;
    for (Token token : tokens)
        cout << "[" << token.type << ": " << token.value << "]" << endl;
    cout << endl << endl;
    ///
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

Token *Parse(vector<Token> tokens, int from, int to) // converts line to token tree
{
    Token *token = &tokens.at(from);
    int index = 0;
    for (int i = from; i < to; i++) // iterate through every token from from to to
    {
        if (tokens.at(i).priority > token->priority)
        {
            token = &tokens.at(i);
            index = i;
        }
    }
    if (index > from)
    {
        /// debug
        cout << "\t";
        ///
        token->left = Parse(tokens, from, index - 1); // find highest token from left
    }
    else
        token->left = nullptr;
    if (index < to)
    {
        ///
        cout << "\t";
        ///
        token->right = Parse(tokens, index + 1, to); // find highest token from right
    }
    else
        token->right = nullptr;
    /// debug
    cout << "[" << token->type << ": " << token->value << "]" << endl;
    ///
    return token;
}

string Convert(vector<Token*> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";

    for (Token *token : tokens)
    {
        if (token->type == Type::_keyword && token->value == "exit")
        {
            output += "mov rax, 60\n";
            output += "mov rdi, " + token->right->value + '\n';
            output += "syscall\n";
        }
    }
    return output;
}

string Compile(string text)
{
    vector<Token> tokens = Tokenize(text); // get all tokens
    vector<vector<Token>> lines = Divide(tokens); // divide them on lines

    vector<Token*> trees;
    for (vector<Token> line : lines)
        trees.push_back(Parse(line, 0, line.size() - 1)); // convert each line to tree

    string output = Convert(trees); // convert to assembly code
    return output;
}
