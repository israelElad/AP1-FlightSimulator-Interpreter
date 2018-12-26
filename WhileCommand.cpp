#include "WhileCommand.h"
#include "DataCommands.h"
#include "DataVars.h"
#include "ConditionParser.h"

WhileCommand::WhileCommand(DataCommands *dataCommands, DataVars *dataVars) {
    this->dataCommands = dataCommands;
    this->dataVars = dataVars;
}

void WhileCommand::doCommand() {
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
    unordered_map<string, Command *> stringsToCommands = dataCommands->getStringsToCommands();
    unsigned long oldIndex = index;

    while (conditionParser->checkCondition()) {
        index = oldIndex;
        auto it1 = this->dataCommands->getSeparated().begin();
        it1 += index;
        Command *command;
        while (*it1 != "}") {
            auto it2 = stringsToCommands.find(*it1);
            if (it2 == stringsToCommands.end()) {
                it1++;
                continue;
            }
            command = it2->second;
            command->doCommand();
            it1++;
        }
        // set the new index of dataCommands
        this->dataCommands->setIndex(oldIndex);
    }

    //TODO: index++ until we get to the }

    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}
