#include <string>
#include <iostream> // DEBUG
#include <vector>
#include "basic_functions.h"
#include "rat.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "Converter.h"
using namespace std;

string Compile(string text)
{
// TOKENIZE
    vector<Token> tokens = Tokenize(text); // get all tokens
    vector<vector<Token>> lines = Divide(tokens); // divide them on lines

    // debug
    cout << endl << Green("Tokenizer:") << endl;
    for (vector<Token> line : lines)
    {
        for (Token token : line)
            cout << "[" << token.value << "]";
        cout << endl;
    }
    cout << endl;

// PARSE
    vector<Token> trees;
    for (size_t i = 0; i < lines.size(); i++)
        trees.push_back(*Parse(&lines.at(i), 0, lines.at(i).size() - 1)); // convert each line to tree
    
    // debug
    cout << Green("Parser:") << endl;
    for (Token token : trees)
    {
        PrintTree("", &token, false);
        cout << endl;
    }

// CONVERT
    string output = Convert(trees); // convert to assembly code

    // debug
    cout << Green("Converter:") << endl;
    cout << output << endl;
    
    return output;
}