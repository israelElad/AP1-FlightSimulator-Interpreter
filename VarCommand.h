#ifndef AP3_VARCOMMAND_H
#define AP3_VARCOMMAND_H

#include "Command.h"
#include "DataVars.h"
#include "DataCommands.h"

using namespace std;

class VarCommand : public Command {
private:
    DataCommands* dataCommands;
    DataVars* dataVars;
public:
    explicit VarCommand(DataCommands* dataCommands, DataVars* dataVars);

    virtual void doCommand();
};


#endif //AP3_VARCOMMAND_H
