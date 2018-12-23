#include "DataBinds.h"

DataBinds::DataBinds() = default;

void DataBinds::addNewBind(const string &nameInSimulator, const string &varName) {
    varToNameInSimulator.insert(pair<string, string>(varName, nameInSimulator));
}

unordered_map<string, string> DataBinds::getVarToNameInSimulator() {
    return varToNameInSimulator;
}
