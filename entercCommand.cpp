#include <iostream>
#include "entercCommand.h"
#include "DataCommands.h"

using namespace std;

entercCommand::entercCommand(DataCommands *dataCommands){
    this->dataCommands = dataCommands;
}

void entercCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;

    fflush(stdin);
    char dummy;
    cin >> dummy;
    fflush(stdin);

    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}
