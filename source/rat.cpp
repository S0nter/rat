#include <iostream> // DEBUG
#include <string>
#include <vector>
#include <algorithm>

#include "functions.h"
#include "rat.h"

using namespace std;

bool IsOperator(std::string value)
{
    std::vector<std::string> operators = {
        "+",
        "-",
        "*",
        "/",
        "+=",
        "-=",
        "*=",
        "/=",
        "==",
        ">",
        ">=",
        "<",
        "<=",
        "||",
        "&&",
    };
    // if value in operators
    if (std::find(operators.begin(), operators.end(), value) != operators.end())
        return true;
    return false;
}

bool IsOperatorCharacter(char value)
{
    std::vector<char> characters = {
        '+',
        '-',
        '*',
        '/',
        '=',
        '>',
        '<',
        '|',
        '&',
    };
    // if value in characters
    if (std::find(characters.begin(), characters.end(), value) != characters.end())
        return true;
    return false;
}

int GetOperatorPriority(std::string value)
{
    if (value == "*" || value == "/")
        return 1;
    else if (value == "+" || value == "-")
        return 2;
    else if (value == "=")
        return 3;
    
    return 1;
}

bool IsNumber(std::string value)
{
    if (value.length() == 0)
        return false;
    for (char character : value)
    {
        if (!isdigit(character))
            return false;
    }
    return true;
}

Token AddToken(string value)
{
    Token token;
    token.value = value;

    if (IsOperator(value))
    {
        token.type = Type::_operator;
        token.priority = GetOperatorPriority(value);
    }
    else if (value == "exit")
    {
        token.type = Type::_keyword;
        token.priority = 4;
    }
    else if (IsNumber(value))
    {
        token.type = Type::_number;
        token.priority = 0;
    }
    return token;
}

vector<vector<Token>> Tokenize(string text)
{
    vector<vector<Token>> lines;
    vector<Token> tokens;
    string buffer;

    for (char character : text)
    {
        if (!buffer.empty())
        {
            if ((isalnum(character) && isalpha(buffer.at(0))) || // keyword
                (isdigit(character) && isdigit(buffer.at(0))) || // number
                (IsOperatorCharacter(character) && IsOperatorCharacter(buffer.at(0)))) // operator
            {
                buffer.push_back(character);
                continue;
            }
            else
            {
                tokens.push_back(AddToken(buffer));
                buffer.clear();
            }
        }
        if (character == '\n' || character == ';')
        {
            if (!tokens.empty())
                lines.push_back(tokens);
            tokens.clear();
        }
        else if (character != ' ')
            buffer.push_back(character);
    }
    if (!buffer.empty()) // add last token
        tokens.push_back(AddToken(buffer));

    return lines;
}

Token *Parse(vector<Token> *tokens, int from, int to) // converts line to token tree
{
    Token *token = &tokens->at(from);
    int index = from;

    for (int i = from; i < to; i++) // iterate through every token from from to to
    {
        if (tokens->at(i).priority > token->priority)
        {
            token = &tokens->at(i);
            index = i;
        }
    }

    if (index > from)
        token->left = Parse(tokens, from, index - 1); // find highest token from left
    else
        token->left = nullptr; // no tokens from left
    
    if (index < to)
        token->right = Parse(tokens, index + 1, to); // find highest token from right
    else
        token->right = nullptr; // no tokens from right
    
    return token;
}

string Convert(Token* token)
{
    string output;
    
    if (token->type == Type::_operator)
    {   
        if (token->left != nullptr && token->right != nullptr)
        {
            if (token->left->type == Type::_operator)
            {
                output += Convert(token->left);
                // output += "mov rax, rbx\n";
            }
            else if (token->left->type == Type::_number)
                output += "mov rax, " + token->left->value + "\n";
            
            if (token->right->type == Type::_operator)
                output += Convert(token->right);
            else if (token->right->type == Type::_number)
                output += "mov rbx, " + token->right->value + "\n";
        }
        else
            Error("invalid operator syntax");

        if (token->value == "+")
        {
            output += "add rax, rbx\n";
        }
        if (token->value == "-")
        {
            output += "sub rax, rbx\n";
        }
        if (token->value == "*")
        {
            output += "imul rax, rbx\n";
        }
    }
    return output;
}

void PrintTree(const std::string& prefix, const Token* node, bool isLeft)
{
    if (node != nullptr )
    {
        std::cout << prefix;

        std::cout << "|--";

        // print the value of the node
        std::cout << "[" << node->value << "]" << std::endl;

        // enter the next tree level - left and right branch
        PrintTree( prefix + (isLeft ? "|   " : "    "), node->left, true);
        PrintTree( prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

string Compile(string text)
{
// TOKENIZE
    cout << endl << Green("Tokenizer:") << endl;

    vector<vector<Token>> lines = Tokenize(text); // get tokens

    // debug
    for (vector<Token> line : lines)
    {
        for (Token token : line)
            cout << "[" << token.value << "]" << " ";
        cout << endl;
    }
    cout << endl;

// PARSE
    cout << Green("Parser:") << endl;

    vector<Token> trees;
    for (size_t i = 0; i < lines.size(); i++)
        trees.push_back(*Parse(&lines.at(i), 0, lines.at(i).size() - 1)); // convert each line to tree
    
    // debug
    for (Token token : trees)
    {
        PrintTree("", &token, false);
        cout << endl;
    }

// CONVERT
    cout << Green("Converter:") << endl;
    
    string output;
    
    for (Token token : trees)
        output += Convert(&token); // convert to assembly code

    // debug
    cout << output << endl;
    
    return output;
}