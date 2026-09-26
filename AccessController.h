#ifndef ACCESSCONTROLLER_H
#define ACCESSCONTROLLER_H
#include "CampusArea.h"

class AccessController{
    public:
        virtual ~AccessController(){}
        virtual bool lock(CampusArea*) = 0;
        virtual bool unlock(CampusArea*) = 0;
};


#endif //ACCESSCONTROLLER_H