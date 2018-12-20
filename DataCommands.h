#ifndef AP3_COMMANDSDATA_H
#define AP3_COMMANDSDATA_H

#include <string>
#include <vector>

using namespace std;

class DataCommands {
private:
    vector<string> separated;
    unsigned long index;
public:
    explicit DataCommands(vector<string> &separated);

    void setIndex(unsigned long index);

    const vector<string> &getSeparated();

    unsigned long getIndex();
};


#endif //AP3_COMMANDSDATA_H
