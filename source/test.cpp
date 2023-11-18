#include <iostream>
#include <vector>
#include <functional>
#include <string>

#include "rat.h"
#include "basic_functions.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "Converter.h"

bool CompareTokens(Token token1, Token token2)
{
    if (token1.type != token2.type || token1.value != token2.value || token1.priority != token2.priority)
        return false;
    else
    {
        if (token1.left == token2.left && token1.right == token2.right)
            return true;
        if (token1.left != token2.left)
        {
            if (!CompareTokens(*token1.left, *token2.left))
                return false;
        }
        if (token1.right != token2.right)
        {
            if (!CompareTokens(*token1.right, *token2.right))
                return false;
        }
        return true;
    }
}

bool CompareLines(std::vector<Token> vector1, std::vector<Token> vector2)
{
    if (vector1.size() != vector2.size())
        return false;
    for (size_t i = 0; i < vector1.size(); i++)
    {
        if (!CompareTokens(vector1.at(i), vector2.at(i)))
            return false;
    }
    return true;
}

bool TestAddToken()
{
    std::string buffer = "69"; // test buffer
    // expected values:
    Token expected;
    expected.type = Type::_number;
    expected.value = "69";
    expected.priority = 1;
    expected.left = nullptr;
    expected.right = nullptr;

    Token result = AddToken(buffer);
    return CompareTokens(result, expected);
}

bool TestTokenize()
{
    std::string text = "exit 60 + 9"; // test text
    // expected values:
    std::vector<Token> expected = {
        AddToken("exit"),
        AddToken("60"),
        AddToken("+"),
        AddToken("9"),
    };
    std::vector<Token> result = Tokenize(text);
    return CompareLines(result, expected);
}

bool TestTokenize2()
{
    std::string text = "exit 13* 3 ==1\n;;\n"; // test "=="
    // expected values:
    std::vector<Token> expected = {
        AddToken("exit"),
        AddToken("13"),
        AddToken("*"),
        AddToken("3"),
        AddToken("=="),
        AddToken("1"),
        AddToken("\n"),
        AddToken(";"),
        AddToken(";"),
        AddToken("\n"),
    };
    std::vector<Token> result = Tokenize(text);
    return CompareLines(result, expected);
}

bool TestDivide()
{
    std::vector<Token> tokens = { // test tokens
        AddToken("60"),
        AddToken("+"),
        AddToken("9"),
        AddToken(";"),
        AddToken("blah"),
    };
    // expected values:
    std::vector<std::vector<Token>> expected = {
        { AddToken("60"), AddToken("+"), AddToken("9"), },
        { AddToken("blah"), },
    };
    std::vector<std::vector<Token>> result = Divide(tokens);
    for (size_t i = 0; i < result.size(); i++)
    {
        if (!CompareLines(result.at(i), expected.at(i)))
            return false;
    }
    return true;
}

bool TestParse()
{
    std::vector<Token> tokens = { // test tokens
        AddToken("exit"),
        AddToken("60"),
        AddToken("+"),
        AddToken("9"),
    };
    // expected values:
    Token expected = AddToken("exit");
    expected.left = nullptr;
    Token right = AddToken("+");
    expected.right = &right;
    Token rightLeft = AddToken("60");
    Token rightRight = AddToken("9");
    expected.right->left = &rightLeft;
    expected.right->right = &rightRight;

    Token* result = Parse(&tokens, 0, tokens.size() - 1);
    return CompareTokens(expected, *result);
}

bool TestConvert()
{
    std::vector<Token> tokens = { // test tokens
        AddToken("exit"),
        AddToken("60"),
        AddToken("+"),
        AddToken("9"),
    };

    // expected values:
    std::string expected;
    expected += "section .text\n";
    expected += "global _start\n";
    expected += "_start:\n";

    return Convert(tokens) == expected;
}

std::vector<std::function<bool()>> tests
{
    TestAddToken,
    TestTokenize,
    TestTokenize2,
    TestDivide,
    TestParse,
    TestConvert,
};
   
int Test(size_t index)
{
    int failed = false;
    if (index < tests.size())
    {
        if (tests.at(index)())
            std::cout << Green("Test " + std::to_string(index) + " passed") << std::endl;
        else
        {
            std::cout << Red("Test " + std::to_string(index) + " failed") << std::endl;
            failed = true;
        }
    }
    else // index error
    {
        std::cout << Red("Test " + std::to_string(index) + " does not exist") << std::endl;
        failed = true;
    }
    return failed;
}

int TestAll()
{
    int failed = false;
    for (size_t i = 0; i < tests.size(); i++) 
    {
        if (tests.at(i)()) 
            std::cout << Green("Test " + std::to_string(i) + " passed") << std::endl;
        else
        {
            std::cout << Red("Test " + std::to_string(i) + " failed") << std::endl;
            failed = true;
            return failed;
        }
    }
    return failed;
}