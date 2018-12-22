#ifndef AP3_EQUALCOMMAND_H
#define AP3_EQUALCOMMAND_H

#include "DataCommands.h"
#include "Command.h"
#include "DataVars.h"

using namespace std;

class EqualCommand : public Command {
private:
    DataCommands* dataCommands;
    DataVars* dataVars;
public:
    explicit EqualCommand(DataCommands* dataCommands, DataVars* dataVars);

    virtual void doCommand();
};


#endif //AP3_EQUALCOMMAND_H
