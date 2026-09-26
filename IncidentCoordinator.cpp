#include "Mediator.h"

void IncidentCoordinator::addComponent(ResponseComponent* rc){
    if (rc == nullptr) return;

    colleagues.push_back(rc);
}

void IncidentCoordinator::unitDispatched(ResponseUnit* ru, Incident* i){
    if (i == nullptr || ru == nullptr) return;
    cout << "unit "<< ru->getName() <<" has been dispatched"<<endl;

    for(ResponseComponent* rs : colleagues){
        if(rs == ru) continue;

        rs->handleNotice();
    }

}

void IncidentCoordinator::escalated(Incident* i){
    if (i == nullptr) return;

    cout<<"Incident has been escalated"<<endl;


    for(ResponseComponent* rs : colleagues){
        rs->handleNotice();
    }

}


void IncidentCoordinator::areaSecured(CampusArea* ca, Incident* i){
    if (ca == nullptr ) return;

    cout<<"Campus Area has been secured"<<endl;


    for(ResponseComponent* rs : colleagues){
        rs->handleNotice();
    }

}
