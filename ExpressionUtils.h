#ifndef AP3_UTILS_H
#define AP3_UTILS_H

#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include "Expression.h"

class ExpressionUtils {
public:

    /**
     * calculate infix string by converting it to prefix using dijkstra’s shunting yard variant,
     * then converts that to a complex expression, calculates it, and return the result.
     */
    double calculateInfixStr(string &infix, unordered_map<string, double> assignment);


    /** Find precedence of operators. **/
    int precedence(string op);

    /**
     * converts infix string to prefix using dijkstra’s shunting yard variant.
     */
    queue<string> infixToPrefixQueue(string &infix);

    /**
     * converts queue of strings(as prefix) to a complex Expression.
     */
    Expression *queueToExp(queue<string> &queueValOp);
};

#endif //AP3_UTILS_H
