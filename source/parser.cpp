#include <string>
#include <vector>
#include <iostream>
//#include <./rat.h>
#include <./Parser.h>
using namespace std;

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

void PrintTree(const string& prefix, const Token* node, bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;
        cout << "|__";
        // print the value of the node
        cout << "[" << node->value << "]" << endl;
        // enter the next tree level - left and right branch
        PrintTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
        PrintTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}