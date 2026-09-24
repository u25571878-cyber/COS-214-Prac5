#ifndef RESPONSEMEDIATOR_H
#define RESPONSEMEDIATOR_H

#include "Incident.h"
#include "CampusArea.h"

#include <iostream>
#include <std::vector>

using namespace std;

class ResponseUnit;
class Incident;
class CampusArea;
class ResponseComponent;
class Campus;

class ResponseMediator{
    public:
        virtual void unitDispatched(ResponseUnit*, Incident* ) =0;
        virtual void escalated(Incident*) =0;
        virtual void areaSecured(CampusArea*, Incident*) =0;
        virtual ~ResponseMediator() = default;
};

class IncidentCoordinator : public ResponseMediator{
    private:
        vector<ResponseComponent*> colleagues;
    public:
        void addComponent(ResponseComponent*);
        void unitDispatched(ResponseUnit*, Incident*) override;
        void escalated(Incident*) override;
        void areaSecured(CampusArea*, Incident*) override;
};

class ResponseComponent {
    protected:
        ResponseMediator* mediator;
        string name;
    public:
        ResponseComponent(ResponseMediator* m, string n);
        virtual void handleNotice() =0;
        virtual ~ResponseComponent() = default;
        string getName();
};

class CommsService : public ResponseComponent{
    public:
        using ResponseComponent::ResponseComponent;
        void handleNotice() override;
        void broadCast(Incident*, string);
        void retract(Incident*);
};

class ResponseUnit : ResponseComponent{
    public:
        using ResponseComponent::ResponseComponent;
        virtual ~ResponseUnit() = default;
        virtual bool dispatchTo(Incident*) =0;
        virtual bool recall(Incident*) =0;
};

class SecurityTeam : public ResponseUnit {
    public:
        using ResponseUnit::ResponseUnit;
        void handleNotice() override;
        bool dispatchTo(Incident* incident) override;
        bool recall(Incident* incident) override;
        bool secureArea(CampusArea* area);
        bool reOpenArea(CampusArea* area);
};

class medicalTeam : public ResponseUnit{
    public:
        using ResponseUnit::ResponseUnit;

        void handleNotice() override;
        bool dispatchTo(Incident* incident) override;
        bool recall(Incident* incident) override;
};

class facilitiesTeam : public ResponseUnit{
    public:
        using ResponseUnit::ResponseUnit;

        void handleNotice() override;
        bool dispatchTo(Incident* incident) override;
        bool recall(Incident* incident) override;
};

#endif
