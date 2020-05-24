// Sequencing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include "Sequence.h"
#include "Utilities.h";
#include "IOUtils.h";

using namespace std;

void print(string input) {
    cout << input << endl;
}

int main(int argc, char* argv[])
{
    string sequence;
    string fileName;
    for (int i = 1; i < argc; ++i) {
        string filenameFromArgs = argv[i];
        try {
            ifstream file(filenameFromArgs);
            if (file.is_open()) {

                string line;
                while (getline(file, line)) {
                    sequence += line;
                }
                file.close();
            }

            sequence = Utilities::removeformatting(sequence);

            const size_t last_slash_idx = filenameFromArgs.find_last_of("\\/");
            if (std::string::npos != last_slash_idx)
            {
                filenameFromArgs.erase(0, last_slash_idx + 1);
            }

            // Remove extension if present.
            const size_t period_idx = filenameFromArgs.rfind('.');
            if (std::string::npos != period_idx)
            {
                filenameFromArgs.erase(period_idx);
            }
            fileName = filenameFromArgs;
        }
        catch (const std::exception & e) { /* woops, file doesn't exist or something*/ }
    }

    bool turnDNAintoRNA = false;
    
    Sequence sequencer;

    if (fileName == "" && sequence == "") {
        cout << "Please enter your sequence:" << endl;
        cin >> sequence;
        cout << "Please enter a filename:" << endl;
        cin >> fileName;
    }

    std::transform(sequence.begin(), sequence.end(), sequence.begin(), ::toupper);

    Sequence::info information = sequencer.GetProteinInformation(fileName, sequence, false);
    Utilities::PrintMessageInColor("Press any button to close",36);
    IOUtils::saveToDisk(fileName, IOUtils::infoToJson(information));

    string asdf;
    cin >> asdf;

    return 0;
}