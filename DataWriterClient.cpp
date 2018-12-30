#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "DataWriterClient.h"
#include "DataVars.h"
#include "DataBinds.h"

DataWriterClient::DataWriterClient(string &ip, int &port, DataBinds *dataBinds, DataVars *dataVars, pthread_mutex_t &mutex) {
    this->ip = ip;
    this->port = port;
    this->dataBinds = dataBinds;
    this->dataVars = dataVars;
    this->mutex = mutex;
}

void DataWriterClient::openClient() {
    cout<<"openning client"<<endl;
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
    server = gethostbyname(this->ip.c_str());
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
    cout<<"before if"<<endl;

    while (true) {
        if (this->dataVars->isChanged) {
            cout<<"entered if"<<endl;
            string varName = this->dataVars->getLastChanged().at(0);
            // delete first element
            this->dataVars->deleteFirstElementFromLastChanged();
            // lock
//            pthread_mutex_lock(&this->mutex);
            // Find the value of the var
            double varValue=0;
            if(this->dataBinds->getVarToNameInSimulator().count(varName)>=1) {
                varValue = this->dataVars->getSymbolTable().at(varName);
            }
            else{
                cout<<"error"<<endl;
            }
            // Find the name of the var according to how it appears in the simulator
            string bindStr;
            if(this->dataBinds->getVarToNameInSimulator().count(varName)==1){
                bindStr = this->dataBinds->getVarToNameInSimulator().at(varName);
            }
            //local variable- not found in binds
            if(bindStr.empty()){
                cout<<"bindStr empty"<<endl;
                continue;
            }
            // Create an appropriate set command
            bindStr=bindStr.substr(1,bindStr.length()-2);
            string setCommand = "set " + bindStr + " " + to_string(varValue) + "\r\n";
            bzero(buffer, 1024);

            strcpy(buffer, setCommand.c_str());

            cout<<buffer<<endl;

            // Send message to the server
            send(sockfd, buffer, strlen(buffer),0);

//            read(sockfd, buffer, strlen(buffer));
//            cout<<buffer<<endl;
//            pthread_mutex_unlock(&this->mutex);
        }
    }
}
//
//DataWriterClient::~DataWriterClient() {
//    close(sockfd);
//}
