#ifndef AP3_PRINTCOMMAND_H
#define AP3_PRINTCOMMAND_H

#include "DataVars.h"
#include "DataCommands.h"

using namespace std;

class PrintCommand : public Command {
private:
    DataCommands* dataCommands;
    DataVars* dataVars;
public:
    explicit PrintCommand(DataCommands* dataCommands, DataVars* dataVars);
    virtual void doCommand();
};

#endif //AP3_PRINTCOMMAND_H
