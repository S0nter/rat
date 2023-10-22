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
    vector<vector<Token>> tokens;
    int line = 0;
    string buffer;
    for (char character : text)
    {
        if (character == ' ' && !buffer.empty())
        {
            tokens[line].push_back(AddToken(buffer));
            buffer.clear();
            continue;
        }
        if (character == '\n' || character == ';')
        {
            line++;
            continue;
        }
        buffer.push_back(character);
    }
    return tokens;
}

void Parse(vector<vector<Token>> tokens)
{
    for (vector<Token> line : tokens)
    {
        // do smth
    }
}

string Convert(vector<vector<Token>> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";
    for (vector<Token> line : tokens)
    {
        for (Token token : line)
        {
            if (token.type == Type::_exit)
            {
                output += "mov rax, 60\n";
                output += "mov rdi, 0\n";
                output += "syscall\n";
            }
        }
    }
    return output;
}

string Compile(string text)
{
    vector<vector<Token>> tokens = Tokenize(text);
    Parse(tokens);
    string output = Convert(tokens);
    return output;
}
