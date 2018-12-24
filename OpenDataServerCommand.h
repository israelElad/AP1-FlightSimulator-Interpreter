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
    DataBinds *dataBinds;
    DataVars *dataVars;
    pthread_mutex_t mutex;
    struct Params {
        DataReaderServer *dataReaderServer;
    };
public:
    explicit OpenDataServerCommand(DataCommands *dataCommands, DataBinds *dataBinds, DataVars *dataVars,
                                   pthread_mutex_t &mutex);

    virtual void doCommand();

    static void *openServer_thread_callback(void *dataReaderServerPtr);
};


#endif //MILESTONE_OPENDATASERVERCOMMAND_H