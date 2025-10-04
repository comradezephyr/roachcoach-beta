#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#define FILE_NAME "Record.log"

void decodeMessage();

void decodeMessage() {
    ifstream inputFile(FILE_NAME);
    ofstream outputFile("Data.log", ios::app);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening files." << endl;
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        if (line[0] == '0') {
            outputFile << line.substr(2) << endl;
        } else {
            for (size_t i = 0; i < line.length(); i += 2) {
                if (i + 1 < line.length()) {
                    int key = (line[i] - '0') * 10 + (line[i + 1] - '0');
                    outputFile << key << " ";
                }
            }
            outputFile << endl;
        }
    }

    inputFile.close();
    outputFile.close();
}