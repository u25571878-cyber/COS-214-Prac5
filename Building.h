#ifndef BUILDING_H
#define BUILDING_H

#include "CampusArea.h"
#include <vector>

using namespace std;

class Building : public CampusArea{
    private:
        vector<CampusArea*> areas;
    public:
        Building(string name);
        bool add(CampusArea* );
        bool secure(AccessController&);
        bool reopen(AccessController&);
        ~Building();
};

#endif //BUILDING_H