#include "IfCommand.h"
#include "ConditionParser.h"

IfCommand::IfCommand(DataCommands *dataCommands, DataVars *dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

void IfCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;

    // get the left from the vector in dataCommands
    string left = this->dataCommands->getSeparated().at(index);
    // skip the left
    index++;

    // get the operator from the vector in dataCommands
    string oper = this->dataCommands->getSeparated().at(index);
    // skip the oper
    index++;

    // get the right from the vector in dataCommands
    string right = this->dataCommands->getSeparated().at(index);
    // skip the right
    index++;

    ConditionParser *conditionParser;
    conditionParser = new ConditionParser(left, oper, right, this->dataVars);
    if (conditionParser->checkCondition()) {

    }

    //TODO: index++ until we get to the }

    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}