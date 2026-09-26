#include "Command.h"

DispatchUnitCommand::DispatchUnitCommand(ResponseUnit* du, Incident* i): responseUnit(du), incident(i){}

bool DispatchUnitCommand::execute() {
    if(responseUnit == nullptr || incident == nullptr ) return false;

    bool success = responseUnit->dispatchTo(incident);
    if (success) {
        cout << "dispatching responseUnit" << endl;
    }
    return success;
}

bool DispatchUnitCommand::undo(){
    if(responseUnit == nullptr || incident == nullptr ) return false;

    bool success = responseUnit->recall(incident);
    if (success) {
        cout << "recalling the response unit" << endl;
    }
    return success;
}

string DispatchUnitCommand::describe(){
    return "Dispatch unit command object";
}
