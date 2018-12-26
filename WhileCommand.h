#ifndef AP3_WHILECOMMAND_H
#define AP3_WHILECOMMAND_H

#include "DataCommands.h"
#include "Command.h"
#include "DataVars.h"

using namespace std;

class WhileCommand : public Command {
private:
    DataCommands* dataCommands;
public:
    explicit WhileCommand(DataCommands *dataCommands, DataVars *dataVars);

    virtual void doCommand();
};


#endif //AP3_WHILECOMMAND_H
