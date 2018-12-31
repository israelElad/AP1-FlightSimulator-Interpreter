#include <cstring>
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
    this->deathMap.push_back(conditionParser);
    unordered_map<string, Command *> stringsToCommands = dataCommands->getStringsToCommands();
    unsigned long oldIndex = index;
    bool isEntered = false;
    while (conditionParser->checkCondition()) {
        isEntered = true;
        index = oldIndex;
        // set the new index of dataCommands
        this->dataCommands->setIndex(oldIndex);
        vector<string> separetedCopy=this->dataCommands->getSeparated();
        auto it1 = separetedCopy.begin();
        it1 += index;
        Command *command;
        int bracesCounter = 0;
        do {
            string currentComStr=separetedCopy.at(index);
            if (currentComStr.find('{') != string::npos) {
                bracesCounter++;
                index++;
                it1++;
                // set the new index of dataCommands
                this->dataCommands->setIndex(index);
                continue;
            } else if (currentComStr.find('}') != string::npos) {
                bracesCounter--;
                index++;
                // set the new index of dataCommands
                this->dataCommands->setIndex(index);
                continue;
            }
            if(stringsToCommands.count(*it1)>=1) {
                command = stringsToCommands.at(*it1);
                command->doCommand();
            }
            else{
                it1++;
                continue;
            }

            index = this->dataCommands->getIndex();
            it1 = separetedCopy.begin();
            it1 += index;

        } while (bracesCounter != 0);
        conditionParser = new ConditionParser(left, oper, right, this->dataVars);
        this->deathMap.push_back(conditionParser);
    }
    if (!isEntered) {
        //right now at '{'. index++ until we get to the last '}'
        int bracesSkipCount = 0;
        do{
            if (this->dataCommands->getSeparated().at(index).find('{') != string::npos) {
                bracesSkipCount++;
            }else if (this->dataCommands->getSeparated().at(index).find('}') != string::npos) {
                bracesSkipCount--;
            }
            index++;
        }while (bracesSkipCount > 0);
    }

    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}
