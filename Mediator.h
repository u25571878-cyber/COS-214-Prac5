#ifndef RESPONSEMEDIATOR_H
#define RESPONSEMEDIATOR_H

#include "Incident.h"
#include "CampusArea.h"
#include "AccessController.h"

#include <iostream>
#include <vector>

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
        void broadcast(Incident*, string);
        void retract(Incident*);
};

class ResponseUnit : public ResponseComponent{
    public:
        using ResponseComponent::ResponseComponent;
        virtual ~ResponseUnit() = default;
        virtual bool dispatchTo(Incident*) =0;
        virtual bool recall(Incident*) =0;
};

class AccessController;

class SecurityTeam : public ResponseUnit {
    private:
        AccessController* controller;
    public:
        SecurityTeam(ResponseMediator* m, string n, AccessController* ac);
        void handleNotice() override;
        bool dispatchTo(Incident*) override;
        bool recall(Incident*) override;
        bool secureArea(CampusArea*);
        bool reOpenArea(CampusArea*);
};

class MedicalTeam : public ResponseUnit{
    public:
        using ResponseUnit::ResponseUnit;

        void handleNotice() override;
        bool dispatchTo(Incident*) override;
        bool recall(Incident*) override;
};

class FacilitiesTeam : public ResponseUnit{
    public:
        using ResponseUnit::ResponseUnit;

        void handleNotice() override;
        bool dispatchTo(Incident*) override;
        bool recall(Incident*) override;
};

#endif
