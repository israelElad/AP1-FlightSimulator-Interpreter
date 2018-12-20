#ifndef AP3_IFCOMMAND_H
#define AP3_IFCOMMAND_H


#include "Command.h"
#include "DataCommands.h"

class IfCommand : public Command {
private:
    DataCommands* dataCommands;
public:
    explicit IfCommand(DataCommands* dataCommands);

    virtual void doCommand();
};


#endif //AP3_IFCOMMAND_H
