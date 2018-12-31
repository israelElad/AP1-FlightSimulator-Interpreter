#include <iostream>
#include "Expression.h"

using namespace std;
//Num

Num::Num(double num) {
    this->num = num;
}

/**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
double Num::calculate(unordered_map<string, double> assignment) {
    return num;
}

/**
* A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
*/
double Num::calculate() {
    return num;
}

/** Returns a new expression in which all occurrences of the variable
 * var are replaced with the provided expression (Does not modify the current expression).**/
Expression *Num::assign(string var, Expression *expression) {
    return this;
}


//Var

Var::Var(string var) {
    this->var = var;
}

/**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
double Var::calculate(unordered_map<string, double> assignment) {
    if (assignment.find(this->var) != assignment.end()) { //found in map
        return assignment.at(this->var);
    } else {
        throw "The expression contains a variable which is not in the assignment!";
    }
}

/**
 * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
 */
double Var::calculate() {
    throw "The expression contains a variable which is not in the assignment!!!";
}

/** Returns a new expression in which all occurrences of the variable
  * var are replaced with the provided expression (Does not modify the current expression).**/
Expression* Var::assign(string var, Expression *expression) {
    if (var.compare(this->var) == 0) {
        return expression;
    }
    //assignment of another variable - returns the Expression as is.
    return this;
}

// Neg
Neg::Neg(Expression *exp) {
    this->exp = exp;
}

/**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
double Neg::calculate(unordered_map<string, double> assignment) {
    return -exp->calculate(assignment);
}

/**
* A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
*/
double Neg::calculate() {
    return -exp->calculate();
}

/** Returns a new expression in which all occurrences of the variable
 * var are replaced with the provided expression (Does not modify the current expression).**/
Expression *Neg::assign(string var, Expression *expression) {
    return new Neg(exp->assign(var, expression));
}


//Plus

Plus::Plus(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}

/**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
double Plus::calculate(unordered_map<string, double> assignment) {
    return left->calculate(assignment) + right->calculate(assignment);
}

/**
 * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
 */
double Plus::calculate() {
    return left->calculate() + right->calculate();
}

/** Returns a new expression in which all occurrences of the variable
 * var are replaced with the provided expression (Does not modify the current expression).**/
Expression *Plus::assign(string var, Expression *expression) {
    return new Plus(left->assign(var, expression), right->assign(var, expression));
}


//Minus

Minus::Minus(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}

/**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
double Minus::calculate(unordered_map<string, double> assignment) {
    return left->calculate(assignment) - right->calculate(assignment);
}

/**
 * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
 */
double Minus::calculate() {
    return left->calculate() - right->calculate();
}

/** Returns a new expression in which all occurrences of the variable
 * var are replaced with the provided expression (Does not modify the current expression).**/
Expression *Minus::assign(string var, Expression *expression) {
    return new Minus(left->assign(var, expression), right->assign(var, expression));
}


//Div

Div::Div(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}

/**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
double Div::calculate(unordered_map<string, double> assignment) {
    return left->calculate(assignment) / right->calculate(assignment);
}

/**
 * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
 */
double Div::calculate() {
    return left->calculate() / right->calculate();
}

/** Returns a new expression in which all occurrences of the variable
 * var are replaced with the provided expression (Does not modify the current expression).**/
Expression *Div::assign(string var, Expression *expression) {
    return new Div(left->assign(var, expression), right->assign(var, expression));
}


//Mult

Mult::Mult(Expression *left, Expression *right) {
    this->left = left;
    this->right = right;
}

/**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
double Mult::calculate(unordered_map<string, double> assignment) {
    return left->calculate(assignment) * right->calculate(assignment);
}

/**
 * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
 */
double Mult::calculate() {
    return left->calculate() * right->calculate();
}

/** Returns a new expression in which all occurrences of the variable
 * var are replaced with the provided expression (Does not modify the current expression).**/
Expression *Mult::assign(string var, Expression *expression) {
    return new Mult(left->assign(var, expression), right->assign(var, expression));
}
