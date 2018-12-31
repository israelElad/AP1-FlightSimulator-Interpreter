#include <cstring>
#include <unistd.h>
#include "EqualCommand.h"
#include "DataVars.h"
#include "ExpressionUtils.h"

EqualCommand::EqualCommand(DataCommands *dataCommands, DataVars *dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

void EqualCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the =
    index++;

    // If bind doesn't appear after "="
    if (strcmp(this->dataCommands->getSeparated().at(index + 1).c_str(), "bind") != 0) {
        string varValueStr = this->dataCommands->getSeparated().at(index + 1);
        ExpressionUtils expUtils;
        double varValue = expUtils.calculateInfixStr(varValueStr, this->dataVars->getSymbolTable());
        string varName = this->dataCommands->getSeparated().at(index - 1);

        // Find the relevant var in the table and save its new value
        auto itSymbolTable = this->dataVars->getSymbolTable().find(varName);
        if (itSymbolTable == this->dataVars->getSymbolTable().end()) {
            throw "This var has not been declared before";
        }
        this->dataVars->setSymbolTableValue(varName, varValue);
        // update isChanged and lastChanged
        this->dataVars->addLastChanged(varName);
        index = index + 2;
        // set the new index of dataCommands
        this->dataCommands->setIndex(index);
    } else { // If bind appears after "="
        index++;
        // set the new index of dataCommands
        this->dataCommands->setIndex(index);
    }
}
