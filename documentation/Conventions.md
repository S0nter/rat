## Best practices and naming coventions:
 - functions, structs, enums, etc. should be in ***PascalCase***
 - variable names should be in ***camelCase***
 - ***curly brackets*** after the function definition, etc. should be on the next line
 - ***spacing*** have to be persistent
 - ***commas*** should be at the end of iterable (when possible) to reduce occasional errors
 - you should use ***std::*** but it's not that necessary
 - ***comments*** shoud be meaningfull and neat
 - ***names*** HAVE TO MAKE SENCE
 - it's always better to write ***safe*** and foolproof ***code***
    
### Examples:

**Ugly** code:
```cpp
void fun (int t_i) {
    vector < int> t {
    1, 2,3,
        4,
        5
    };

    
    cout<< t.at ( t_id) <<endl;//get t at t_i
}
```


**Neat** code:
```cpp
void GetToken(int indexOfToken)
{
    vector<int> tokens 
    {
        1,
        2,
        3,
        4,
        5,
    };
    if (indexOfToken >= 0 && indexOfToken < tokens.size())
        std::cout << tokens.at(indexOfToken) << std::endl; // print token at indexOfToken
}
```