#include "Mediator.h"

SecurityTeam:: SecurityTeam(ResponseMediator* m, string n, AccessController* ac): ResponseUnit(m, n), controller(ac) {}

void CommsService::handleNotice(){
    cout << " CommsService (" << getName() << ") received a system notice. Standing by to broadcast updates." << endl;
}

void CommsService::broadcast(Incident* i, string s){
     if (i == nullptr)
         return;

     cout << "Be advised of the following incident INCIDENT ID: (" << i->getID() <<")\nTYPE: ("
          << i->getType() <<")\nSEVERITY: ("<<
          i->getSeverity()<<")\n MESSAGE: ("<< s <<")"<<endl;
}

 void CommsService::retract(Incident* i){
     if (i == nullptr)
         return;

     cout << "Be advised of the following incident has been retracted INCIDENT ID: (" << i->getID() <<")"<<endl;
 }
