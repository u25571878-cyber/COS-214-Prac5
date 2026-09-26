#ifndef ROOM_H
#define ROOM_H

#include "AccessController.h"
#include "CampusArea.h"

class Room : public CampusArea{
    public:
        Room(string name);
        bool secure(AccessController&) override;
        bool reopen(AccessController&) override;
};

#endif //ROOM_H