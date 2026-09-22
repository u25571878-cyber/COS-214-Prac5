#include "Command.h"

DispatchUnitCommand::DispatchUnitCommand(ResponseUnit* du, Incident* i): responseUnit(du), incident(i){}

bool DispatchUnitCommand::execute() {
    if(responseUnit == nullptr || incident == nullptr ) return false;

    responseUnit->dispatchTo(incident);
    cout<<"dispatching responseUnit"<<endl;
    return true;
}

bool DispatchUnitCommand::undo(){
    if(responseUnit == nullptr || incident == nullptr ) return false;

    responseUnit->recall(incident);
    cout<<"recalling the response unit" <<endl;
    return true;
}

string DispatchUnitCommand::describe(){
    return "Dispatch unit command object";
}
