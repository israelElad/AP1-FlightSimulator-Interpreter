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
    pthread_mutex_t mutex;
    struct Params {
        DataWriterClient* dataWriterClient;
    };
    vector<DataWriterClient*> deathMap1;
    vector<Params*> deathMap2;
public:
    explicit ConnectCommand(DataCommands* dataCommands, DataBinds* dataBinds, DataVars* dataVars, pthread_mutex_t &mutex);

    virtual void doCommand();

    static void *openClient_thread_callback(void *params);

    ~ConnectCommand(){
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

#endif //AP3_CONNECTCOMMAND_H
