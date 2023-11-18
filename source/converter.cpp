#include <string>
#include <vector>
#include <./rat.h>
#include <./Converter.h>
using namespace std;

string Convert(vector<Token> tokens)
{
    string output;
    output += "section .text\n";
    output += "global _start\n";
    output += "_start:\n";

    for (Token token : tokens)
    {
        if (token.type == Type::_keyword)
        {
            if (token.value == "exit" && token.right->type == Type::_number)
            {
                output += "mov rax, 60\n";
                output += "mov rdi, " + token.right->value + '\n';
                output += "syscall\n";
            }
        }
    }
    return output;
}