#include <iostream>
#include <fstream>
#include <cstring>
#include <docopt.h>

#include "rat.cpp"
#include "basic_functions.h"

// static const char USAGE[] =
// R"(rat [-hso FILE] [--quiet | --verbose] [INPUT ...]
//
// -h --help    show this
// -o FILE      specify output file [default: ./test.txt]
// --quiet      print less text
// --verbose    print more text
// )
//
//     Usage:
//
//       rat (-h | --help)
//       rat --version
//       rat [FILE]
//       rat [FILE] -o []
//       rat ship <name> move <x> <y> [--speed=<kn>]
//       rat ship shoot <x> <y>
//       rat mine (set|remove) <x> <y> [--moored | --drifting]
//
//     Options:
//       -h --help        Show this screen.
//       --version     Show version.
//       --test [NUM | list]    Run test NUM
// )";

bool test()
{
    if (
        IsMathOperator('*') &&
        IsMathOperator('/') &&
        IsMathOperator('+') &&
        IsMathOperator('-')) return true;
    return false;
}

string ReadFile(string name)
{
    fstream file;
    file.open("./" + name, ios_base::in);
    if (!file.is_open())
    {
        std::cout << "Cannot open " << "\"" << Red(name) << "\"" << std::endl;
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
        std::cout << "Cannot open " << "\"" << Red(name) << "\"" << std::endl;
        exit(1);
    }
    file << content;
    file.close();
}

int main(int argc, char** argv)
{
    // std::map<std::string, docopt::value> args
    // = docopt::docopt(USAGE,
    //                  { argv + 1, argv + argc },
    //                  true,               // show help if requested
    //                  "We don't know what we're doing");  // version string
    if (string (argv[1]) == "--test") {
        if (test())
        {
            std::cout << Green("Tests passed") << std::endl;
            return 0;
        }
            std::cout << Red("Test failed") << std::endl;
        return -1;
    }
    if (argc <= 1) {
        std::cout << "Usage: " << argv[0] << " file.rat out" << std::endl;
        return 1;
    }
    std::cout << "Opening " << argv[1] << std::endl;
    string content = ReadFile(argv[1]);

    string output = Compile(content);
    WriteFile(argv[2], output);
    return 0;
}
