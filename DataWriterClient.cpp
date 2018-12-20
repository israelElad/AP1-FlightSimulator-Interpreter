#include <netinet/in.h>
#include <string>
#include <netdb.h>
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include "DataWriterClient.h"

DataWriterClient::DataWriterClient(string &ip, int &port) {
    this->ip = ip;
    this->port = port;
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
        fprintf(stderr,"ERROR, no such host\n");
        return;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *)&serv_addr.sin_addr.s_addr, static_cast<size_t>(server->h_length));
    serv_addr.sin_port = htons(static_cast<uint16_t>(portno));

    // Now connect to the server
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        return;
    }

    while (true) {
        // Now ask for a message from the user, this message will be read by server
        bzero(buffer, 1024);
        fgets(buffer, 1024, stdin);

        // Send message to the server
        n = static_cast<int>(write(sockfd, buffer, strlen(buffer)));

        if (n < 0) {
            perror("ERROR writing to socket");
            return;
        }
    }
}
