#ifndef AP3_COMMANDSDATA_H
#define AP3_COMMANDSDATA_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Command.h"

using namespace std;

class DataCommands {
private:
    vector<string> separated;
    unsigned long index;
    unordered_map<string, Command *> stringsToCommands;
    pthread_mutex_t mutex;

public:
    unordered_map<string, Command *> getStringsToCommands();

    explicit DataCommands(vector<string> &separated);

    void setIndex(unsigned long index);

    vector<string> getSeparated();

    unsigned long getIndex();

    ~DataCommands() {
        pthread_mutex_destroy(&this->mutex);
    }
};

#endif //AP3_COMMANDSDATA_H
