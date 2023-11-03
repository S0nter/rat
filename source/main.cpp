#include <iostream>
#include <fstream>
#include <cstring>
#include <docopt.h>

#include "rat.cpp"
#include "basic_functions.h"
#include "test.h"

static const char USAGE[] =
R"(

    Usage:
      rat (-h | --help)
      rat --version
      rat FILE FILE
      rat --test


    Options:
      -h --help  Show this screen.
      --version  Show version.
      --test     Run tests
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
    std::map<std::string, docopt::value> args
    = docopt::docopt(USAGE,
                     { argv + 1, argv + argc },
                     true,               // show help if requested
                     "We don't know what we're doing");  // version string
    for(auto const& arg : args) {
        std::cout << arg.first << "|" <<  arg.second << std::endl;
        if (string (arg.first) == "--test" && arg.second) return test();
    }
    std::cout << "Opening " << argv[1] << std::endl;
    string content = ReadFile(argv[1]);

    string output = Compile(content);
    WriteFile(argv[2], output);
    return 0;
}
