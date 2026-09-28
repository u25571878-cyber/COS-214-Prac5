#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <string>
#include "Incident.h"
#include "Mediator.h"
#include "Command.h"
#include "OperatorConsole.h"
#include "Building.h"
#include "IncidentRegistry.h"

class Emergency
{
private:
    OperatorConsole &console;
    IncidentCoordinator &coordinator;
    SecurityTeam &securityTeam;
    MedicalTeam &medicalTeam;
    FacilitiesTeam &facilitiesTeam;
    CommsService &commsService;
    IncidentRegistry registry;

public:
    Emergency(OperatorConsole &operatorConsole,
              IncidentCoordinator &incidentCoordinator,
              SecurityTeam &security,
              MedicalTeam &medical,
              FacilitiesTeam &facilities,
              CommsService &comms);
    Incident *reportIncident(const std::string &type, int severity);
    Incident *findIncident(int id);
    bool evacuation(Incident &incident, Building &building);
    bool medicalEmergency(Incident &incident);
    bool escalateIncident(Incident &incident);
};

#endif // EMERGENCY_H