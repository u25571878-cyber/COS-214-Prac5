#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <string>
#include "Incident.h"
#include "Mediator.h"
#include "Command.h"
#include "OperatorConsole.h"
#include "Building.h"


class Emergency {
private:
    OperatorConsole& console;
    SecurityTeam& securityTeam;
    MedicalTeam& medicalTeam;
    FacilitiesTeam& facilitiesTeam;
    CommsService& commsService;

public:
    Emergency(OperatorConsole& operatorConsole,
              SecurityTeam& security,
              MedicalTeam& medical,
              FacilitiesTeam& facilities,
              CommsService& comms);
    Incident* reportIncident(const std::string& type, int severity);
    bool evacuation(Incident& incident, Building& building);
    bool medicalEmergency(Incident& incident);

};


#endif //EMERGENCY_H