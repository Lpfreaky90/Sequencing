#pragma once
#include <string>activecf.h
#include <map>adodef.h
#include <iostream>
#include <functional>__msvc_all_public_headers.hpp
#include <thread>_dbdao.h
#include <algorithm>
#include <vector>activation.h
#include "Utilities.h"

using namespace std;

class Sequence
{
public:
	struct ProteinName
	{
		string longName;
		string shortName;
	};

	struct proteinInfo {
		string proteinSequence;
		int startPosition;
		int baseLength;
		string OGSequence;
	};

	struct info
	{
		string name;
		int numberOfProteins;
		string sequence;
		vector<proteinInfo> proteins;
	};

	/* Transcribes RNA to mRNA*/
	string Transcribe(string input);
	
	/*Just replaces T's with U's so we can use the lookup table*/
	string TtoU(string input);

	/*Gets the protein sequences from start-end proteins.*/
	vector<Sequence::proteinInfo> GetProteins(vector<string> input);

	/*Get the protein sequences*/
	vector<string> Translate(string input);

	info GetProteinInformation(string name, string sequence, bool turnDNAintoRNA);

	vector<Sequence::proteinInfo> FillInTheBlanks(vector<Sequence::proteinInfo> info, string OGSequence);
};