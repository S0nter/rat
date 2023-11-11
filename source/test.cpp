#include <iostream>
#include <vector>
#include <bits/stdc++.h>

#include "basic_functions.h"


bool testIsOperator()
{
    if (IsOperator("*") &&
        IsOperator("/") &&
        IsOperator("+") &&
        IsOperator("-")) return true;
    return false;
}

bool testTokenize1()
{
    // FIXME
    return false;
}

// tests
std::vector<std::function<bool()>> test_functions
{
    testIsOperator,
    testTokenize1,
};
   
int test(int number = -1)
{
    bool failed = false;
    if (number == -1) // all tests
    {
        
        for (int i = 0 ; i < int(test_functions.size()); i++) 
        {
            if (test_functions[i]()) 
                std::cout << Green("Test " + std::to_string(i) + " passed") << std::endl;
            else
            {
                std::cout << Red("Test " + std::to_string(i) + " failed") << std::endl;
                failed = true;
            }
        }
    }
    else if (number > int(test_functions.size()) - 1)
    {
        std::cout << Red("Test " + std::to_string(number) + " does not exist") << std::endl;
        failed = true;
    }
    else
    {
        if (test_functions[number]())
        {
            std::cout << Green("Test " + std::to_string(number) + " passed") << std::endl;
        }
        else
        {
            std::cout << Red("Test " + std::to_string(number) + " failed") << std::endl;
            failed = true;
        }
    }
    if (failed) return -1;
    else return 0;
}