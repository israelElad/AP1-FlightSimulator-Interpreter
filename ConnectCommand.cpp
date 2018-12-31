#include <regex>
#include "ConnectCommand.h"
#include "DataCommands.h"
#include "DataWriterClient.h"
#include "ExpressionUtils.h"
#include <pthread.h>

ConnectCommand::ConnectCommand(DataCommands *dataCommands, DataBinds *dataBinds, DataVars *dataVars,
                               pthread_mutex_t &mutex) {
    this->dataCommands = dataCommands;
    this->dataBinds = dataBinds;
    this->dataVars = dataVars;
    this->mutex = mutex;
}

void ConnectCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;

    // get the ip from the vector in dataCommands
    string ip = this->dataCommands->getSeparated().at(index);
    // skip the ip
    index++;

    ExpressionUtils expUtils;

    // get the port from the vector in dataCommands
    string portStr = this->dataCommands->getSeparated().at(index);
    // skip the port
    index++;
    int port = static_cast<int>(expUtils.calculateInfixStr(portStr, this->dataVars->getSymbolTable()));

    // create a struct of the thread params
    struct Params *params;
    params = new Params();
    this->deathMap2.push_back(params);

    // put values into the params
    DataWriterClient* temp;
    temp = new DataWriterClient(ip, port, this->dataBinds, this->dataVars, this->mutex);
    params->dataWriterClient = temp;
    this->deathMap1.push_back(temp);

    pthread_t tId;
    // Launch a thread
    pthread_create(&tId, nullptr, openClient_thread_callback, params);
    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}

void *ConnectCommand::openClient_thread_callback(void *params) {
    DataWriterClient *dataWriterClient;
    dataWriterClient = static_cast<Params *>(params)->dataWriterClient;
    dataWriterClient->openClient();
    delete static_cast<Params *>(params);
    return nullptr;
}
