#include <iostream>
#include "DataVars.h"

DataVars::DataVars() = default;;

using namespace std;

void DataVars::addNewVar(const string &newVar) {
    this->symbolTable.insert(pair<string, double>(newVar, 0));
}

void DataVars::setSymbolTableValue(const string &key, double &newValue) {
    this->symbolTable.at(key) = newValue;
}

unordered_map<string, double> DataVars::getSymbolTable() {
    return this->symbolTable;
}

vector<string> DataVars::getLastChanged() {
    return this->lastChanged;
}

void DataVars::addLastChanged(const string &newLastChanged) {
    isChanged = true;
    this->lastChanged.push_back(newLastChanged);
}

void DataVars::deleteFirstElementFromLastChanged() {
    if (this->lastChanged.size() == 1) {
        isChanged = false;
    } else if (this->lastChanged.empty()) {
        throw invalid_argument("cannot delete element");
    }

    this->lastChanged.erase(this->lastChanged.begin());
}



