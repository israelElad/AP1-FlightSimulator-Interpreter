//
// Created by elad on 18/12/18.
//

#include "ExpressionUtils.h"

using namespace std;

/**
 * calculate infix string by converting it to prefix using dijkstra’s shunting yard variant,
 * then converts that to a complex expression, calculates it, and return the result.
 */
double ExpressionUtils::calculateInfixStr(const string &infix, unordered_map<string, double> assignment) {
    queue<string> prefixQueue = infixToPrefixQueue(infix);
    Expression *exp = queueToExp(prefixQueue);
    return exp->calculate(assignment);
}


/** Find precedence of operators. **/
int ExpressionUtils::precedence(const string &op) {
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

void ExpressionUtils::treatNegBracesAndSpaces(string &infix){
    //delete spaces
    std::string::iterator end_pos = std::remove(infix.begin(), infix.end(), ' ');
    infix.erase(end_pos, infix.end());
    string toSearch="-(";
    string replaceStr="-1*(";
    // Get the first occurrence
    size_t pos = infix.find(toSearch);

    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Replace this occurrence of Sub String
        infix.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos =infix.find(toSearch, pos + toSearch.size());
    }
}


/**
 * converts infix string to prefix using dijkstra’s shunting yard variant.
 */
queue<string> ExpressionUtils::infixToPrefixQueue(const string &infixToChange) {

    //string copy
    string infix=infixToChange;
    // stack to store operators.
    stack<string> stackOp;

    // queue to store vals and operators.
    queue<string> queueValOp;

    bool flagOp = true;
    bool isNeg = false;

    treatNegBracesAndSpaces(infix);

    for (unsigned int i = 0; i < infix.length(); i++) {
        // whitespace- skip.
        if (isspace(infix[i]))
            continue;

            //opening brace - push to stack
        else if (infix[i] == '(') {
            //negative braces are taken care of in treatNegBraces method
            isNeg=false;
            flagOp=true;
            stackOp.push(string(1, infix[i]));
        }

            // number-push to the values queue
        else if (isdigit(infix[i])) {
            string valStr;
            if (isNeg) {
                valStr = "-";
                isNeg = false;
            }
            while (isdigit(infix[i]) || infix[i] == '.') {
                valStr += infix[i];
                i++;
            }
            i--;
            queueValOp.push(valStr);
            flagOp = false;
        }

            //variable- push to queue
        else if (((infix[i] >= 'a') && (infix[i] <= 'z')) || ((infix[i] >= 'A') && (infix[i] <= 'Z'))) {
            string varStr;
            if (isNeg) {
                varStr = "-";
                isNeg = false;
            }
            while (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != ')' &&
                   i < infix.length() && !isspace(infix[i])) {
                varStr += infix[i];
                ++i;
            }
            --i;
            queueValOp.push(varStr);
            flagOp = false;
        }

            // Closing braces
        else if (infix[i] == ')') {
            while (!stackOp.empty() && stackOp.top() != "(") {
                //pop operator from stack onto queue
                queueValOp.push(stackOp.top());
                stackOp.pop();
            }
            if (stackOp.top() == "(") {
                // pop opening brace.
                stackOp.pop();
            } else {
                throw "Opening braces missing";
            }
            flagOp = false;
        }
            //operator
        else {
            if (infix[i] == '-') {
                if (flagOp) {
                    isNeg = true;
                    continue;
                }
            }if (infix[i] == '+') { //redundant
                if(flagOp){
                    continue;
                }
            }
            flagOp = true;
            //while the top of operators stack has equal or greater precedence than the current token(operator)
            while (!stackOp.empty() && precedence(stackOp.top()) >= precedence(string(1, infix[i]))) {
                //pop operator from stack onto queue
                queueValOp.push(stackOp.top());
                stackOp.pop();
            }
            stackOp.push(string(1, infix[i]));
        }
    }
    //no more tokens to read
    while (!stackOp.empty()) {
        //pop operator from stack onto queue
        queueValOp.push(stackOp.top());
        stackOp.pop();
    }
    return queueValOp;
}

/**
 * converts queue of strings(as prefix) to a complex Expression.
 */
Expression *ExpressionUtils::queueToExp(queue<string> &queueValOp) {
    //all tokens in queue - convert to Expressions
    stack<Expression *> expStack;
    while (!queueValOp.empty()) {
        Expression *num;
        Expression *neg;
        Expression *var;
        //take number from front
        string front = queueValOp.front();
        queueValOp.pop();
        if (front == "+" || front == "-" || front == "*" || front == "/") {//operator
            Expression *secondNum = expStack.top();
            expStack.pop();
            Expression *firstNum = expStack.top();
            expStack.pop();

            Expression *exp;
            if (front == "+") {
                exp = new Plus(firstNum, secondNum);
                deathMap.push_back(exp);
            } else if (front == "-") {
                exp = new Minus(firstNum, secondNum);
                deathMap.push_back(exp);
            } else if (front == "/") {
                exp = new Div(firstNum, secondNum);
                deathMap.push_back(exp);
            } else if (front == "*") {
                exp = new Mult(firstNum, secondNum);
                deathMap.push_back(exp);
            }
            expStack.push(exp);
        } else if (front[0] == '-') {//neg num
            front.erase(front.find('-'), 1);
            if (isdigit(front[0])) {//num
                num = new Num(stod(front));
                deathMap.push_back(num);
                neg = new Neg(num);
                deathMap.push_back(neg);
                expStack.push(neg);
            } else { //var
                var = new Var(front);
                deathMap.push_back(var);
                neg = new Neg(var);
                deathMap.push_back(neg);
                expStack.push(neg);
            }
        } else if (isdigit(front[0])) {//num
            num = new Num(stod(front));
            deathMap.push_back(num);
            expStack.push(num);
        } else { //var
            var = new Var(front);
            deathMap.push_back(var);
            expStack.push(var);
        }
    }
    //only one (complex) expression left on stack
    return expStack.top();
}