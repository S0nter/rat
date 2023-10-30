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
    string value = 0;
    Token(Type t, int v)
    {
        type = t;
        value = v;
    }
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
    int id = 0;
    char character = text.at(id);
    string buffer;
    while (id < text.size())
    {
        if (std::isalpha(character))
        {
            do
            {
                buffer.push_back(character);
                character = text.at(++id); 
            } while (std::isalnum(character));
            line.push_back(AddToken(buffer));
            buffer.clear();
        }
        if (std::isdigit(character))
        {
            do
            {
                buffer.push_back(character);
                character = text.at(++id); 
            } while (std::isdigit(character));
            line.push_back(Token(Type::_number, stoi(buffer)));
            buffer.clear();
        }
        if (character == '\n' || character == ';')
        {
            lines.push_back(line);
            line.clear();
        }
        character = text.at(++id);
    }
    // for (char character : text)
    // {
    //     if (character == ' ' && !buffer.empty())
    //     {
    //         line.push_back(AddToken(buffer));
    //         buffer.clear();
    //         continue;
    //     }
    //     if (character == '\n' || character == ';')
    //     {
    //         lines.push_back(line);
    //         line.clear();
    //     }
    // }
    return lines;
}

Tree Parse(vector<Token> line)
{
    Token root;
    for (Token token : line)
    {
        if (token.Type type = Type::_exit)
        {
            root = token;

        }
        // exit 6 * 2
        
        //     to

        //    exit
        //    /  \
        //        *
        //       / \ 
        //      6   2
    }
    return root;
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
