#ifndef AP3_ENTERCCOMMAND_H
#define AP3_ENTERCCOMMAND_H


#include "Command.h"
#include "DataCommands.h"

class entercCommand : public Command {
private:
    DataCommands* dataCommands;
public:
    explicit entercCommand(DataCommands *dataCommands);
    virtual void doCommand();
};


#endif //AP3_ENTERCCOMMAND_H
