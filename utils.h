#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

using namespace std;

void InputString(string& str, const string& prompt, size_t maxLength);
int InputIntInRange(const string& prompt, int minValue, int maxValue);

#endif