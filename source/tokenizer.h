#pragma once
#include <string>
#include "rat.h"

Token AddToken(std::string value);
std::vector<Token> Tokenize(std::string text);
std::vector<std::vector<Token>> Divide(std::vector<Token> tokens);