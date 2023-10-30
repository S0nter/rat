#include <iostream>
#include <fstream>
#include "rat.cpp"

using namespace std;

string Red(string text)
{
    return "\33[1;91m" + text + "\33[0m";
}

string ReadFile(string name)
{
    fstream file;
    file.open("./" + name, ios_base::in);
    if (!file.is_open())
    {
        cout << "Cannot open " << "\"" << Red(name) << "\"" << endl;
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
        cout << "Cannot open " << "\"" << Red(name) << "\"" << endl;
        exit(1);
    }
    file << content;
    file.close();
}

int main(int argc, char* argv[])
{
    if (argc <= 1) {
        std::cout << "Usage: " << argv[0] << " file.rat out" << endl;
        return 1;
    }
    cout << "Opening " << argv[1] << endl;
    string content = ReadFile(argv[1]);
    
    string output = Compile(content);
    WriteFile(argv[2], output);
    return 0;
}
