#include "ConditionParser.h"
#include "ExpressionUtils.h"
#include "DataVars.h"

ConditionParser::ConditionParser(const string &left, const string &oper, const string &right, DataVars *dataVars) {
    this->dataVars = dataVars;
    ExpressionUtils expUtils;
    this->left = expUtils.calculateInfixStr(left, this->dataVars->getSymbolTable());
    this->oper = oper;
    this->right = expUtils.calculateInfixStr(right, this->dataVars->getSymbolTable());
}

bool ConditionParser::checkCondition() {
    if (this->oper == "<") {
        return this->left < this->right;
    } else if (this->oper == ">") {
        return this->left > this->right;
    } else if (this->oper == "<=") {
        return this->left <= this->right;
    } else if (this->oper == ">=") {
        return this->left >= this->right;
    } else if (this->oper == "==") {
        return this->left == this->right;
    } else if (this->oper == "!=") {
        return this->left != this->right;
    } else {
        throw "invalid operator";
    }
}
