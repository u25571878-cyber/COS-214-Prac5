#include "Incident.h"

void ReportState::dispatch(Incident* i ){
    if(i == nullptr)
        return;

    i->setState(new DispatchedState());
    cout<<"Changing the incident State from ReportState -> DispatchState"<<endl;
}


void ReportState::escalate(Incident* i){
    if(i == nullptr)
        return;

    i->setState(new EscalatedState());
    cout<<"Changing the incident State from ReportState -> EscalatedState"<<endl;

}

void ReportState::resolve(Incident* i){
    if(i == nullptr)
        return;

    i->setState(new ResolvedState());
    cout<<"Changing the incident State from ReportState -> ResolvedState"<<endl;

}

void ReportState::cancel(Incident* i){
    if(i == nullptr)
        return;

    i->setState(new CanceledState());
    cout<<"Changing the incident State from ReportState -> CanceledState"<<endl;

}
