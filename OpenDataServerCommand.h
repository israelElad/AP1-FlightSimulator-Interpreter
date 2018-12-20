#ifndef MILESTONE_OPENDATASERVERCOMMAND_H
#define MILESTONE_OPENDATASERVERCOMMAND_H

#include "DataCommands.h"
#include "DataReaderServer.h"
#include "Command.h"
#include "DataBinds.h"
#include "DataVars.h"

using namespace std;

class OpenDataServerCommand : public Command {
private:
    DataCommands *dataCommands;
    DataBinds* dataBinds;
    DataVars* dataVars;
    struct Params {
        DataReaderServer* dataReaderServer;
    };
public:
    explicit OpenDataServerCommand(DataCommands *dataCommands, DataBinds* dataBinds, DataVars* dataVars);

    virtual void doCommand();

    bool portOrPerSecIntegrityCheck(string &portOrPerSec);

    static void *openServer_thread_callback(void *dataReaderServerPtr);
};


#endif //MILESTONE_OPENDATASERVERCOMMAND_H