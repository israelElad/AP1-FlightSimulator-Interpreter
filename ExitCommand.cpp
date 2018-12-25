#include "ExitCommand.h"

ExitCommand::ExitCommand(bool *shouldStop) {
    this->shouldStop = shouldStop;
}

void ExitCommand::doCommand() {
    *(this->shouldStop) = true;
}
