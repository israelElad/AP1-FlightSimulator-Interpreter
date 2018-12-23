#include "PrintCommand.h"
#include "DataVars.h"
#include "DataCommands.h"

PrintCommand::PrintCommand(DataCommands* dataCommands, DataVars* dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

void PrintCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    if(this->dataCommands->getSeparated().at(index + 1).c_str()){

    }
}
