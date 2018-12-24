#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include "DataWriterClient.h"
#include "DataVars.h"
#include "DataBinds.h"

DataWriterClient::DataWriterClient(string &ip, int &port, DataBinds *dataBinds, DataVars *dataVars) {
    this->ip = ip;
    this->port = port;
    this->dataBinds = dataBinds;
    this->dataVars = dataVars;
}

void DataWriterClient::openClient() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr{};
    struct hostent *server;
    char buffer[1024];
    portno = this->port;

    // Create a socket point
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        return;
    }
    server = gethostbyname((this->ip).c_str());
    if (server == nullptr) {
        fprintf(stderr, "ERROR, no such host\n");
        return;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr, static_cast<size_t>(server->h_length));
    serv_addr.sin_port = htons(static_cast<uint16_t>(portno));

    // Now connect to the server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        return;
    }

    while (true) {
        // Now ask for a message from the user, this message will be read by server
        bzero(buffer, 1024);
        if (this->dataVars->getIsChanged()) {
            string varName = this->dataVars->getLastChanged();
            // Find the value of the var
            auto itSymbolTable = this->dataVars->getSymbolTable().find(varName);
            double varValue = itSymbolTable->second;
            // Find the name of the var according to how it appears in the simulator
            auto itBinds = this->dataBinds->getVarToNameInSimulator().find(varName);
            // Create an appropriate set command
            string setCommand = "set " + itBinds->second + " " + to_string(varValue);
            strcpy(buffer, setCommand.c_str());

            // Send message to the server
            n = static_cast<int>(write(sockfd, buffer, strlen(buffer)));
            if (n < 0) {
                perror("ERROR writing to socket");
                return;
            }
            this->dataVars->setIsChanged(false);
        }
    }
}
