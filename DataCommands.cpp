#include "DataCommands.h"
#include "DataBinds.h"
#include "DataVars.h"
#include "OpenDataServerCommand.h"
#include "BindCommand.h"
#include "IfCommand.h"
#include "EqualCommand.h"
#include "WhileCommand.h"
#include "EntercCommand.h"
#include "VarCommand.h"
#include "ConnectCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

DataCommands::DataCommands(vector<string> &separated) {
    this->index = 0;
    this->separated = separated;

    DataVars *dataVars;
    dataVars = new DataVars();

    DataBinds *dataBinds;
    dataBinds = new DataBinds();

    pthread_mutex_init(&this->mutex, nullptr);

    this->stringsToCommands.insert(
            pair<string, Command *>("openDataServer", new OpenDataServerCommand(this, dataBinds, dataVars, mutex)));
    this->stringsToCommands.insert(
            pair<string, Command *>("connect", new ConnectCommand(this, dataBinds, dataVars, mutex)));
    this->stringsToCommands.insert(pair<string, Command *>("var", new VarCommand(this, dataVars)));
    this->stringsToCommands.insert(pair<string, Command *>("bind", new BindCommand(this, dataBinds)));
    this->stringsToCommands.insert(pair<string, Command *>("while", new WhileCommand(this, dataVars)));
    this->stringsToCommands.insert(pair<string, Command *>("if", new IfCommand(this, dataVars)));
    this->stringsToCommands.insert(pair<string, Command *>("print", new PrintCommand(this, dataVars)));
    this->stringsToCommands.insert(pair<string, Command *>("=", new EqualCommand(this, dataVars)));
    this->stringsToCommands.insert(pair<string, Command *>("enterc", new EntercCommand(this)));
    this->stringsToCommands.insert(pair<string, Command *>("sleep", new SleepCommand(this, dataVars)));
}

unsigned long DataCommands::getIndex() {
    return index;
}

vector<string> DataCommands::getSeparated() {
    return separated;
}

void DataCommands::setIndex(unsigned long index) {
    this->index = index;
}

unordered_map<string, Command *> DataCommands::getStringsToCommands() {
    return stringsToCommands;
}
