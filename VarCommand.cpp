#include <cstring>
#include <regex>
#include "VarCommand.h"
#include "DataVars.h"
#include "DataCommands.h"

VarCommand::VarCommand(DataCommands *dataCommands, DataVars *dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

// The function defines a new variable and adds it with a value of 0 to the symbolTable
void VarCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;
    // get the name from the vector in dataCommands
    string name = this->dataCommands->getSeparated().at(index);
    // else, we add the new var to the map in dataVars
    this->dataVars->addNewVar(name);
    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}
