#include "Incident.h"

void ResolvedState::dispatch(Incident* i) {
    cout << "Incident is already resolved." << endl;
}

void ResolvedState::escalate(Incident* i) {
    cout << "Incident is already resolved." << endl;
}

void ResolvedState::resolve(Incident* i) {
    cout << "Incident is already resolved." << endl;
}

void ResolvedState::cancel(Incident* i) {
    cout << "Cannot cancel a resolved incident." << endl;
}
