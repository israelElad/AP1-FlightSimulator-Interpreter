#ifndef AP3_COMMAND_H
#define AP3_COMMAND_H

using namespace std;

class Command {
public:
    virtual void doCommand() = 0;
};

#endif //AP3_COMMAND_H