#include <iostream>
#include <fstream>
#include "rat.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    cout << argv[1] << endl;
    if (argc <= 1) {
        std::cout << "Usage: " << argv[0] <<" file.rat out" << endl;
        return 1;
    }
    string name(argv[1]);
    fstream file;
    cout << "File name: " << name << endl;;
    file.open("./" + name, ios_base::in);
    if (!file.is_open())
    {
        cout << "Cannot open \33[1;91m\"" + name + "\"\33[0m" << endl;
        return 1;
    }
    string content;
    string line;
    while (getline(file, line))
        content += line + '\n';
    file.close();

    string output = Compile(content);
    fstream outputfile;
    outputfile.open(argv[2], ios_base::out);
    if (!outputfile.is_open())
    {
        cout << "Cannot open \33[1;91m\"" << argv[2] << "\"\33[0m" << endl;
        return 1;
    }
    outputfile << output;
    outputfile.close();
    cout << "SUCCESS";
}
