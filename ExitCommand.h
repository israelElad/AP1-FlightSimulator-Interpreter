#ifndef AP3_EXITCOMMAND_H
#define AP3_EXITCOMMAND_H

#include "Command.h"

class ExitCommand : public Command {
private:
    bool shouldStop;
public:
    explicit ExitCommand(bool &shouldStop);

    virtual void doCommand();
};


#endif //AP3_EXITCOMMAND_H
