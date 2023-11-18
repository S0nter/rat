#pragma once

#include <vector>

#include "rat.h"

Token *Parse(std::vector<Token> *tokens, int from, int to);
void PrintTree(const std::string& prefix, const Token* node, bool isLeft);