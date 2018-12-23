#ifndef AP3_DATAVARS_H
#define AP3_DATAVARS_H

#include <string>
#include <unordered_map>
#include "Command.h"

using namespace std;

class DataVars {
private:
    unordered_map<string, double> symbolTable;
public:
    unordered_map<string, double> getSymbolTable();

public:
    void setSymbolTableValue(const string &key, double &newValue);
    explicit DataVars();
    void addNewVar(const string &newVar);
};


#endif //AP3_DATAVARS_H
