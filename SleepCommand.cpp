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
    // check the integrity of the numStr
    bool result = numIntegrityCheck(numStr);
    // if the check return false we throw an error
    if (!result) {
        throw "The numStr is invalid!";
    }
    ExpressionUtils expUtils;
    double num = expUtils.calculateInfixStr(numStr,dataVars->getSymbolTable());
    sleep(static_cast<unsigned int>(num));
    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}

bool SleepCommand::numIntegrityCheck(string &num) {

}
