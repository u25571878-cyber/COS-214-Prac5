#include "OperatorConsole.h"

using namespace std;

bool OperatorConsole::run(Command* c){
    if(c == nullptr)return false;

    c->execute();
    history.push_back(unique_ptr<Command>(c)); ///add it to the history
    return true;
}


bool OperatorConsole::cancelLast(){
    if (history.empty()) return false;

    history.back()->undo();

    history.pop_back();
    return true;
}

OperatorConsole::~OperatorConsole(){
    history.clear(); ///auto handles memory
}
