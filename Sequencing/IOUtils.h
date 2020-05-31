#pragma once
#include "Sequence.h";
#include <iostream>
#include <fstream>

using namespace std;
class IOUtils
{
public:
	static string infoToJson(Sequence::info information);
	static void saveToDisk(string filename, string fileContent);
};

