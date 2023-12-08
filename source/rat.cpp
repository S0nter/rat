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
        token.priority = 2;
    }
    else if (IsOperator(value))
    {
        token.type = Type::_comparator;
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
        // // check weather character is alpha-numeric (a, b, c, d... or 1, 2, 3, 4...)
        // if (std::isalnum(character) && 
        //     // if buffer empty or (if it's not) last char is alpha-numeric
        //    (buffer.empty() || std::isalnum(buffer[buffer.length()-1])))
        // {
        //     buffer.push_back(character);
        //     continue;
        // }
        // else if (character == '|' || // check for &&, ||, ==, ... 
        //          character == '&' ||
        //          character == '=' ||
        //          character == '<' || 
        //          character == '>')
        // {
        //     // clear buffer in case like "5==" ("5" should be added before handling "==")
        //     if (!buffer.empty() && std::isalnum(buffer[buffer.length()-1]))
        //     {
        //         tokens.push_back(AddToken(buffer));
        //         buffer.clear();
        //     }
        //     buffer.push_back(character);
        //     continue;
        // }
        // else if (!buffer.empty()) // convert buffer
        // {
        //     tokens.push_back(AddToken(buffer));
        //     buffer.clear();
        // }

        if (!buffer.empty())
        {
            if (isalnum(character) && isalnum(buffer.at(0)))
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

string Convert(vector<Token> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n\n";
    output += "_start:\n";

    for (Token token : tokens)
    {
        if (token.type == Type::_keyword)
        {
            if (token.value == "exit")
            {
                Token *right = token.right;
                if (right == nullptr)
                    Error("exit needs an argument");
                else if (right->type == Type::_number)
                {
                    output += "    mov rdi, " + right->value + '\n';
                }
                else if (right->type == Type::_operator)
                {
                    if (right->value == "+")
                    {
                        if (right->left == nullptr || right->right == nullptr)
                            Error("invalid operator arguments");
                        output += "    mov rdi, " + right->left->value + '\n';
                        output += "    add rdi, " + right->right->value + '\n';
                    }
                    if (right->value == "-")
                    {
                        if (right->left == nullptr || right->right == nullptr)
                            Error("invalid operator arguments");
                        output += "    mov rdi, " + right->left->value + '\n';
                        output += "    sub rdi, " + right->right->value + '\n';
                    }
                    if (right->value == "*")
                    {
                        if (right->left == nullptr || right->right == nullptr)
                            Error("invalid operator arguments");
                        output += "    mov rdi, " + right->left->value + '\n';
                        output += "    imul rdi, " + right->right->value + '\n';
                    }
                }
                else
                    Error("exit needs an argument of type number");
                
                output += "    mov rax, 60\n";
                output += "    syscall\n";
            }
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
    
    string output = Convert(trees); // convert to assembly code

    // debug
    cout << output << endl;
    
    return output;
}