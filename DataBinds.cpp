#include "DataBinds.h"

DataBinds::DataBinds() = default;

void DataBinds::addNewBind(string &nameInSimulator, string &varName) {
    varToNameInSimulator.insert(pair<string, string>(varName, nameInSimulator));
}

unordered_map<string, string> DataBinds::getVarToNameInSimulator() {
    return varToNameInSimulator;
}
