#ifndef AP3_WHILECOMMAND_H
#define AP3_WHILECOMMAND_H

#include "DataCommands.h"
#include "Command.h"
#include "DataVars.h"
#include "ConditionParser.h"

using namespace std;

class WhileCommand : public Command {
private:
    DataCommands* dataCommands;
    DataVars* dataVars;
    vector<ConditionParser*> deathMap;
public:
    explicit WhileCommand(DataCommands *dataCommands, DataVars *dataVars);

    virtual void doCommand();

    ~WhileCommand(){
        auto it = this->deathMap.begin();
        while (it != this->deathMap.end()){
            delete *it;
            it++;
        }

    }
};

#endif //AP3_WHILECOMMAND_H
