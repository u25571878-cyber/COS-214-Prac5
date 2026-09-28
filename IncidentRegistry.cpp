#include "IncidentRegistry.h"

void IncidentRegistry::add(Incident* incident){
    if(incident == nullptr) return;
    incidents.push_back(incident);
}

Incident* IncidentRegistry::find(int id) const{
    for(Incident* i : incidents){
        if(i != nullptr && i->getID() == id){
            return i;
        }
    }
    return nullptr;
}

IncidentRegistry::~IncidentRegistry(){
    for(Incident* i : incidents){
        delete i;
    }
    incidents.clear();
}