#include "IOUtils.h"

using namespace std;
string IOUtils::infoToJson(Sequence::info information) {
	information.name;
	string result = "{\n\t\"numberOfProteins\" : " + to_string(information.numberOfProteins) + ", \n";

	if (information.numberOfProteins > 0) {
		result += "\t\"sequences\" : {\n";
		int i = 1;
		for (Sequence::proteinInfo sequence : information.proteins) {
			result += "\t\t\"" + to_string(i);
			result += "\" : {\n";
			result += "\t\t\t\"proteinLength\" : \"" + to_string(sequence.baseLength / 3) + "\",\n";
			result += "\t\t\t\"proteinSequence\" : \"" + sequence.proteinSequence + "\",\n";
			result += "\t\t\t\"OGSequence\" : \"" + sequence.OGSequence + "\"\n";
			result += "\t\t}";

			if (i != information.numberOfProteins)
			{
				result += ",\n";
			}
			else {
				result += "\n\t},\n";
			}
			i++;
		}
	}

	result += "\t\"sequence\" : \"" + information.sequence;
	result += "\"\n}";

	return result;
}

string  IOUtils::saveToDisk(string filename, string fileContent) {
	ofstream file;
	file.open(filename + ".json");
	file << fileContent;
	file.close();
}