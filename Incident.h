#ifndef INCIDENT_H
#define INCIDENT_H

#include <iostream>
#include <string>

using namespace std;

class IncidentState;

class Incident{
    private:
        static int id;
        int localID;
        string type;
        int severity; /// 1-10
        IncidentState* state;
    public:
        Incident(IncidentState*, string, int);
        void dispatch();
        void escalate();
        void resolve();
        void cancel();
        void setState(IncidentState*);
        int getID() const { return localID; }
        string getType() const { return type; }
        int getSeverity() const { return severity; }

        ~Incident();
};


class IncidentState{
    public:
        virtual void dispatch(Incident*)= 0;
        virtual void escalate(Incident*)=0;
        virtual void resolve(Incident*) =0;
        virtual void cancel(Incident*)=0;
        virtual ~IncidentState() = default;
};

class ReportState: public IncidentState{
    public:
        virtual void dispatch(Incident*);
        virtual void escalate(Incident*);
        virtual void resolve(Incident*);
        virtual void cancel(Incident*);
};

class DispatchedState: public IncidentState{
    public:
        virtual void dispatch(Incident*);
        virtual void escalate(Incident*);
        virtual void resolve(Incident*);
        virtual void cancel(Incident*);
};


class EscalatedState: public IncidentState{
    public:
        virtual void dispatch(Incident*);
        virtual void escalate(Incident*);
        virtual void resolve(Incident*);
        virtual void cancel(Incident*);
};


class ResolvedState: public IncidentState{
    public:
        virtual void dispatch(Incident*);
        virtual void escalate(Incident*);
        virtual void resolve(Incident*);
        virtual void cancel(Incident*);
};

class CanceledState: public IncidentState{
    public:
        virtual void dispatch(Incident*);
        virtual void escalate(Incident*);
        virtual void resolve(Incident*);
        virtual void cancel(Incident*);
};

#endif
