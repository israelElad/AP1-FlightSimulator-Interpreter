#ifndef AP3_UTILS_H
#define AP3_UTILS_H

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include "Expression.h"

class ExpressionUtils {
    vector<Expression*> deathMap;
public:

    /**
     * calculate infix string by converting it to prefix using dijkstra’s shunting yard variant,
     * then converts that to a complex expression, calculates it, and return the result.
     */
    double calculateInfixStr(const string &infix, unordered_map<string, double> assignment);


    /** Find precedence of operators. **/
    int precedence(const string &op);

    /**
     * converts infix string to prefix using dijkstra’s shunting yard variant.
     */
    queue<string> infixToPrefixQueue(const string &infix);

    void treatNegBracesAndSpaces(string &infix);


    /**
     * converts queue of strings(as prefix) to a complex Expression.
     */
    Expression *queueToExp(queue<string> &queueValOp);

    ~ExpressionUtils(){
        auto it = this->deathMap.begin();
        while (it != this->deathMap.end()){
            delete *it;
            it++;
        }
    }
};


#endif //AP3_UTILS_H
