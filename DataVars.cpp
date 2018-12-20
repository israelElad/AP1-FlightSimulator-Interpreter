#include "DataVars.h"

DataVars::DataVars() = default;

void DataVars::addNewVar(string newVar) {
    this->symbolTable.insert(pair<string, double>(newVar, 0));
}

void DataVars::setSymbolTableValue(string key, double newValue) {
    this->symbolTable.at(key) = newValue;
}

unordered_map<string, double> &DataVars::getSymbolTable() {
    return symbolTable;
}


