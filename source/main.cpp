#include <iostream>
#include <fstream>
#include <cstring>
#include "lib/docopt/docopt.h"

#include "rat.cpp"
#include "test.h"

static const char USAGE[] =
R"(
    Usage:
        rat IN -o OUT
        rat --run INP
        rat --testall
        rat --test ID
        rat --version
        rat -h|--help

    Options:
        --help -h   Show help screen
        --version   Show version
        --run INP   Compile input
        --testall   Run all tests
        --test ID   Run test ID
        IN          Input file (.rat)
        -o OUT      Output file (.asm)
)";

string ReadFile(string name)
{
    fstream file;
    file.open("./" + name, ios_base::in);
    if (!file.is_open())
    {
        std::cout << "Cannot open " << Quote(Red(name)) << std::endl;
        exit(1);
    }
    string content;
    string line;
    while (getline(file, line))
        content += line + '\n';
    file.close();
    return content;
}

void WriteFile(string name, string content)
{
    fstream file;
    file.open(name, ios_base::out);
    if (!file.is_open())
    {
        std::cout << "Cannot open " << Quote(Red(name)) << std::endl;
        exit(1);
    }
    file << content;
    file.close();
}

int main(int argc, char** argv)
{
    std::string inputFile = "";
    std::string outputFile = "";
    
    // parser for command line arguments
    std::map<std::string, docopt::value> args
    = docopt::docopt(USAGE, { argv + 1, argv + argc }, true, "0.0.1");
    
    for (auto const& arg : args)
    {
        if(string(arg.first) == "--test" && arg.second.isString())
            return Test(stoi(arg.second.asString()));
        else if (string(arg.first) == "--testall" && arg.second.asBool())
            return TestAll();
        else if (string(arg.first) == "--run" && arg.second.isString())
        {
            Compile(arg.second.asString());
            return 0;
        }
        else if (string(arg.first) == "IN" && arg.second.isString())
            inputFile = arg.second.asString();
        else if (string(arg.first) == "-o" && arg.second.isString())
            outputFile = arg.second.asString();
    }

    std::cout << "Opening " << inputFile << std::endl;
    string content = ReadFile(inputFile);

    string output = Compile(content);
    WriteFile(outputFile, output);
    return 0;
}
