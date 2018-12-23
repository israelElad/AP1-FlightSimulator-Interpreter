//
// Created by elad on 23/12/18.
//

#ifndef AP3_COMMANDEXPRESSIONADAPTER_H
#define AP3_COMMANDEXPRESSIONADAPTER_H


#include "Expression.h"
#include "Command.h"

class CommandExpressionAdapter : Expression{
private:
    Command *command;
public:
    CommandExpressionAdapter(Command *command){
        this->command=command;
    }
    /**
 * Evaluate the expression using the variable values provided
 * in the assignment, and return the result.  If the expression
 * contains a variable which is not in the assignment, an exception is thrown.
 * */
    virtual double calculate(unordered_map<string, double> assignment){
        command->doCommand();
    }

    /**
    * A convenience method. Like the `evaluate(assignment)` method above, but uses an empty assignment.
    */
    virtual double calculate(){
        command->doCommand();
    }


    /** Returns a new expression in which all occurrences of the variable
     * var are replaced with the provided expression (Does not modify the current expression).**/
    virtual Expression *assign(string var, Expression *expression){
        return nullptr;
    }
};


#endif //AP3_COMMANDEXPRESSIONADAPTER_H
