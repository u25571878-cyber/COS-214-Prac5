#include "Room.h"

Room::Room(string name):CampusArea(name){}

bool Room::secure(AccessController& controller){
    bool success = controller.lock(this);
    if(success){
        locked = true;
    }
    return success;
}

bool Room::reopen(AccessController& controller){
    bool success = controller.unlock(this);
    if(success){
        locked = false;
    }
    return success;
}
