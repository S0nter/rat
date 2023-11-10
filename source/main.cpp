#include <iostream>
#include <fstream>
#include <cstring>
#include "docopt/docopt.h"

#include "rat.cpp"
#include "basic_functions.h"
#include "test.h"

static const char USAGE[] =
R"(

    Usage:  rat [FILE -o FILE | [-h | --help] | [--version] | [--tests | --test NUM]]
      
      rat FILE -o FILE
      rat --tests
      rat --test NUM
      rat -h | --help
      rat --version



    Options:
      -h --help   Show this screen
      --version   Show version
      --tests     Run all tests, same as --test -1
      --test NUM  Run test NUM
      FILE        Input file
      -o FILE     Output file
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
    std::string input_file = "";
    std::string output_file = "";
    
    // parser for command line arguments
    std::map<std::string, docopt::value> args
    = docopt::docopt(USAGE,
                     { argv + 1, argv + argc },
                     true,      // show help if requested
                     "0.0.1");  // version string
    
    for(auto const& arg : args) {
        if (string (arg.first) == "--tests" && arg.second.asBool()) return test(-1);
        else if (string (arg.first) == "--test" && arg.second.isString()) return test(stoi(arg.second.asString()));
        else if (string (arg.first) == "FILE" && arg.second.isString()) input_file = arg.second.asString();
        else if (string (arg.first) == "-o" && arg.second.isString()) output_file = arg.second.asString();
    }

    std::cout << "Opening " << input_file << std::endl;
    string content = ReadFile(input_file);

    string output = Compile(content);
    WriteFile(output_file, output);
    return 0;
}
