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
    // check the integrity of the ip
    bool result = ipIntegrityCheck(ip);
    // if the check return false we throw an error
    if (!result) {
        throw "The ip is invalid!";
    }

    // get the port from the vector in dataCommands
    string portStr = this->dataCommands->getSeparated().at(index);
    // skip the port
    index++;
    // check the integrity of the port
    result = portIntegrityCheck(portStr);
    // if the check return false we throw an error
    if (!result) {
        throw "The port is invalid!";
    }
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

// The function checks the validity of the ip it received
bool ConnectCommand::ipIntegrityCheck(string ip) {
    // Set the appropriate regular expression
    regex b("([0-9]+\\.){3}[0-9]+");
    // Returns true if the ip matches the regular expression and returns false if not
    return regex_match(ip, b);
}

// The function checks the validity of the port it received
bool ConnectCommand::portIntegrityCheck(string port) {
    // Set the appropriate regular expression
    regex b("[0-9]*");
    // Returns true if the port matches the regular expression and returns false if not
    return regex_match(port, b);
}

void *ConnectCommand::openClient_thread_callback(void *params) {
    DataWriterClient *dataWriterClient;
    dataWriterClient = static_cast<Params *>(params)->dataWriterClient;
    dataWriterClient->openClient();
    delete static_cast<Params *>(params);
    return nullptr;
}
