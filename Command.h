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

class SecureAreaCommand: public Command{
    private:
        SecurityTeam* securityTeam;
    public:
        bool execute() override;
        bool undo() override;
        string describe() override;
};

class IssueAlertCommand : public Command{
    private:
        CommandService* commsService;
    public:
        bool execute() override;
        bool undo() override;
        string describe() override;
};

class CancelCommand : public Command{
    private:
        Command* target;
    public:
        bool execute() override;
        bool undo() override;
        string describe() override;
};

class DispatchUnitCommand : public Command{
    private:
        ResponseUnit* responseUnit;
        Incident* incident;
    public:
        bool execute() override;
        bool undo() override;
        string describe() override;
};

#endif
