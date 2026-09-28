#include "Emergency.h"

Emergency::Emergency(OperatorConsole& operatorConsole, IncidentCoordinator& incidentCoordinator, SecurityTeam& security, MedicalTeam& medical, FacilitiesTeam& facilities, CommsService& comms) : console(operatorConsole), coordinator(incidentCoordinator), securityTeam(security), medicalTeam(medical), facilitiesTeam(facilities), commsService(comms) {}

Incident* Emergency::reportIncident(const std::string& type, int severity) {
    Incident* incident = new Incident(NULL, type, severity);
    registry.add(incident);
    return incident;
}

Incident* Emergency::findIncident(int id) {
    return registry.find(id);
}

bool Emergency::evacuation(Incident& incident, Building& building){
    incident.setLocation(&building);
    bool securityDispatched = console.run(new DispatchUnitCommand(&securityTeam, &incident));
    bool facilitiesDispatched = console.run(new DispatchUnitCommand(&facilitiesTeam, &incident));
    bool secured = console.run(new SecureAreaCommand(&securityTeam, &building));
    bool alerted = console.run(new IssueAlertCommand(&commsService, &incident, "Evacuation in progress"));
    return securityDispatched && facilitiesDispatched && secured && alerted;
}

bool Emergency::medicalEmergency(Incident& incident) {
    bool dispatched = console.run(new DispatchUnitCommand(&medicalTeam, &incident));
    bool alerted = console.run(new IssueAlertCommand(&commsService, &incident, "Medical emergency in progress"));
    return dispatched && alerted;
}

bool Emergency::escalateIncident(Incident& incident) {
    incident.escalate();
    coordinator.escalated(&incident);
    return true;
}