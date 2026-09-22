#ifndef OPERATORCONSOLE_H
#define OPERATORCONSOLE_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>


#include "Command.h"

using namespace std;


class OperatorConsole {
    private:
        vector<unique_ptr<Command>> history;
    public:
        bool run(Command* c);
        bool cancelLast();
        ~OperatorConsole();
};

#endif
