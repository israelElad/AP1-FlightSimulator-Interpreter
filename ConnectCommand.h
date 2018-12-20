#ifndef AP3_CONNECTCOMMAND_H
#define AP3_CONNECTCOMMAND_H

#include "Command.h"
#include "DataCommands.h"
#include "DataWriterClient.h"

using namespace std;

class ConnectCommand : public Command {
private:
    DataCommands* dataCommands;
    struct Params {
        string ip;
        int port;
        DataWriterClient* dataWriterClient;
    };
public:
    explicit ConnectCommand(DataCommands* dataCommands);

    virtual void doCommand();

    bool ipIntegrityCheck(string ip);

    bool portIntegrityCheck(string port);

    static void *openClient_thread_callback(void *params);
};


#endif //AP3_CONNECTCOMMAND_H
