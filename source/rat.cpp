#include <string>
#include <vector>

using namespace std;

enum Type
{
    _none,
    _number,
    _exit,
};

struct Token
{
    Type type = Type::_none;
    int value = 0;
    struct Token* left;
    struct Token* right;
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

Tree Parse(vector<Token> line)
{
    for (Token token : line)
    {
        // exit 6 * 2
        
        //     to

        //    exit
        //    /  \
        //        *
        //       / \ 
        //      6   2
    }
}

string Convert(vector<Token> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";

    for (Token token : tokens)
    {
        if (token.type == Type::_exit)
        {
            output += "mov rax, 60\n";
            output += "mov rdi, " + token.right.value + '\n';
            output += "syscall\n";
        }
    }
    return output;
}

string Compile(string text)
{
    vector<vector<Token>> lines = Tokenize(text);
    vector<Token> tokens;
    for (vector<Token> line : lines)
    {
        tokens.push_back(Parse(line));
    }
    string output = Convert(tokens);
    return output;
}
