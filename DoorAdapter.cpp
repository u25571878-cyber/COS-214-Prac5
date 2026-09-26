#include "DoorAdapter.h"

DoorAdapter::DoorAdapter(DoorController* controller) : doorController(controller){}

DoorAdapter::~DoorAdapter(){
    delete doorController;
}

int DoorAdapter::zoneId(CampusArea* area){
    if(area == NULL){
        return 0;
    }
    string areaName = area -> getName();

    int hash = 0;
    for(int i = 0; i < areaName.size(); i++){
        hash = hash * 31 + static_cast<int>(areaName[i]);
    }
    if(hash < 0){
        hash = -hash;
    }
    return (hash % 900) + 100;
}

bool DoorAdapter::lock(CampusArea* area){
    int zone = zoneId(area);
    if(zone <= 0){
        return false;
    }
    int code = zone * 10;
    return doorController -> sendCommand(code) == 1;
}

bool DoorAdapter::unlock(CampusArea* area) {
    int zone = zoneId(area);
    if (zone <= 0) {
        return false;
    }
    int code = zone * 10 + 1;
    return doorController->sendCommand(code) == 1;
}

