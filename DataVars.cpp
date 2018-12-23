#include "DataVars.h"

DataVars::DataVars() = default;

void DataVars::addNewVar(const string &newVar) {
    this->symbolTable.insert(pair<string, double>(newVar, 0));
}

void DataVars::setSymbolTableValue(const string &key, double &newValue) {
    this->symbolTable.at(key) = newValue;
}

unordered_map<string, double> DataVars::getSymbolTable() {
    return symbolTable;
}


