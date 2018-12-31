#include <regex>
#include "OpenDataServerCommand.h"
#include "DataCommands.h"
#include "DataReaderServer.h"
#include "ExpressionUtils.h"
#include <pthread.h>

OpenDataServerCommand::OpenDataServerCommand(DataCommands *dataCommands, DataBinds *dataBinds, DataVars *dataVars,
                                             pthread_mutex_t &mutex) {
    this->dataCommands = dataCommands;
    this->dataBinds = dataBinds;
    this->dataVars = dataVars;
    this->mutex = mutex;
}

void OpenDataServerCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;

    ExpressionUtils expUtils;

    // get the port from the vector in dataCommands
    string portStr = this->dataCommands->getSeparated().at(index);
    // skip the port
    index++;
    int port = static_cast<int>(expUtils.calculateInfixStr(portStr, this->dataVars->getSymbolTable()));

    // get the perSec from the vector in dataCommands
    string perSecStr = this->dataCommands->getSeparated().at(index);
    // skip the perSec
    index++;
    int perSec = static_cast<int>(expUtils.calculateInfixStr(perSecStr, this->dataVars->getSymbolTable()));

    // create a struct of the thread params
    struct Params *params;
    params = new Params();
    this->deathMap2.push_back(params);

    DataReaderServer* temp;
    temp = new DataReaderServer(port, perSec, this->dataBinds, this->dataVars, this->mutex);
    // put values into the params
    params->dataReaderServer = temp;
    this->deathMap1.push_back(temp);

    pthread_t tId;
    // Launch a thread
    pthread_create(&tId, nullptr, openServer_thread_callback, params);

    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}

void *OpenDataServerCommand::openServer_thread_callback(void *params) {
    DataReaderServer *dataReaderServer;
    dataReaderServer = static_cast<Params *>(params)->dataReaderServer;
    dataReaderServer->openServer();
    delete static_cast<Params *>(params);
    return nullptr;
}
