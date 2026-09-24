#include "Mediator.h"

void FacilitiesTeam::handleNotice(){
    cout << " Facilities Team (" << getName() << ") received a system notice. Standing by to dispatch and provide facilities assistance." << endl;
}

bool FacilitiesTeam::dispatchTo(Incident* i){
    if (i == nullptr) return false;

    cout<<"Dispatching a Facilities team to the incident site INCIDENT ID: ("<< i->getID()<<")" <<endl;


    i->dispatch();

    if (mediator != nullptr) {
        mediator->unitDispatched(this, i);
    }

    return true;

}


bool FacilitiesTeam::recall(Incident* i){
    if (i == nullptr) return false;

    cout<<"Recalling the Facilities team from the incident site INCIDENT ID: ("<< i->getID()<<")" <<endl;
    i->cancel();
    return true;
}
