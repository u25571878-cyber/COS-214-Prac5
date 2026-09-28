#include "Building.h"

Building::Building(string areaName) : CampusArea(areaName){};

Building::~Building(){
    for(std::size_t i = 0; i < areas.size(); i++)
    {
        delete areas[i];
    }
    areas.clear();
}

bool Building::add(CampusArea* area){
    if(area == NULL){
        return false;
    }
    areas.push_back(area);
    return true;
}

bool Building::secure(AccessController& controller){
    if(areas.empty()){
        return false;
    }
    bool allSuccessful = true;
    for(std::size_t i = 0; i < areas.size(); i++){
        bool success = areas[i] -> secure(controller);
        if(!success){
            allSuccessful = false;
        }
    }
    locked = allSuccessful;
    return allSuccessful;
}

bool Building::reopen(AccessController& controller){
    if(areas.empty()){
        return false;
    }
    bool allSuccessful = true;
    for(std::size_t i = 0; i < areas.size(); i++){
        bool success = areas[i] -> reopen(controller);
        if(!success){
            allSuccessful = false;
        }
    }
    if(allSuccessful){
        locked = false;
    }
    return allSuccessful;
}

