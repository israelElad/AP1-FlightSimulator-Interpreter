#ifndef AP3_DATAWRITERCLIENT_H
#define AP3_DATAWRITERCLIENT_H

#include "DataBinds.h"
#include "DataVars.h"

using namespace std;

class DataWriterClient {
private:
    string ip;
    int port;
    DataBinds *dataBinds;
    DataVars *dataVars;
    pthread_mutex_t mutex;

public:
    DataWriterClient(string &ip, int &port, DataBinds *dataBinds, DataVars *dataVars, pthread_mutex_t &mutex);

    void openClient();
};


#endif //AP3_DATAWRITERCLIENT_H
