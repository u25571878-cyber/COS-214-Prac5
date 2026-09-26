#include "OperatorConsole.h"

using namespace std;

bool OperatorConsole::run(Command* c){
    if (c == nullptr) return false;

    unique_ptr<Command> cmd(c);
    if (!cmd->execute())
        return false;

    history.push_back(std::move(cmd));
    return true;

}


bool OperatorConsole::cancelLast(){
    if (history.empty()) return false;

    bool success = history.back()->undo();
    history.pop_back();

    return success;

}

OperatorConsole::~OperatorConsole(){
    history.clear(); ///auto handles memory
}
