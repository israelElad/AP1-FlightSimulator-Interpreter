#include <regex>
#include "BindCommand.h"

BindCommand::BindCommand(DataCommands *dataCommands, DataBinds *dataBinds) {
    this->dataCommands = dataCommands;
    this->dataBinds = dataBinds;
}

void BindCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;
    // get the nameInSimulator from the vector in dataCommands
    string nameInSimulator = this->dataCommands->getSeparated().at(index);
    // skip the nameInSimulator
    index++;
    unsigned long indexOfVarName = this->dataCommands->getIndex() - 2;
    // get the varName from the vector in dataCommands
    string varName = this->dataCommands->getSeparated().at(indexOfVarName);
    // add to the varToNameInSimulator map
    this->dataBinds->addNewBind(nameInSimulator, varName);
    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}