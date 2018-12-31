#ifndef AP3_IFCOMMAND_H
#define AP3_IFCOMMAND_H


#include "Command.h"
#include "DataCommands.h"
#include "DataVars.h"
#include "ConditionParser.h"

class IfCommand : public Command {
private:
    DataCommands* dataCommands;
    DataVars* dataVars;
    vector<ConditionParser*> deathMap;
public:
    explicit IfCommand(DataCommands* dataCommands, DataVars* dataVars);

    virtual void doCommand();

    ~IfCommand(){
        auto it = this->deathMap.begin();
        while (it != this->deathMap.end()){
            delete *it;
            it++;
        }
    }
};

#endif //AP3_IFCOMMAND_H
