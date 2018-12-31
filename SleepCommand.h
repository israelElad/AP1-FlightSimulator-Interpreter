#ifndef AP3_SLEEPCOMMAND_H
#define AP3_SLEEPCOMMAND_H


#include "DataCommands.h"
#include "VarCommand.h"
#include "Command.h"

class SleepCommand : public Command {
private:
    DataCommands *dataCommands;
    DataVars *dataVars;
public:
    explicit SleepCommand(DataCommands *dataCommands, DataVars *dataVars);

    virtual void doCommand();
};

#endif //AP3_SLEEPCOMMAND_H
