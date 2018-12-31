#include <netinet/in.h>
#include <cstdio>
#include <strings.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstring>
#include "DataReaderServer.h"
#include "DataBinds.h"

using namespace std;

DataReaderServer::DataReaderServer(int &port, int &perSec, DataBinds *dataBinds, DataVars *dataVars, pthread_mutex_t &mutex) {
    this->perSec = perSec;
    this->port = port;
    this->dataBinds = dataBinds;
    this->dataVars = dataVars;
    this->mutex = mutex;
}

void DataReaderServer::openServer() {
    int socketFd, newSockFd, clientLen;
    char buffer[1024];
    struct sockaddr_in serv_addr{}, cli_addr{};
    int n;
    // First call to socket() function
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0) {
        perror("ERROR opening socket");
        return;
    }
    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(static_cast<uint16_t>(this->port));
    // Now bind the host address using bind() call
    if (bind(socketFd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        return;
    }

    /* Now start listening for the clients, here process will go in sleep mode and
     * will wait for the incoming connection */
    listen(socketFd, 5);
    clientLen = sizeof(cli_addr);
    // Accept actual connection from the client
    newSockFd = accept(socketFd, (struct sockaddr *) &cli_addr, (socklen_t *) &clientLen);
    if (newSockFd < 0) {
        perror("ERROR on accept");
        return;
    }
    // Create a vector arranged in order of variables in the XML file
    vector<string> xmlVariables = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
                                   "/instrumentation/altimeter/indicated-altitude-ft",
                                   "/instrumentation/altimeter/pressure-alt-ft",
                                   "/instrumentation/attitude-indicator/indicated-pitch-deg",
                                   "/instrumentation/attitude-indicator/indicated-roll-deg",
                                   "/instrumentation/attitude-indicator/internal-pitch-deg",
                                   "/instrumentation/attitude-indicator/internal-roll-deg",
                                   "/instrumentation/encoder/indicated-altitude-ft",
                                   "/instrumentation/encoder/pressure-alt-ft",
                                   "/instrumentation/gps/indicated-altitude-ft",
                                   "/instrumentation/gps/indicated-ground-speed-kt",
                                   "/instrumentation/gps/indicated-vertical-speed",
                                   "/instrumentation/heading-indicator/indicated-heading-deg",
                                   "/instrumentation/magnetic-compass/indicated-heading-deg",
                                   "/instrumentation/slip-skid-ball/indicated-slip-skid",
                                   "/instrumentation/turn-indicator/indicated-turn-rate",
                                   "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                                   "/controls/flight/aileron",
                                   "/controls/flight/elevator",
                                   "/controls/flight/rudder",
                                   "/controls/flight/flaps",
                                   "/controls/engines/current-engine/throttle",
                                   "/engines/engine/rpm"};
    string dataFromSimulator;
    while (true) {

        char c = 'n';
        int idx = 0;
        while (c != '\n')   {
            n = static_cast<int>(read(newSockFd, &c, 1));
            if (n < 0) {
                perror("ERROR reading from socket");
                return;
            }   else if (n == 0)    {
                perror("Socket is closed");
                return;
            }
            buffer[idx++] = c;
        }
        buffer[idx] = 0;


        // put the data in vector
        dataFromSimulator = buffer;
        replace(dataFromSimulator.begin(), dataFromSimulator.end(), ',', ' '); // replace ' , ' by ' '
        vector<double> dataValues;
        stringstream ss(dataFromSimulator);
        double temp;
        while (ss >> temp) {
            dataValues.push_back(temp);
        }
        // Replaces any vector name found on the Bind map in the name of Var
        vector<string> xmlVariablesCopy = xmlVariables;
        auto itXml1 = xmlVariablesCopy.begin();
        while (itXml1 != xmlVariablesCopy.end()) {
            for (auto &itBinds : this->dataBinds->getVarToNameInSimulator()) {
                string bindPath=itBinds.second;
                bindPath=bindPath.substr(1,bindPath.length()-2);
                if (strcmp(bindPath.c_str(), (*itXml1).c_str())== 0) {
                    *itXml1 = itBinds.first;
                }
            }
            itXml1++;
        }
        pthread_mutex_lock(&this->mutex);
        // Updating the symbolTable according to the values ​​received
        auto itXml2 = xmlVariablesCopy.begin();
        auto itValues = dataValues.begin();
        while (itXml2 != xmlVariablesCopy.end()) {
            if(this->dataVars->getSymbolTable().count(*itXml2)>=1){
                this->dataVars->setSymbolTableValue(*itXml2, *itValues);
            }
            itXml2++;
            itValues++;
        }
        pthread_mutex_unlock(&this->mutex);
    }
}