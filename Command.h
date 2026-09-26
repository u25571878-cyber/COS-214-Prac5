#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "ResponseComponent.h"
#include "Incident.h"

using namespace std;


class Command{
    public:
        virtual bool execute() =0;
        virtual bool undo() =0;
        virtual string describe()=0;
        virtual ~Command() = default;
};

class SecurityTeam;
class CampusArea;

class SecureAreaCommand: public Command{
    private:
        SecurityTeam* securityTeam;
        CampusArea* campusArea;
    public:
        SecureAreaCommand(SecurityTeam* st, CampusArea* ca);
        bool execute() override;
        bool undo() override;
        string describe() override;
};

class CommsService;
class Incident;

class IssueAlertCommand : public Command{
    private:
        CommsService* commsService;
        Incident* incident;
        string message;
    public:
        IssueAlertCommand(CommsService* cs, Incident* i, string s);
        bool execute() override;
        bool undo() override;
        string describe() override;
};

class CancelCommand : public Command{
    private:
        Command* targetCommand;
    public:
        CancelCommand(Command* target);
        bool execute() override;
        bool undo() override;
        string describe() override;
};

class ResponseUnit;

class DispatchUnitCommand : public Command{
    private:
        ResponseUnit* responseUnit;
        Incident* incident;
    public:
        DispatchUnitCommand(ResponseUnit* du, Incident* i);
        bool execute() override;
        bool undo() override;
        string describe() override;
};

#endif
