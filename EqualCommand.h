#ifndef AP3_EQUALCOMMAND_H
#define AP3_EQUALCOMMAND_H

#include "DataCommands.h"
#include "Command.h"

using namespace std;

class EqualCommand : public Command {
private:
    DataCommands* dataCommands;
public:
    explicit EqualCommand(DataCommands* dataCommands);

    virtual void doCommand();
};


#endif //AP3_EQUALCOMMAND_H
