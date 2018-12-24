#include <iostream>
#include "entercCommand.h"

using namespace std;

entercCommand::entercCommand() = default;

void entercCommand::doCommand() {
    fflush(stdin);
    char dummy;
    cin >> dummy;
    fflush(stdin);
}
