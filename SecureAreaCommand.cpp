#include "Command.h"

SecureAreaCommand::SecureAreaCommand(SecurityTeam* st, CampusArea* ca): securityTeam(st), campusArea(ca){}

bool SecureAreaCommand::execute() {
    if(securityTeam == nullptr || campusArea == nullptr) return false;

    securityTeam->secureArea(campusArea);
    cout<<"securing the area " <<endl;
    return true;
}

bool SecureAreaCommand::undo(){
    if(securityTeam == nullptr || campusArea == nullptr) return false;

    securityTeam->reopenArea(campusArea);
    cout<<"reopening the area " <<endl;
    return true;
}

string SecureAreaCommand::describe(){
    return "secure Area command object";
}
