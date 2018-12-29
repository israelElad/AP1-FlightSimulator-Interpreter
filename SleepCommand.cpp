#include <unistd.h>
#include "SleepCommand.h"
#include "ExpressionUtils.h"

SleepCommand::SleepCommand(DataCommands *dataCommands, DataVars *dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

void SleepCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;
    // get the numStr from the vector in dataCommands
    string numStr = this->dataCommands->getSeparated().at(index);
    // skip the numStr
    index++;
    ExpressionUtils expUtils;
    double num = expUtils.calculateInfixStr(numStr,dataVars->getSymbolTable());
    if(num<1000){
        num=1000;
    }
    sleep(num /1000);
    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}
