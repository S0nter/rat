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
        main();
    }
    string content;
    string line;
    while (getline(file, line))
        content += line + '\n';
    file.close();

    Compile(content);
}