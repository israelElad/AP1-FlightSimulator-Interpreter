/******************************************
* Simulator project- first milestone
* Elad Israel
* 313448888
* Narkis Shallev Kermizi
* 205832447
******************************************/

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "TextAnalyzer.h"

using namespace std;

/* Receive a line or a set of commands and values from the user. Transfer them to the lexer
 * and then to the parser. */
int main(int argc, char *argv[]) {
    vector<string> separated;
    if (argc == 2) { // from file
        fstream file;
        string buffer;
        file.open(argv[1], ios_base::in);
        if (!file.is_open()) {
            throw "cannot open file!";
        }
        getline(file, buffer);
        while (!file.eof()) {
            vector<string> tmpV = TextAnalyzer::lexer(buffer);
            separated.insert(separated.end(), tmpV.begin(), tmpV.end());
            getline(file, buffer);
        }
        vector<string> tmpV = TextAnalyzer::lexer(buffer);
        separated.insert(separated.end(), tmpV.begin(), tmpV.end());
        file.close();

    } else if (argc == 1) { // from users input
        string tmpS;
        getline(cin, tmpS);
        vector<string> tmpV = TextAnalyzer::lexer(tmpS);
        separated.insert(separated.end(), tmpV.begin(), tmpV.end());
    } else { //invalid arguments
        throw "invalid arguments!";
    }
    bool shouldStop = false;
    TextAnalyzer::parse(separated, shouldStop);
    while (true) {}
    return 0;
}
