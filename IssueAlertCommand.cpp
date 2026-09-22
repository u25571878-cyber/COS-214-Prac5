#include "Command.h"

IssueAlertCommand::IssueAlertCommand(CommsService* cs, Incident* i, string s):commsService(cs), incident(i), message(s){}

bool IssueAlertCommand::execute() {
    if(commsService == nullptr || incident == nullptr) return false;

    commsService->broadcast(incident, message);
    cout<<"broadcasting the message " <<endl;
    return true;
}

bool IssueAlertCommand::undo(){
    if(commsService == nullptr || incident == nullptr) return false;

    commsService->retract(incident);
    cout<<"retracting the incident" <<endl;
    return true;
}

string IssueAlertCommand::describe(){
    return "broadcasting the following message :" +  message;
}
