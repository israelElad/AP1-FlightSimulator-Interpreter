#ifndef AP3_DATAVARS_H
#define AP3_DATAVARS_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Command.h"

using namespace std;

class DataVars {
private:
    unordered_map<string, double> symbolTable;
    vector<string> lastChanged;
public:
    bool isChanged=false;

    void addLastChanged(const string &newLastChanged);

    vector<string> getLastChanged();

    unordered_map<string, double> getSymbolTable();

    void setSymbolTableValue(const string &key, double &newValue);

    explicit DataVars();

    void addNewVar(const string &newVar);

    void deleteFirstElementFromLastChanged();
};


#endif //AP3_DATAVARS_H
