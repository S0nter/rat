#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>

#include "basic_functions.h"
#include "rat.h"


bool testIsOperator()
{
    if (IsOperator("*") &&
        IsOperator("/") &&
        IsOperator("+") &&
        IsOperator("-")) return true;
    return false;
}

bool IsEqual(std::vector<Token> vector1, std::vector<Token> vector2)
{
    if (vector1.size() != vector2.size()) return false;
    for (int i=0; i<vector1.size(); i++)
    {
        if (
            vector1[i].value != vector2[i].value ||
            vector1[i].priority != vector2[i].priority ||
            vector1[i].type != vector2[i].type
        ) return false;
    }
    return true;
}

bool testTokenize1()
{
    std::string test_str = "exit 13*  3\n"; // file doesn't always end with  "\n"
    std::vector<Token> correct_result = {
        AddToken("exit"),
        AddToken("13"),
        AddToken("*"),
        AddToken("3"),
        AddToken("\n"),
    };
    std::vector<Token> test_result = Tokenize(test_str);
    return IsEqual(test_result, correct_result);
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