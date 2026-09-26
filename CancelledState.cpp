#include "Incident.h"

void CanceledState::dispatch(Incident* i) {
    cout << "Incident was canceled." << endl;
}

void CanceledState::escalate(Incident* i) {
    cout << "Incident was canceled." << endl;
}

void CanceledState::resolve(Incident* i) {
    cout << "Incident was canceled." << endl;
}

void CanceledState::cancel(Incident* i) {
    cout << "Incident is already canceled." << endl;
}
