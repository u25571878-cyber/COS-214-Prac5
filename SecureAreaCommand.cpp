#include "Command.h"

SecureAreaCommand::SecureAreaCommand(SecurityTeam* st, CampusArea* ca): securityTeam(st), campusArea(ca){}

bool SecureAreaCommand::execute() {
    if(securityTeam == nullptr || campusArea == nullptr) return false;

    bool success = securityTeam->secureArea(campusArea);
    if (success) {
        cout << "securing the area" << endl;
    }
    return success;
}

bool SecureAreaCommand::undo(){
    if(securityTeam == nullptr || campusArea == nullptr) return false;

    bool success = securityTeam->reOpenArea(campusArea);
    if (success) {
        cout << "reopening the area" << endl;
    }
    return success;
}

string SecureAreaCommand::describe(){
    return "secure Area command object";
}
