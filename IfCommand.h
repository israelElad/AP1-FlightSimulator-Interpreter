#ifndef AP3_IFCOMMAND_H
#define AP3_IFCOMMAND_H


#include "Command.h"
#include "DataCommands.h"
#include "DataVars.h"

class IfCommand : public Command {
private:
    DataCommands* dataCommands;
    DataVars* dataVars;
public:
    explicit IfCommand(DataCommands* dataCommands, DataVars* dataVars);

    virtual void doCommand();
};


#endif //AP3_IFCOMMAND_H
