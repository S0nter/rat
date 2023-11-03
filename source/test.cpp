#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#include "basic_functions.h"


using test_func=std::function<bool()>;


// create a map object
std::vector<test_func> test_functions {
    {"+", plus<long>()},
    {"-", minus<long>()},
    {"/", divides<long>()},
    {"*", multiplies<long>()}
};

bool TestIsOperator()
    {
        if (IsOperator("*") &&
            IsOperator("/") &&
            IsOperator("+") &&
            IsOperator("-")) return true;
        return false;
    };
    
map <int, fptr>
int test(int number = -1)
{
    
    if (TestIsOperator())
    {
        std::cout << Green("Tests passed") << std::endl;
        return 0;
    }
    std::cout << Red("Test failed") << std::endl;
    return -1;
    
}