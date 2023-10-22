using namespace std;
#include <iostream>
#include <fstream>
#include "./rat.cpp"

int main()
{
    string name = "file.rat";
    fstream file;
    cout << "File name: ";
    cout << name << endl; //cin >> name;
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
    outputfile.open("./output.asm", ios_base::in);
    if (!outputfile.is_open())
    {
        cout << "Cannot open \33[1;91m\"output.asm\"\33[0m" << endl;
        return 1;
    }
    outputfile << output;
    outputfile.close();
    cout << "SUCCESS";
}
