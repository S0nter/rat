#pragma once

#include <string>
#include <vector>


bool IsOperator(std::string value);
bool IsComparator(std::string value);
bool IsNumber(std::string value);

std::string Red(std::string text);
std::string Green(std::string text);

std::string Quote(std::string str);

void Error(std::string text);
