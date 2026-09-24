#include "Mediator.h"

void MedicalTeam::handleNotice(){
    cout << " Medical Team (" << getName() << ") received a system notice. Standing by to dispatch and provide medical assistance." << endl;
}

bool MedicalTeam::dispatchTo(Incident* i){
    if (i == nullptr) return false;

    cout<<"Dispatching a medical team to the incident site INCIDENT ID: ("<< i->getID()<<")" <<endl;


    i->dispatch();

    if (mediator != nullptr) {
        mediator->unitDispatched(this, i);
    }

    return true;

}


bool MedicalTeam::recall(Incident* i){
    if (i == nullptr) return false;

    cout<<"Recalling the medical team from the incident site INCIDENT ID: ("<< i->getID()<<")" <<endl;
    i->cancel();
    return true;
}
