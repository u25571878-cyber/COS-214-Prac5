#include "Mediator.h"

SecurityTeam:: SecurityTeam(ResponseMediator* m, string n, AccessController* ac): ResponseUnit(m, n), controller(ac) {}

void SecurityTeam::handleNotice(){
    cout << " SecurityTeam (" << getName() << ") received a system notice. Standing by to dispatch and secure the area" << endl;
}


bool SecurityTeam::dispatchTo(Incident* i){
    if (i == nullptr) return false;

    cout<<"Dispatching a security team to the incident site INCIDENT ID: ("<< i->getID()<<")" <<endl;

    i->dispatch();

    if (mediator != nullptr) {
        mediator->unitDispatched(this, i);
    }

    return true;

}

bool SecurityTeam::recall(Incident* i){
    if (i == nullptr) return false;

    cout<<"Recalling the security team from the incident site INCIDENT ID: ("<< i->getID()<<")" <<endl;
    i->cancel();
    return true;
}

bool SecurityTeam::secureArea(CampusArea* a){
    if (a == nullptr) return false;

    cout<<"Securing the area: ("<< a->getName()<<")" <<endl;
    a->secure(controller);

    if (mediator != nullptr) {
        mediator->areaSecured(a, nullptr);
    }

    return true;
}

bool SecurityTeam::reOpenArea(CampusArea* a){
    if (a == nullptr) return false;

    cout<<"reOpening the area: ("<< a->getName()<<")" <<endl;
    a->reOpen(controller);///fix this
    return true;
}
