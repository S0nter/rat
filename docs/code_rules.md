### How to write appropriate code?
 - functions, structs, enums, etc. should be in `PascalCase`
 - variable names should be in `camelCase`
 - curly brackets after the function definition, etc. should be on the next line
 - commas should be at the end of iterable (when possible) to reduce occasional errors
 - you should use `std::` but it's not that necessary
    
#### Examples:
This is how you shouldn't write code:
```cpp
void foo(int bar_qux) {
    vector<int> baz {
    1, 2,3,
        4,
        5
    };
    cout << bar_qux << endl;
}
```


And this is how you should:
```cpp
void Foo(int barQux)
{
    vector<int> baz 
    {
        1,
        2,
        3,
        4,
        5,
    };
    std::cout << barQux << std::endl;
}
```

