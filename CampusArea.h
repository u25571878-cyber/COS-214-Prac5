#ifndef CAMPUSAREA_H
#define CAMPUSAREA_H

#include <string>
#include "AccessController.h"

class AccessController;

using namespace std;

class CampusArea
{
protected:
    string name;
    bool locked;

public:
    CampusArea(string name);
    virtual bool secure(AccessController &) = 0;
    virtual bool reopen(AccessController &) = 0;
    bool isLocked();
    string getName() { return name; }
    virtual ~CampusArea();
};

#endif // CAMPUSAREA_H
