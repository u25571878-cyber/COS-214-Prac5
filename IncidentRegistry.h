#ifndef INCIDENTREGISTRY_H
#define INCIDENTREGISTRY_H

#include <vector>
#include "Incident.h"

using namespace std;

class IncidentRegistry {
    private:
        vector<Incident*> incidents;
    public:
        void add(Incident* incident);
        Incident* find(int id) const;
        ~IncidentRegistry();
};

#endif //INCIDENTREGISTRY_H