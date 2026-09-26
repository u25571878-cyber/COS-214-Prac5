#include "Incident.h"


void EscalatedState::dispatch(Incident* i) {
    cout << "Units are already managing this escalated incident." << endl;
}

void EscalatedState::escalate(Incident* i) {
    cout << "Incident is already escalated." << endl;
}

void EscalatedState::resolve(Incident* i) {
    if (i == nullptr) return;
    cout << "Changing the incident State from EscalatedState -> ResolvedState" << endl;

    i->setState(new ResolvedState());
}

void EscalatedState::cancel(Incident* i) {
    if (i == nullptr) return;
    cout << "Changing the incident State from EscalatedState -> CanceledState" << endl;

    i->setState(new CanceledState());
}
