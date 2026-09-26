#include "Incident.h"


void DispatchedState::dispatch(Incident* i) {
    cout << "Incident is already dispatched." << endl;
}

void DispatchedState::escalate(Incident* i) {
    if (i == nullptr) return;
    cout << "Changing the incident State from DispatchedState -> EscalatedState" << endl;
    i->setState(new EscalatedState());
}

void DispatchedState::resolve(Incident* i) {
    if (i == nullptr) return;
    cout << "Changing the incident State from DispatchedState -> ResolvedState" << endl;
    i->setState(new ResolvedState());
}

void DispatchedState::cancel(Incident* i) {
    if (i == nullptr) return;
    cout << "Changing the incident State from DispatchedState -> CanceledState" << endl;
    i->setState(new CanceledState());
}
