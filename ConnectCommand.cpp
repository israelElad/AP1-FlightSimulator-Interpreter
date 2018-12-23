#include <regex>
#include "ConnectCommand.h"
#include "DataCommands.h"
#include "DataWriterClient.h"
#include <pthread.h>

ConnectCommand::ConnectCommand(DataCommands *dataCommands, DataBinds* dataBinds, DataVars* dataVars) {
    this->dataCommands = dataCommands;
    this->dataBinds = dataBinds;
    this->dataVars = dataVars;
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
    // get the port from the vector in dataCommands
    string portStr = this->dataCommands->getSeparated().at(index);
    // skip the port
    index++;
    int port = stoi(portStr);

    // create a struct of the thread params
    struct Params *params;
    params = new Params();
    // put values into the params
    params->dataWriterClient = new DataWriterClient(ip, port, this->dataBinds, this->dataVars);

    pthread_t tId;
    // Launch a thread
    pthread_create(&tId, nullptr, openClient_thread_callback, params);
    // Join the thread with the main thread
    pthread_join(tId, nullptr);


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
