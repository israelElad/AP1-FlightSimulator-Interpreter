#include "DataCommands.h"

DataCommands::DataCommands(vector<string> &separated) {
    this->index = 0;
    this->separated = separated;
}

unsigned long DataCommands::getIndex() {
    return index;
}

vector<string> DataCommands::getSeparated() {
    return separated;
}

void DataCommands::setIndex(unsigned long &index) {
    DataCommands::index = index;
}
