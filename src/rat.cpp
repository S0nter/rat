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

vector<Token> Tokenize(string text)
{
    vector<Token> tokens;
    string buffer;
    for (char character : text)
    {
        if (character == ' ' && !buffer.empty())
        {
            tokens.push_back(AddToken(buffer));
            buffer.clear();
            continue;
        }
        buffer.push_back(character);
    }
    return tokens;
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
            output += "mov rdi, 0\n";
            output += "syscall\n";
        }
    }
    return output;
}

string Compile(string text)
{
    vector<Token> tokens = Tokenize(text);
    string output = Convert(tokens);
    return output;
}
