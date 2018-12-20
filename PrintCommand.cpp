#include "PrintCommand.h"
#include "DataVars.h"
#include "DataCommands.h"

PrintCommand::PrintCommand(DataCommands* dataCommands, DataVars* dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

void PrintCommand::doCommand() {

}
