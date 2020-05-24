#include "Sequence.h"
using namespace std;

enum ProteinNamingType { shortName, longName};

ProteinNamingType namingType = shortName;

//define variables based on the namingType we use;
string startCodon = namingType == shortName ? "M" : "Met";
string endCodon = namingType == shortName ? "*" : "Ter";
int codonLength = namingType == shortName ? 1 : 3;

//a map with all the proteins
map<string, Sequence::ProteinName> proteins = {
	{"UUU", {"Phe", "F"}},
	{"UUC", {"Phe", "F"}},
	{"UUA", {"Leu", "L"}},
	{"UUG", {"Leu", "L"}},

	{"UCU", {"Ser", "S"}},
	{"UCC", {"Ser", "S"}},
	{"UCA", {"Ser", "S"}},
	{"UCG", {"Ser", "S"}},

	{"UAU", {"Tyr", "Y"}},
	{"UAC", {"Tyr", "Y"}},
	{"UAA", {"Ter", "*"}},
	{"UAG", {"Ter", "*"}},

	{"UGU", {"Cys", "C"}},
	{"UGC", {"Cys", "C"}},
	{"UGA", {"Ter", "*"}},
	{"UGG", {"Trp", "W"}},

	//Codons starting with C
	{"CUU", {"Leu", "L"}},
	{"CUC", {"Leu", "L"}},
	{"CUA", {"Leu", "L"}},
	{"CUG", {"Leu", "L"}},

	{"CCU", {"Pro", "P"}},
	{"CCC", {"Pro", "P"}},
	{"CCA", {"Pro", "P"}},
	{"CCG", {"Pro", "P"}},

	{"CAU", {"His", "H"}},
	{"CAC", {"His", "H"}},
	{"CAA", {"Gln", "Q"}},
	{"CAG", {"Gln", "Q"}},

	{"CGU", {"Arg", "R"}},
	{"CGC", {"Arg", "R"}},
	{"CGA", {"Arg", "R"}},
	{"CGG", {"Arg", "R"}},

	//Codons starting with A
	{"AUU", {"Ile", "I"}},
	{"AUC", {"Ile", "I"}},
	{"AUA", {"Ile", "I"}},
	{"AUG", {"Met", "M"}},

	{"ACU", {"Thr", "T"}},
	{"ACC", {"Thr", "T"}},
	{"ACA", {"Thr", "T"}},
	{"ACG", {"Thr", "T"}},

	{"AAU", {"Asn", "N"}},
	{"AAC", {"Asn", "N"}},
	{"AAA", {"Lys", "K"}},
	{"AAG", {"Lys", "K"}},

	{"AGU", {"Ser", "S"}},
	{"AGC", {"Ser", "S"}},
	{"AGA", {"Arg", "R"}},
	{"AGG", {"Arg", "R"}},

	//Codons starting with G
	{"GUU", {"Val", "V"}},
	{"GUC", {"Val", "V"}},
	{"GUA", {"Val", "V"}},
	{"GUG", {"Val", "V"}},

	{"GCU", {"Ala", "A"}},
	{"GCC", {"Ala", "A"}},
	{"GCA", {"Ala", "A"}},
	{"GCG", {"Ala", "A"}},

	{"GAU", {"Asp", "D"}},
	{"GAC", {"Asp", "D"}},
	{"GAA", {"Glu", "E"}},
	{"GAG", {"Glu", "E"}},

	{"GGU", {"Gly", "G"}},
	{"GGC", {"Gly", "G"}},
	{"GGA", {"Gly", "G"}},
	{"GGG", {"Gly", "G"}}
};

/* Transcribes RNA to mRNA*/
string Sequence::Transcribe(string input) {
	replace(input.begin(), input.end(), 'A', 'U');
	replace(input.begin(), input.end(), 'T', 'A');
	replace(input.begin(), input.end(), 'G', 'X');
	replace(input.begin(), input.end(), 'C', 'G');
	replace(input.begin(), input.end(), 'X', 'C');

	return input;
}

string Sequence::TtoU(string input){
	replace(input.begin(), input.end(), 'T', 'U');
	return input;
}

/*now that we have the sequences, look for the actual coding sequences with an open and close.*/
vector<Sequence::proteinInfo> Sequence::GetProteins(vector<string> sequences) {
	vector<Sequence::proteinInfo> foundSequences;
	for (int i = 0; i < sequences.size(); i++) {
		string sequence = sequences[i];
		int startCodonPosition = sequence.find(startCodon, 0);
		while (startCodonPosition != -1)
		{
			//we have a start codon
			int j = startCodonPosition + codonLength;
			bool endCodonFound = false;
			string codingSequence = namingType == shortName ? "M": "Met";
			while (j <= sequence.length() && !endCodonFound) {
				string nucleotide = sequence.substr(j, codonLength);
				endCodonFound = nucleotide == endCodon;
				if (!endCodonFound) {
					codingSequence += nucleotide;
				}
				j += codonLength;
			}

			if (endCodonFound) {
				int start = startCodonPosition / codonLength;
				int length = (codingSequence.length() / codonLength) * 3;

				foundSequences.push_back({ codingSequence , start, length , ""});
			}

			startCodonPosition = sequence.find(startCodon, startCodonPosition + 1);
		}
	}
	return foundSequences;
}

/*RNA -> protein Sequence*/
vector<string> Sequence::Translate(string input) {
	int stringLength = input.length();
	transform(input.begin(), input.end(), input.begin(), ::toupper);

	vector<string> proteinSequences(3);
	//we need to get all 3 reading frames.
	for (int j = 0; j < 3; j++)
	{
		string proteinSequence = "";
		for (int i = j; i < stringLength; i = i + 3) {
			string protein = input.substr(i, min(3, stringLength - i));
			map<string, Sequence::ProteinName>::iterator result = proteins.find(protein);

			if (result != proteins.end()) {
				proteinSequence += namingType == shortName ? result->second.shortName : result->second.longName;
			}
		}
		proteinSequences[j] = proteinSequence;
	}

	return proteinSequences;
};

vector<Sequence::proteinInfo> Sequence::FillInTheBlanks(vector<Sequence::proteinInfo> info, string OGSequence) {
	vector<Sequence::proteinInfo> result;
	for (Sequence::proteinInfo information : info) {
		information.OGSequence = OGSequence.substr(information.startPosition, information.baseLength - 1);
		result.push_back(information);
	}
	return result;
}

Sequence::info Sequence::GetProteinInformation(string name, string sequence, bool turnDNAintoRNA = false) {
	string mRNAsequence = turnDNAintoRNA ? Transcribe(sequence) : TtoU(sequence);
	vector<string> proteinSequences = Translate(mRNAsequence);
	vector< Sequence::proteinInfo>proteinInfo = GetProteins(proteinSequences);
	proteinInfo = FillInTheBlanks(proteinInfo, sequence);
	return info{ name, (int)proteinInfo.size(), sequence, proteinInfo };
}

