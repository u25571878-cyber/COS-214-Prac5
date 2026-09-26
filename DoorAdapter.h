#ifndef DOORADAPTER_H
#define DOORADAPTER_H
#include "AccessController.h"
#include "DoorController.h"
#include <string>

using namespace std;

class DoorAdapter : public AccessController{
    private:
        DoorController* doorController;
        int zoneId(CampusArea*);
    public:
        DoorAdapter(DoorController*);
        ~DoorAdapter() override;
        bool lock(CampusArea*) override;
        bool unlock(CampusArea*) override;
};

#endif //DOORADAPTER_H