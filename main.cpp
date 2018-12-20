#include <string>
#include <vector>
#include <ios>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "DataCommands.h"
#include "Command.h"
#include "DataVars.h"
#include "ConnectCommand.h"
#include "WhileCommand.h"
#include "BindCommand.h"
#include "PrintCommand.h"
#include "VarCommand.h"
#include "OpenDataServerCommand.h"
#include "IfCommand.h"
#include "EqualCommand.h"

using namespace std;

vector<string> lexer(string &toSeparate);

unsigned long findMinIndexToSeparate(const string &str);

void addSpaces(string &toSeparate);

void parse(vector<string> &separated);

// Receive a line or a set of commands and values from the user. Transfer them to the lexer
// and then to the parser.
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
            vector<string> tmpV = lexer(buffer);
            separated.insert(separated.end(), tmpV.begin(), tmpV.end());
            getline(file, buffer);
        }
        file.close();

    } else if (argc == 1) { // from users input
        string tmpS;
        getline(cin, tmpS);
        vector<string> tmpV = lexer(tmpS);
        separated.insert(separated.end(), tmpV.begin(), tmpV.end());
    } else { //invalid arguments
        throw "invalid arguments!";
    }
    parse(separated);
    return 0;
}

// Separating a line into words.
vector<string> lexer(string &toSeparate) {
    vector<string> separated;
    addSpaces(toSeparate);
    unsigned long index = findMinIndexToSeparate(toSeparate);
    string word;
    while (index != string::npos) {
        string sub = toSeparate.substr(0, index);
        if ((sub.empty()) || (sub == "\f") || (sub == "\n") || (sub == "\r") || (sub == "\t") || (sub == "\v")
            || (sub == ",")) {
            toSeparate.erase(0, index + 1);
            index = findMinIndexToSeparate(toSeparate);
            continue;
        }
        separated.push_back(sub);
        toSeparate.erase(0, index + 1);
        index = findMinIndexToSeparate(toSeparate);
    }
    separated.push_back(toSeparate);
    return separated;
}

void parse(vector<string> &separated) {
    unordered_map<string, Command *> stringsToCommands;
    DataCommands *dataCommands;
    dataCommands = new DataCommands(separated);
    DataVars *dataVars;
    dataVars = new DataVars();
    DataBinds *dataBinds;
    dataBinds = new DataBinds();
    stringsToCommands.insert(
            pair<string, Command *>("openDataServer", new OpenDataServerCommand(dataCommands, dataBinds, dataVars)));
    stringsToCommands.insert(pair<string, Command *>("connect", new ConnectCommand(dataCommands)));
    stringsToCommands.insert(pair<string, Command *>("var", new VarCommand(dataCommands, dataVars)));
    stringsToCommands.insert(pair<string, Command *>("bind", new BindCommand(dataCommands, dataBinds)));
    stringsToCommands.insert(pair<string, Command *>("while", new WhileCommand(dataCommands)));
    stringsToCommands.insert(pair<string, Command *>("if", new IfCommand(dataCommands)));
    stringsToCommands.insert(pair<string, Command *>("print", new PrintCommand(dataCommands, dataVars)));
    stringsToCommands.insert(pair<string, Command *>("=", new EqualCommand(dataCommands)));
    auto it1 = separated.begin();
    while (it1 != separated.end()) {
        auto it2 = stringsToCommands.find(*it1);
        if (it2 == stringsToCommands.end()) {
            it1++;
            continue;
        }
        Command *command = it2->second;
        command->doCommand();
        it1++;
    }
}

unsigned long findMinIndexToSeparate(const string &str) {
    vector<unsigned long> tmpVec = {str.find(' '), str.find('\f'), str.find('\n'), str.find('\r'),
                                    str.find('\t'), str.find('\v'), str.find(',')};
    auto it = min_element(tmpVec.begin(), tmpVec.end());
    unsigned long index = *(it);
    return index;
}

void addSpaces(string &toSeparate) {
    short opLen = 2;
    vector<unsigned long> tmpVec1 = {toSeparate.find("=="), toSeparate.find("!="), toSeparate.find(">="), toSeparate
            .find("<="), toSeparate.find("!=")};
    auto it1 = min_element(tmpVec1.begin(), tmpVec1.end());
    unsigned long index = *(it1);
    if (index == string::npos) {// ==,!=,>=,<=,!= wasn't found - search =,<,>
        vector<unsigned long> tmpVec2 = {toSeparate.find('='), toSeparate.find('<'), toSeparate.find('>')};
        auto it2 = min_element(tmpVec2.begin(), tmpVec2.end());
        index = *(it2);
        opLen = 1;
    }

    if (index != string::npos) {
        toSeparate.insert(index, " ");
        if (opLen == 2) {
            toSeparate.insert(index + 3, " ");
        } else {
            toSeparate.insert(index + 2, " ");
        }
    }

}