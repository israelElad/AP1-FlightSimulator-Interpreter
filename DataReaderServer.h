#ifndef MILESTONE_DATAREADERSERVER_H
#define MILESTONE_DATAREADERSERVER_H

#include "DataBinds.h"
#include "DataVars.h"

class DataReaderServer {
private:
    int port;
    int perSec;
    DataBinds *dataBinds;
    DataVars *dataVars;
    pthread_mutex_t mutex;


public:
    DataReaderServer(int &port, int &perSec, DataBinds *dataBinds, DataVars *dataVars, pthread_mutex_t &mutex);
    void openServer();
};


#endif //MILESTONE_DATAREADERSERVER_H