#include <cstring>
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

    // If bind appears after "=" - do not do anything, otherwise ...
    if (strcmp(this->dataCommands->getSeparated().at(index + 1).c_str(), "bind") != 0) {
        string varValueStr = this->dataCommands->getSeparated().at(index + 1);
        ExpressionUtils expUtils;
        double varValue = expUtils.calculateInfixStr(varValueStr, dataVars->getSymbolTable());
        string varName = this->dataCommands->getSeparated().at(index - 1);

        // Find the relevant var in the table and save its new value
        auto itSymbolTable = this->dataVars->getSymbolTable().find(varName);
        if (itSymbolTable == this->dataVars->getSymbolTable().end()) {
            throw "This var has not been declared before";
        }
        itSymbolTable->second = varValue;

        // update isChanged and lastChanged
        this->dataVars->setIsChanged(true);
        this->dataVars->setLastChanged(varName);

        index += 2;
        // set the new index of dataCommands
        this->dataCommands->setIndex(index);
    }
}
