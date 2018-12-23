#ifndef AP3_BINDCOMMAND_H
#define AP3_BINDCOMMAND_H

#include <unordered_map>
#include "Command.h"
#include "DataCommands.h"
#include "DataBinds.h"

using namespace std;

class BindCommand : public Command {
private:
    DataCommands* dataCommands;
    DataBinds* dataBinds;
public:
    explicit BindCommand(DataCommands* dataCommands, DataBinds* dataBinds);

    virtual void doCommand();
};

#endif //AP3_BINDCOMMAND_H
