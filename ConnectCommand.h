#ifndef AP3_CONNECTCOMMAND_H
#define AP3_CONNECTCOMMAND_H

#include "Command.h"
#include "DataCommands.h"
#include "DataWriterClient.h"

using namespace std;

class ConnectCommand : public Command {
private:
    DataCommands* dataCommands;
    DataBinds* dataBinds;
    DataVars* dataVars;
    struct Params {
        DataWriterClient* dataWriterClient;
    };
public:
    explicit ConnectCommand(DataCommands* dataCommands, DataBinds* dataBinds, DataVars* dataVars);

    virtual void doCommand();

    static void *openClient_thread_callback(void *params);
};


#endif //AP3_CONNECTCOMMAND_H
