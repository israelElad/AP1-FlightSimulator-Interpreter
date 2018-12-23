#include <regex>
#include <iostream>
#include "PrintCommand.h"
#include "DataVars.h"
#include "DataCommands.h"
#include "ExpressionUtils.h"

using namespace std;

PrintCommand::PrintCommand(DataCommands* dataCommands, DataVars* dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

void PrintCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // Set the appropriate regular expression
    string toPrint=this->dataCommands->getSeparated().at(index + 1);
    regex quote("\".*\"");
    // Returns true if the nameInSimulator matches the regular expression of quotes and returns false if not
    if(regex_match(toPrint, quote)){
        cout<<toPrint.substr(1, toPrint.size() - 2)<<endl;
    }
    else{ //print Expression
        ExpressionUtils expressionUtils;
        cout<<expressionUtils.calculateInfixStr(toPrint,dataVars->getSymbolTable())<<endl;
    }
    index += 2;
    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}
