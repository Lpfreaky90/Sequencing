#pragma once
#include <string>activecf.h
#include <map>adodef.h
#include <iostream>
#include <functional>__msvc_all_public_headers.hpp
#include <thread>_dbdao.h
#include <algorithm>
#include <vector>activation.h

using namespace std;

class Sequence
{
public:
	/* Transcribes RNA to mRNA*/
	string Transcribe(string input);
	
	/*Just replaces T's with U's so we can use the lookup table*/
	string TtoU(string input);

	/*Gets the protein sequences from start-end proteins.*/
	vector<string> GetProteins(vector<string> input);

	/*Get the protein sequences*/
	vector<string> Translate(string input);

	struct ProteinName
	{
		string longName;
		string shortName;
	};
};