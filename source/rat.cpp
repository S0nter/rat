#include <string>
#include <vector>

using namespace std;

enum Type
{
    _none,
    _exit,
    _number,
};

struct Token
{
    Type type = Type::_none;
    int value = 0;
};

Token AddToken(string buffer)
{
    Token token;
    if (buffer == "exit")
    {
        token.type = Type::_exit;
    }
    else
    {
        token.type = Type::_none;
    }
    return token;
}

vector<vector<Token>> Tokenize(string text)
{
    vector<vector<Token>> lines;
    vector<Token> line;
    string buffer;
    for (char character : text)
    {
        if (character == ' ' && !buffer.empty())
        {
            line.push_back(AddToken(buffer));
            buffer.clear();
            continue;
        }
        if (character == '\n' || character == ';')
        {
            lines.push_back(line);
            line.clear();
        }
    }
    return tokens;
}

string Parse(vector<Token> line)
{
    for (Token token : line)
    {
        // do smth
    }
}

string Convert(vector<string> trees)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";

    for (string tree : trees)
    {
        
    }
    // for (Token token : trees)
    // {
    //     if (token.type == Type::_exit)
    //     {
    //         output += "mov rax, 60\n";
    //         output += "mov rdi, 0\n";
    //         output += "syscall\n";
    //     }
    // }
    return output;
}

string Compile(string text)
{
    vector<vector<Token>> lines = Tokenize(text);
    vector<string> trees;
    for (vector<Token> line : lines)
    {
        trees.push_back(Parse(line));
    }
    string output = Convert(trees);
    return output;
}
