#include <regex>
#include "OpenDataServerCommand.h"
#include "DataCommands.h"
#include "DataReaderServer.h"
#include <pthread.h>

OpenDataServerCommand::OpenDataServerCommand(DataCommands *dataCommands, DataBinds *dataBinds, DataVars* dataVars) {
    this->dataCommands = dataCommands;
    this->dataBinds = dataBinds;
    this->dataVars = dataVars;
}

void OpenDataServerCommand::doCommand() {
    // get the index from dataCommands
    unsigned long index = this->dataCommands->getIndex();
    // skip the command
    index++;

    // get the port from the vector in dataCommands
    string portStr = this->dataCommands->getSeparated().at(index);
    // skip the port
    index++;
    // check the integrity of the port
    bool result = portOrPerSecIntegrityCheck(portStr);
    // if the check return false we throw an error
    if (!result) {
        throw "The port is invalid!";
    }
    int port = stoi(portStr);

    // get the perSec from the vector in dataCommands
    string perSecStr = this->dataCommands->getSeparated().at(index);
    // skip the perSec
    index++;
    // check the integrity of the perSec
    result = portOrPerSecIntegrityCheck(perSecStr);
    // if the check return false we throw an error
    if (!result) {
        throw "The perSec is invalid!";
    }
    int perSec = stoi(perSecStr);

    // create a struct of the thread params
    struct Params *params;
    params = new Params();
    // put values into the params
    params->dataReaderServer = new DataReaderServer(port, perSec, this->dataBinds, this->dataVars);

    pthread_t tId;
    // Launch a thread
    pthread_create(&tId, nullptr, openServer_thread_callback, params);
    // Join the thread with the main thread
    //pthread_join(tId, nullptr);

    // set the new index of dataCommands
    this->dataCommands->setIndex(index);
}

// The function checks the validity of the port or perSec it received
bool OpenDataServerCommand::portOrPerSecIntegrityCheck(string &portOrPerSec) {
    // Set the appropriate regular expression
    regex b("[0-9]*");
    // Returns true if the port/perSec matches the regular expression and returns false if not
    return regex_match(portOrPerSec, b);
}

void *OpenDataServerCommand::openServer_thread_callback(void *params) {
    DataReaderServer *dataReaderServer;
    dataReaderServer = static_cast<Params *>(params)->dataReaderServer;
    dataReaderServer->openServer();
    delete static_cast<Params *>(params);
    return nullptr;
}
