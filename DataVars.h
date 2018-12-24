#ifndef AP3_DATAVARS_H
#define AP3_DATAVARS_H

#include <string>
#include <unordered_map>
#include "Command.h"

using namespace std;

class DataVars {
private:
    unordered_map<string, double> symbolTable;
    bool isChanged;
    string lastChanged;
public:
    void setLastChanged(const string &newLastChanged);

    string getLastChanged();

    bool getIsChanged();

    void setIsChanged(bool newIsChanged);

    unordered_map<string, double> getSymbolTable();

    void setSymbolTableValue(const string &key, double &newValue);

    explicit DataVars();

    void addNewVar(const string &newVar);
};


#endif //AP3_DATAVARS_H
