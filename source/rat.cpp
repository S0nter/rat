#include <string>
#include <iostream> // DEBUG
#include <vector>

#include "basic_functions.h"
#include "rat.h"

using namespace std;


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
        if (!buffer.empty())
        {
            if (isalnum(character) && isalpha(buffer.at(0)))
            {
                buffer.push_back(character);
                continue;
            }
            if (isdigit(character) && isdigit(buffer.at(0)))
            {
                buffer.push_back(character);
                continue;
            }
            else if (IsOperatorCharacter(character) && IsOperatorCharacter(buffer.at(0)))
            {
                buffer.push_back(character);
                continue;
            }
            else
            {
                tokens.push_back(AddToken(buffer));
                buffer.clear();
                if (character != ' ')
                    buffer.push_back(character);
            }
        }
        else if (character != ' ')
            buffer.push_back(character);
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
                output += "mov rax, rbx\n";
            }
            else if (token->left->type == Type::_number)
            {
                output += "mov rbx, " + token->left->value + "\n";
            }
            
            if (token->right->type == Type::_operator)
            {
                output += Convert(token->right);
            }
            else if (token->right->type == Type::_number)
            {
                output += "mov rax, " + token->left->value + "\n";
            }
        }
        else
            Error("invalid operator syntax");

        if (token->value == "+")
        {
            output += "add rbx, rax\n";
        }
        if (token->value == "-")
        {
            output += "sub rbx, rax\n";
        }
        if (token->value == "*")
        {
            output += "imul rbx, rax\n";
        }
    }
    return output;
}

void PrintTree(const std::string& prefix, const Token* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << "|__";

        // print the value of the node
        std::cout << "[" << node->value << "]" << std::endl;

        // enter the next tree level - left and right branch
        PrintTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
        PrintTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

string Compile(string text)
{
// TOKENIZE
    cout << endl << Green("Tokenizer:") << endl;

    vector<Token> tokens = Tokenize(text); // get all tokens
    vector<vector<Token>> lines = Divide(tokens); // divide them on lines

    // debug
    for (vector<Token> line : lines)
    {
        for (Token token : line)
            cout << "[" << token.value << "]";
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