#include <string>
#include <unordered_map>
#include <list>

#ifndef MILESTONE_EXPRESSION_H
#define MILESTONE_EXPRESSION_H

#endif //MILESTONE_EXPRESSION_H

using namespace std;

class Expression {
public:
    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.  If the expression
     * contains a variable which is not in the assignment, an exception is thrown.
     * */
    virtual double calculate(unordered_map<string, double> assignment) = 0;

    /**
    * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
    */
    virtual double calculate() = 0;


    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression) = 0;

    virtual ~Expression(){};
};



class Plus:public Expression{
private:
    Expression *left;
    Expression *right;
public:
    Plus(Expression *left, Expression *right);

    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.  If the expression
     * contains a variable which is not in the assignment, an exception is thrown.
     * */
    virtual double calculate(unordered_map<string, double> assignment);

    /**
     * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
     */
    virtual double calculate();

    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression);
    ~Plus(){
    }
};

class Num:public Expression{
private:
    double num;
public:
    Num(double num);

    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.  If the expression
     * contains a variable which is not in the assignment, an exception is thrown.
     * */
    virtual double calculate(unordered_map<string, double> assignment);

    /**
    * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
    */
    virtual double calculate();

    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression);
    ~Num(){

    }
};

class Var:public Expression{
private:
    string var;
public:
    Var(string var);

    /**
      * Evaluate the expression using the variable values provided
      * in the assignment, and return the result.  If the expression
      * contains a variable which is not in the assignment, an exception is thrown.
      * */
    virtual double calculate(unordered_map<string, double> assignment);

    /**
    * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
    */
    virtual double calculate();

    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression);
    ~Var(){

    }
};


class Neg:public Expression{
private:
    Expression *exp;
public:
    Neg(Expression *exp);

    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.  If the expression
     * contains a variable which is not in the assignment, an exception is thrown.
     * */
    virtual double calculate(unordered_map<string, double> assignment);

    /**
    * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
    */
    virtual double calculate();

    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression);
    ~Neg(){

    }
};


class Minus:public Expression{
private:
    Expression *left;
    Expression *right;
public:
    Minus(Expression *left, Expression *right);

    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.  If the expression
     * contains a variable which is not in the assignment, an exception is thrown.
     * */
    virtual double calculate(unordered_map<string, double> assignment);

    /**
     * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
     */
    virtual double calculate();

    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression);
    ~Minus(){

    }
};


class Div:public Expression{
private:
    Expression *left;
    Expression *right;
public:
    Div(Expression *left, Expression *right);

    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.  If the expression
     * contains a variable which is not in the assignment, an exception is thrown.
     * */
    virtual double calculate(unordered_map<string, double> assignment);

    /**
     * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
     */
    virtual double calculate();

    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression);
};

class Mult:public Expression{
private:
    Expression *left;
    Expression *right;
public:
    Mult(Expression *left, Expression *right);

    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.  If the expression
     * contains a variable which is not in the assignment, an exception is thrown.
     * */
    virtual double calculate(unordered_map<string, double> assignment);

    /**
     * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
     */
    virtual double calculate();

    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression);
};