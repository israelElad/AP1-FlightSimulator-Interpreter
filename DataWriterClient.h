#ifndef AP3_DATAWRITERCLIENT_H
#define AP3_DATAWRITERCLIENT_H

using namespace std;

class DataWriterClient {
private:
    string ip;
    int port;

public:
    DataWriterClient(string &ip, int &port);

    void openClient();
};


#endif //AP3_DATAWRITERCLIENT_H
