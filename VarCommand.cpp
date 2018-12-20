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
    // skip the name
    index++;
    // check the integrity of the name
    bool result = nameIntegrityCheck(name);
    // if the check return false we throw an error
    if (!result) {
        throw "The name is invalid!";
    }
    // else, we add the new var to the map in dataVars
    this->dataVars->addNewVar(name);
    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}

// The function checks the validity of the name it received
bool VarCommand::nameIntegrityCheck(string &name) {
    if (strcmp(name.c_str(), "var") == 0){
        return false;
    }
    // Set the appropriate regular expression
    regex b("[a-zA-Z_][a-zA-Z0-9]*");
    // Returns true if the name matches the regular expression and returns false if not
    return regex_match(name, b);
}
