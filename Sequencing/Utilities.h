#pragma once
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>activation.h

using namespace std;

static class Utilities
{
public:
	static string stringToLower(string input);
	static void PrintMessageInColor(string message, int color);
	static void PrintError(string message);
	static string removeformatting(string horribleString);
};

