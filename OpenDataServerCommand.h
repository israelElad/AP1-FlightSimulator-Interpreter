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
    vector<DataReaderServer*> deathMap1;
    vector<Params*> deathMap2;
public:
    explicit OpenDataServerCommand(DataCommands *dataCommands, DataBinds *dataBinds, DataVars *dataVars,
                                   pthread_mutex_t &mutex);

    virtual void doCommand();

    static void *openServer_thread_callback(void *dataReaderServerPtr);

    ~OpenDataServerCommand(){
        auto it1 = this->deathMap1.begin();
        while (it1 != this->deathMap1.end()){
            delete *it1;
            it1++;
        }
        auto it2 = this->deathMap2.begin();
        while (it2 != this->deathMap2.end()){
            delete *it2;
            it2++;
        }
        pthread_exit(nullptr);
    }
};

#endif //MILESTONE_OPENDATASERVERCOMMAND_H