#include "DataVars.h"

DataVars::DataVars() {
    this->isChanged = false;
};

void DataVars::addNewVar(const string &newVar) {
    this->symbolTable.insert(pair<string, double>(newVar, 0));
}

void DataVars::setSymbolTableValue(const string &key, double &newValue) {
    this->symbolTable.at(key) = newValue;
}

unordered_map<string, double> DataVars::getSymbolTable() {
    return this->symbolTable;
}

bool DataVars::getIsChanged() {
    return this->isChanged;
}

void DataVars::setIsChanged(bool newIsChanged) {
    this->isChanged = newIsChanged;
}

string DataVars::getLastChanged() {
    return this->lastChanged;
}

void DataVars::setLastChanged(const string &newLastChanged) {
    this->lastChanged = newLastChanged;
}


