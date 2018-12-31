//
// Created by root on 31/12/18.
//

#include "TextAnalyzer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include "DataCommands.h"
#include "Command.h"

using namespace std;

// Separating a line into words.
vector<string> TextAnalyzer::lexer(string &toSeparate) {
    vector<string> separated;
    addSpaces(toSeparate);
    unsigned long index = findMinIndexToSeparate(toSeparate);
    string sub;
    while (index != string::npos) {
        sub = toSeparate.substr(0, index);
        if ((sub.empty()) || (sub == "\f") || (sub == "\n") || (sub == "\r") || (sub == "\t") || (sub == "\v")
            || (sub == ",")) {
            toSeparate.erase(0, index + 1);
            index = findMinIndexToSeparate(toSeparate);
            continue;
        }
        separated.push_back(sub);
        toSeparate.erase(0, index + 1);
        //there is "=" and no "bind" - complex expression - break, then take the remains of the line as a whole
        if (sub == "=") {
            if (toSeparate.find("bind") == string::npos) {
                break;
            }
        } else if (sub == "print" || sub == "sleep") {
            //complex expression - break, then take the remains of the line as a whole
            break;
        } else if (sub == "if" || sub == "while") {
            //cut upto the operator
            short opLen;
            index = findOperator(toSeparate, opLen);
            sub = toSeparate.substr(0, index);
            toSeparate.erase(0, index);
            separated.push_back(sub);
            //cut operator
            separated.push_back(toSeparate.substr(0, static_cast<unsigned long>(opLen)));
            toSeparate.erase(0, static_cast<unsigned long>(opLen));
            //cut from the operator -  break, then take the remains of the line as a whole
            break;
        } else if (sub == "connect") {
            //cut IP
            index = findMinIndexToSeparate(toSeparate);
            sub = toSeparate.substr(0, index);
            toSeparate.erase(0, index);
            separated.push_back(sub);
            break;
        } else if (sub == "openDataServer") {
            index = 0;
            bool wasNum = false;
            while (!wasNum) {
                while (isspace(toSeparate[index])) {
                    ++index;
                }
                while (isdigit(toSeparate[index]) || (((toSeparate[index] >= 'a') && (toSeparate[index] <= 'z')) ||
                                                      ((toSeparate[index] >= 'A') && (toSeparate[index] <= 'Z')))) {
                    wasNum = true;
                    ++index;
                }
                while (isspace(toSeparate[index])) {
                    ++index;
                }
                if (toSeparate[index] == '+' || toSeparate[index] == '-' || toSeparate[index] == '*' ||
                    toSeparate[index] == '/') {//operator
                    wasNum = false;
                }
                ++index;
            }
            //there was a num without an operator
            --index;
            sub = toSeparate.substr(0, index);
            toSeparate.erase(0, index);
            separated.push_back(sub);
            break;
        }
        index = findMinIndexToSeparate(toSeparate);
    }
    index = min(toSeparate.find('{'), toSeparate.find('}')); //search for '{' or '}'
    if (index != string::npos) { // '{' or '}' was found
        //separate upto '{' or '}'
        sub = toSeparate.substr(0, index);
        toSeparate.erase(0, index);
        separated.push_back(sub);
    }
    if (!((toSeparate.empty()) || (toSeparate == "\f") || (toSeparate == "\n") || (toSeparate == "\r") ||
          (toSeparate == "\t") || (toSeparate == "\v") || (toSeparate == ","))) {
        separated.push_back(toSeparate);
    }
    return separated;
}

void TextAnalyzer::parse(vector<string> &separated, bool &shouldStop) {
    DataCommands *dataCommands;
    dataCommands = new DataCommands(separated);
    unordered_map<string, Command *> stringsToCommands = dataCommands->getStringsToCommands();
    auto it1 = separated.begin();
    Command *command;
    while (it1 != separated.end()) {
        auto it2 = stringsToCommands.find(*it1);
        if (it2 == stringsToCommands.end()) {
            it1++;
            continue;
        }
        command = it2->second;
        command->doCommand();
        if ((*it1 == "while") || (*it1 == "if")){
            it1 = separated.begin();
            it1 += dataCommands->getIndex();
            continue;
        }
        it1++;
    }
}

unsigned long TextAnalyzer::findMinIndexToSeparate(const string &str) {
    vector<unsigned long> tmpVec = {str.find(' '), str.find('\f'), str.find('\n'), str.find('\r'),
                                    str.find('\t'), str.find('\v'), str.find(',')};
    auto it = min_element(tmpVec.begin(), tmpVec.end());
    unsigned long index = *(it);
    return index;
}


unsigned long TextAnalyzer::findOperator(string &toSeparate, short &opLen) {
    opLen = 2;
    vector<unsigned long> tmpVec1 = {toSeparate.find("=="), toSeparate.find("!="), toSeparate.find(">="), toSeparate
            .find("<="), toSeparate.find("!=")};
    auto it1 = min_element(tmpVec1.begin(), tmpVec1.end());
    unsigned long index = *(it1);
    if (index == string::npos) {// ==,!=,>=,<=,!= wasn't found - search =,<,>
        vector<unsigned long> tmpVec2 = {toSeparate.find('='), toSeparate.find('<'), toSeparate.find('>'), toSeparate
                .find('{'), toSeparate.find('}'), toSeparate.find('('), toSeparate.find(')')};
        auto it2 = min_element(tmpVec2.begin(), tmpVec2.end());
        index = *(it2);
        opLen = 1;
    }
    return index;
}

void TextAnalyzer::addSpaces(string &toSeparate) {
    short opLen;
    unsigned long index = findOperator(toSeparate, opLen);
    if (index != string::npos) {
        toSeparate.insert(index, " ");
        if (opLen == 2) {
            toSeparate.insert(index + 3, " ");
        } else {
            toSeparate.insert(index + 2, " ");
        }
    }
}