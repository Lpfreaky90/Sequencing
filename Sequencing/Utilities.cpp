#pragma once
#include "Utilities.h"

using namespace std;
//returns lowercase values of typed functions
string Utilities::stringToLower(string input)
{
	transform(input.begin(), input.end(), input.begin(), tolower);
	return input;
}

//setting the color of a sentence
void Utilities::PrintMessageInColor(string message, int color = 36) {
	cout << "\033[1;" << color << "m" << message << "\033[0m" << endl;
}

//standard color for Error Messages
void Utilities::PrintError(string message)
{
	PrintMessageInColor(message, 31);
}

string Utilities::removeformatting(string input) {
	input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
	input.erase(std::remove_if(std::begin(input), std::end(input),
		[](auto ch) { return std::isdigit(ch); }),
		input.end());
	return input;
}