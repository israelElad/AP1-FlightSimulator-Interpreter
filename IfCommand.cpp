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
    unordered_map<string, Command *> stringsToCommands = dataCommands->getStringsToCommands();
    unsigned long oldIndex = index;


    if (conditionParser->checkCondition()) {

        index = oldIndex;
        // set the new index of dataCommands
        this->dataCommands->setIndex(oldIndex);

        auto it1 = this->dataCommands->getSeparated().begin();
        it1 += index;
        Command *command;
        int bracesCounter = 0;
        do {
            if (this->dataCommands->getSeparated().at(index).find('{') != string::npos) {
                bracesCounter++;
                index++;
                it1++;
                // set the new index of dataCommands
                this->dataCommands->setIndex(index);
            } else if (this->dataCommands->getSeparated().at(index).find('}') != string::npos) {
                bracesCounter--;
                index++;
                it1++;
                // set the new index of dataCommands
                this->dataCommands->setIndex(index);
            }
            auto it2 = stringsToCommands.find(*it1);
            if (it2 == stringsToCommands.end()) {
                it1++;
                continue;
            }
            command = it2->second;
            command->doCommand();
            it1 += (this->dataCommands->getIndex() - index);
            index = this->dataCommands->getIndex();
        } while (bracesCounter != 0);
    }

    //TODO: index++ until we get to the }

    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}