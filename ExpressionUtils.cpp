//
// Created by elad on 18/12/18.
//

#include "ExpressionUtils.h"


/**
 * calculate infix string by converting it to prefix using dijkstra’s shunting yard variant,
 * then converts that to a complex expression, calculates it, and return the result.
 */
double ExpressionUtils::calculateInfixStr(string &infix,unordered_map<string, double> assignment) {
    queue<string> prefixQueue= infixToPrefixQueue(infix);
    Expression *exp= queueToExp(prefixQueue);
    return exp->calculate(assignment);
}


/** Find precedence of operators. **/
int ExpressionUtils::precedence(string op) {
    if (op == "+" || op == "-")
        return 1;
    if (op == "*" || op == "/")
        return 2;
    return 0;
}

/**
 * converts infix string to prefix using dijkstra’s shunting yard variant.
 */
queue<string> ExpressionUtils::infixToPrefixQueue(string &infix) {

    // stack to store operators.
    stack<string> stackOp;

    // queue to store vals and operators.
    queue<string> queueValOp;

    for (int i = 0; i < infix.length(); i++) {
        // whitespace- skip.
        if (isspace(infix[i]))
            continue;

            //opening brace - push to stack
        else if (infix[i] == '(') {
            stackOp.push(string(1,infix[i]));
        }

            // push numbers to the values queue
        else if (isdigit(infix[i])) {
            string valStr;
            while (isdigit(infix[i]) || infix[i] == '.') {
                valStr += infix[i];
                i++;
            }
            i--;
            queueValOp.push(valStr);
        }

            //variable- push to queue
        else if (((infix[i] >= 'a') && (infix[i] <= 'z')) || ((infix[i] >= 'A') && (infix[i] <= 'Z'))) {
            string varStr;
            while (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != ')' &&
                   i < infix.length() &&!isspace(infix[i])) {
                varStr += infix[i];
                ++i;
            }
            --i;
            queueValOp.push(varStr);
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
        }
            //operator
        else {
            //while the top of operators stack has equal or greater precedence than the current token(operator)
            while (!stackOp.empty() && precedence(stackOp.top()) >= precedence(string(1,infix[i]))) {
                //pop operator from stack onto queue
                queueValOp.push(stackOp.top());
                stackOp.pop();
            }
            stackOp.push(string(1,infix[i]));
        }
    }
    //no more tokens to read
    while (!stackOp.empty()){
        //pop operator from stack onto queue
        queueValOp.push(stackOp.top());
        stackOp.pop();
    }
    return queueValOp;
//
//        //convert to Expressions
//        int numVarCounter=0;
//        stack<string> stackHelp;
//        while (!queueValOp.empty()){
//            string back=queueValOp.back();
//            queueValOp.pop_back();
//            if(back == "+" || back == "-" || back == "*" || back == "/"){//operator
//                numVarCounter=0;
//            }
//            else{//var or num
//                ++numVarCounter;
//            }
//            stackHelp.push(back);
//            if(numVarCounter==2){
//                string operand1 =stackHelp.top();
//                stackHelp.pop();
//                Expression *exp1;
//                if(isdigit(operand1[0])){ //exp is num
//                    exp1=new Num(stoi(operand1));
//                }
//                else{//exp is var
//                    exp1=new Var(operand1);
//                }
//                string operand2 =stackHelp.top();
//                stackHelp.pop();
//
//                Expression *exp2;
//                if(isdigit(operand2[0])){ //exp is num
//                    exp2=new Num(stoi(operand2));
//                }
//                else{//exp is var
//                    exp2=new Var(operand2);
//                }
//                string op =stackHelp.top();
//                stackHelp.pop();
//
//                Expression *exp;
//                if(op=="+"){
//                    exp=new Plus(exp1,exp2);
//                }
//                else if(op=="-"){
//                    //todo
//                }
//                else if(op=="/"){
//
//                }
//                else if(op=="*"){
//
//                }
//                while(){
//
//                }
//            }


}


//
//        for(int j=0;!queueValOp.empty(); j++){
//            cout << queueValOp.front() << std::endl;;
//            queueValOp.pop();
//        }

/**
 * converts queue of strings(as prefix) to a complex Expression.
 */
Expression* ExpressionUtils::queueToExp(queue<string> &queueValOp){
    //all tokens in queue - convert to Expressions
    stack<Expression*> expStack;
    while(!queueValOp.empty()) {
        //take number from front
        string front=queueValOp.front();
        queueValOp.pop();
        if(front == "+" || front == "-" || front == "*" || front == "/"){//operator
            Expression *secondNum=expStack.top();
            expStack.pop();
            Expression *firstNum=expStack.top();
            expStack.pop();

            Expression *exp;
            if(front=="+"){
                exp=new Plus(firstNum,secondNum);
            }
            else if(front=="-"){
                exp=new Minus(firstNum,secondNum);
            }
            else if(front=="/"){
                exp=new Div(firstNum,secondNum);
            }
            else if(front=="*"){
                exp=new Mult(firstNum,secondNum);
            }
            expStack.push(exp);
        }
        else if (isdigit(front[0])){//num
            expStack.push(new Num(stod(front)));
        }
        else { //var
            expStack.push(new Var(front));
        }
    }
    //only one (complex) expression left on stack
    return expStack.top();
}

