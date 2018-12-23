#ifndef AP3_DATABINDS_H
#define AP3_DATABINDS_H

#include <string>
#include <unordered_map>

using namespace std;

class DataBinds {
private:
    unordered_map<string, string> varToNameInSimulator;
public:
    unordered_map<string, string> getVarToNameInSimulator();
    explicit DataBinds();
    void addNewBind(const string &nameInSimulator, const string &varName);
};


#endif //AP3_DATABINDS_H
