using namespace std;
#include <string>
#include <vector>

enum Type
{
    none,
    exit,
    number,
};

struct Token
{
    Type type = Type::none;
    int value = 0;
};

void Compile(string text)
{
    vector<Token> tokens = Tokenize(text);
    string output = Convert(tokens);
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
    }
    return tokens;
}

Token AddToken(string buffer)
{
    Token token;
    if (buffer == "exit")
    {
        token.type = Type::exit;
    }
    else
    {
        token.type = Type::none;
    }
    return token;
}

string Convert(vector<Token> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";
    for (Token token : tokens)
    {
        if (token.type == Type::exit)
        {
            output += "mov rax, 60\n";
            output += "mov rdi, 0\n";
            output += "syscall\n";
        }
    }
}