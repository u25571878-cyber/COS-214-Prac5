#include "Incident.h"

int Incident::id = 0;

Incident::Incident(IncidentState* s, string t, int i): type(t), severity(i){
    localID = id++;

    if(s == nullptr)
        state = new ReportState();
    else
        state = s;
}

void Incident::dispatch(){
    state->dispatch(this);
}

void Incident::escalate(){
    if (severity <= 10)
        severity++;

    state->escalate(this);
}

void Incident::resolve(){
    severity = 0;
    state->resolve(this);
}

void Incident::cancel(){
    severity = -1;

    state->cancel(this);
}


void Incident::setState(IncidentState* i){
    if (i == nullptr)
        return;

    delete state;
    state = i;
}


Incident::~Incident(){
    delete state;
}
