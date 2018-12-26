#ifndef AP3_CONDITIONPARSER_H
#define AP3_CONDITIONPARSER_H

#include <string>
#include "DataVars.h"

using namespace std;

class ConditionParser {
    double left;
    string oper;
    double right;
    DataVars* dataVars;

public:
    ConditionParser(const string &left, const string &oper, const string &right, DataVars* dataVars);
    bool checkCondition();
};


#endif //AP3_CONDITIONPARSER_H
