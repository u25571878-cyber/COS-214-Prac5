#include <iostream>
#include <string>

#include "Incident.h"
#include "Mediator.h"
#include "Command.h"
#include "OperatorConsole.h"
#include "Emergency.h"
#include "Building.h"
#include "Room.h"
#include "DoorAdapter.h"
#include "DoorController.h"

using namespace std;

static void banner(const string &title)
{
     cout << "\n========================================\n";
     cout << title << "\n";
     cout << "========================================\n";
}

int main()
{
     // ---------------------------------------------------------------
     // System setup: build the collaborators once, then run two
     // end-to-end incident stories through them.
     // ---------------------------------------------------------------

     // Adapter: the legacy door hardware only understands sendCommand(int),
     // DoorAdapter translates that into the AccessController interface.
     DoorController *legacyController = new DoorController();
     DoorAdapter doorAdapter(legacyController); // adapter owns the legacy adaptee

     // Mediator: response components only ever talk to the coordinator.
     IncidentCoordinator coordinator;

     // Mediator colleagues / Command receivers
     SecurityTeam securityTeam(&coordinator, "Alpha-Security", &doorAdapter);
     MedicalTeam medicalTeam(&coordinator, "Medic-One");
     FacilitiesTeam facilitiesTeam(&coordinator, "Facilities-Crew");
     CommsService commsService(&coordinator, "CampusComms");

     coordinator.addComponent(&securityTeam);
     coordinator.addComponent(&medicalTeam);
     coordinator.addComponent(&facilitiesTeam);
     coordinator.addComponent(&commsService);

     // Command invoker
     OperatorConsole console;

     // Facade: one entry point for the multi-step workflows below.
     // Owns an IncidentRegistry internally, so every Incident* handed
     // back by reportIncident() is deleted automatically when
     // emergencyFacade goes out of scope -- no manual delete needed.
     Emergency emergencyFacade(console, coordinator, securityTeam, medicalTeam, facilitiesTeam, commsService);

     // Composite: the Science Building is made up of several rooms
     Building *scienceBuilding = new Building("Science Building");
     scienceBuilding->add(new Room("Lecture Hall 1"));
     scienceBuilding->add(new Room("Chemistry Lab"));
     scienceBuilding->add(new Room("Server Room"));

     // =================================================================
     // STORY 1: Fire reported in the Science Building
     // Touches Facade, Command, State, Mediator, Composite and Adapter.
     // =================================================================
     banner("STORY 1: Fire reported in the Science Building");

     Incident *fire = emergencyFacade.reportIncident("Fire", 8);
     cout << "Incident #" << fire->getID() << " (" << fire->getType()
          << ", severity " << fire->getSeverity() << ") has been reported.\n\n";

     bool evacHandled = emergencyFacade.evacuation(*fire, *scienceBuilding);
     cout << "\nFacade result: evacuation workflow "
          << (evacHandled ? "completed successfully." : "completed with failures.") << "\n";
     cout << "Is the Science Building secured overall? "
          << (scienceBuilding->isLocked() ? "Yes" : "No") << "\n";

     // The facade recorded this incident's location and registered it,
     // so both can be recovered without main.cpp tracking anything itself.
     Incident *lookedUpFire = emergencyFacade.findIncident(fire->getID());
     cout << "Facade lookup for incident #" << fire->getID() << ": "
          << (lookedUpFire == fire ? "found the same incident." : "not found.") << "\n";
     if (fire->getLocation() != nullptr)
     {
          cout << "Incident location on record: " << fire->getLocation()->getName() << "\n";
     }

     // =================================================================
     // STORY 2: Medical emergency, an explicit cancellation, and an
     // invalid operation caught by the State pattern.
     // =================================================================
     banner("STORY 2: Medical emergency in the Chemistry Lab");

     Incident *medical = emergencyFacade.reportIncident("Medical", 5);
     cout << "Incident #" << medical->getID() << " (" << medical->getType()
          << ", severity " << medical->getSeverity() << ") has been reported.\n\n";

     bool medHandled = emergencyFacade.medicalEmergency(*medical);
     cout << "\nFacade result: medical response workflow "
          << (medHandled ? "completed successfully." : "completed with failures.") << "\n";

     // Subsystems remain independently usable: the operator issues one more
     // command straight through the console, bypassing the facade entirely.
     banner("Operator issues an extra alert directly via the console");
     IssueAlertCommand *extraAlert =
         new IssueAlertCommand(&commsService, medical, "All clear pending review");
     console.run(extraAlert);

     banner("Operator formally cancels that alert with a CancelCommand");
     console.run(new CancelCommand(extraAlert));

     // Invalid-operation case: resolve the incident, then try to dispatch it
     // again. The State pattern reports this sensibly instead of crashing
     // or silently doing nothing useful.
     banner("Resolving the incident, then attempting an invalid re-dispatch");
     medical->resolve();
     medical->dispatch(); // ResolvedState refuses and explains why

     // Direct subsystem access without the facade: lock and reopen a room
     // that was never part of an incident, showing the adapter still works
     // standalone.
     banner("Direct subsystem access: securing a room without the facade");
     Room isolatedRoom("Records Office");
     bool locked = isolatedRoom.secure(doorAdapter);
     cout << "Records Office locked directly via the adapter: "
          << (locked ? "Yes" : "No") << "\n";
     bool reopened = isolatedRoom.reopen(doorAdapter);
     cout << "Records Office reopened directly via the adapter: "
          << (reopened ? "Yes" : "No") << "\n";

     // =================================================================
     // STORY 3: Full incident lifecycle, undo paths and reopening.
     // Story 1 and 2 only ever moved incidents forward and never
     // reversed a command, so this story deliberately exercises the
     // undo/recall/reopen side of every pattern, plus escalation and
     // cancellation, which nothing above ever touches.
     // =================================================================
     banner("STORY 3: Escalation, undo, recall and reopening");

     Incident *drill = emergencyFacade.reportIncident("Gas Leak", 3);
     cout << "Incident #" << drill->getID() << " (" << drill->getType()
          << ", severity " << drill->getSeverity() << ") has been reported.\n";

     // Escalate through the facade, which now owns the coordinator link
     // and notifies it internally (nothing else in the codebase used to
     // trigger ResponseMediator::escalated() at all), then hit every
     // "already escalated / already resolved" branch directly on the
     // incident's own state machine.
     emergencyFacade.escalateIncident(*drill);
     drill->escalate(); // already escalated
     drill->dispatch(); // units are already managing this escalated incident
     drill->resolve();
     drill->dispatch(); // already resolved
     drill->escalate(); // already resolved
     drill->resolve();  // already resolved
     drill->cancel();   // cannot cancel a resolved incident

     banner("Direct DispatchUnitCommand: execute, describe and undo (recall)");
     Incident *drill2 = emergencyFacade.reportIncident("Suspicious Package", 4);
     DispatchUnitCommand directDispatch(&securityTeam, drill2);
     cout << "Command: " << directDispatch.describe() << "\n";
     directDispatch.execute();
     directDispatch.undo(); // recalls the unit, Incident moves Dispatched -> Canceled

     // The incident is now Canceled: exercise every CanceledState branch.
     drill2->dispatch();
     drill2->escalate();
     drill2->resolve();
     drill2->cancel();

     banner("SecureAreaCommand through the console, then undone (reopen)");
     Room *labRoom = new Room("Physics Lab");
     SecureAreaCommand *secureLab = new SecureAreaCommand(&securityTeam, labRoom);
     console.run(secureLab);
     cout << "Command: " << secureLab->describe() << "\n";
     console.cancelLast(); // SecureAreaCommand::undo() -> SecurityTeam::reOpenArea

     banner("CancelCommand undone in turn (re-applies the original command)");
     IssueAlertCommand *driveAlert = new IssueAlertCommand(&commsService, drill, "Gas leak contained");
     console.run(driveAlert);
     CancelCommand *cancelDriveAlert = new CancelCommand(driveAlert);
     console.run(cancelDriveAlert);
     cout << "Command: " << cancelDriveAlert->describe() << "\n";
     console.cancelLast(); // CancelCommand::undo() -> re-executes driveAlert

     banner("CancelCommand defensive branch: no target command");
     CancelCommand orphanCancel(nullptr);
     cout << "describe(): " << orphanCancel.describe() << "\n";
     cout << "execute():  " << (orphanCancel.execute() ? "true" : "false") << "\n";
     cout << "undo():     " << (orphanCancel.undo() ? "true" : "false") << "\n";

     // Reopen the whole Science Building, the mirror image of Story 1's
     // secure() call, which Building::reopen() never got to run before.
     banner("Reopening the Science Building (Composite, mirror of Story 1)");
     bool reopenedBuilding = scienceBuilding->reopen(doorAdapter);
     cout << "Science Building fully reopened: "
          << (reopenedBuilding ? "Yes" : "No") << "\n";

     // =================================================================
     // STORY 4: Remaining State/Mediator/Composite branches and a few
     // defensive null-checks that nothing above happens to reach.
     // =================================================================
     banner("STORY 4: Closing the remaining State transitions");

     // ReportState -> Resolved and ReportState -> Canceled directly,
     // since every other incident above was dispatched or escalated
     // first and never resolved/cancelled straight from Reported.
     Incident *freshResolve = emergencyFacade.reportIncident("Water Leak", 2);
     freshResolve->resolve();

     Incident *freshCancel = emergencyFacade.reportIncident("Noise Complaint", 1);
     freshCancel->cancel();

     // DispatchedState -> Escalated, which nothing above triggers because
     // every dispatched incident in Story 1-3 was resolved or recalled
     // before ever being escalated.
     Incident *freshEscalateAfterDispatch = emergencyFacade.reportIncident("Power Outage", 4);
     freshEscalateAfterDispatch->dispatch();
     freshEscalateAfterDispatch->escalate();

     // EscalatedState -> Canceled, the one Escalated exit path Story 3
     // doesn't take (Story 3 only resolves out of Escalated).
     Incident *freshCancelAfterEscalate = emergencyFacade.reportIncident("Bomb Threat", 9);
     freshCancelAfterEscalate->escalate();
     freshCancelAfterEscalate->cancel();

     banner("Direct recall on Medical and Facilities teams");
     Incident *recallDrill = emergencyFacade.reportIncident("Flood", 3);
     medicalTeam.dispatchTo(recallDrill);
     medicalTeam.recall(recallDrill);
     facilitiesTeam.dispatchTo(recallDrill);
     facilitiesTeam.recall(recallDrill);

     banner("CommsService defensive branches: null incident");
     commsService.broadcast(nullptr, "should be ignored");
     commsService.retract(nullptr);

     banner("Empty Composite and invalid add()");
     Building emptyAnnex("Unused Annex");
     bool addedNull = emptyAnnex.add(nullptr);
     cout << "Adding a null area to the annex: " << (addedNull ? "true" : "false") << "\n";
     bool emptySecure = emptyAnnex.secure(doorAdapter);
     cout << "Securing an empty building: " << (emptySecure ? "true" : "false") << "\n";
     bool emptyReopen = emptyAnnex.reopen(doorAdapter);
     cout << "Reopening an empty building: " << (emptyReopen ? "true" : "false") << "\n";

     banner("Legacy DoorController rejecting malformed codes directly");
     DoorController standaloneLegacyController;
     cout << "Zone too low (invalid): "
          << standaloneLegacyController.sendCommand(5) << "\n";
     cout << "Unrecognised action digit (invalid): "
          << standaloneLegacyController.sendCommand(1105) << "\n";

     banner("Remaining defensive null-checks, exercised directly");
     ReportState standaloneReportState;
     standaloneReportState.dispatch(nullptr);
     standaloneReportState.escalate(nullptr);
     standaloneReportState.resolve(nullptr);
     standaloneReportState.cancel(nullptr);

     console.run(nullptr);                                                 // OperatorConsole::run() null-command guard
     bool badRun = console.run(new DispatchUnitCommand(nullptr, nullptr)); // execute() fails
     cout << "Running a malformed command: " << (badRun ? "true" : "false") << "\n";
     freshResolve->setState(nullptr); // Incident::setState() null guard, no-op

     bool lockedNullArea = doorAdapter.lock(nullptr);     // DoorAdapter null-area guard
     bool unlockedNullArea = doorAdapter.unlock(nullptr); // DoorAdapter null-area guard
     cout << "Locking a null area (invalid): " << (lockedNullArea ? "true" : "false") << "\n";
     cout << "Unlocking a null area (invalid): " << (unlockedNullArea ? "true" : "false") << "\n";

     // Incident constructed with an explicit starting state, rather than
     // the default ReportState every other incident above was given.
     Incident preDispatchedDrill(new DispatchedState(), "Pre-staged Drill", 1);
     cout << "Pre-staged incident #" << preDispatchedDrill.getID()
          << " starts in DispatchedState.\n";

     // Polymorphic destruction through the AccessController base pointer,
     // per the practical's rule that every polymorphic base needs a
     // working virtual destructor -- stack destruction alone (as with
     // 'doorAdapter' above) never runs this path.
     banner("Polymorphic destruction: delete through AccessController*");
     AccessController *polymorphicAdapter = new DoorAdapter(new DoorController());
     delete polymorphicAdapter;

     // ---------------------------------------------------------------
     // Cleanup. Incidents are NOT deleted here: every Incident* returned
     // by emergencyFacade.reportIncident() is owned by the facade's
     // IncidentRegistry and freed when emergencyFacade goes out of scope.
     // Building owns its rooms; Incident owns its current state;
     // DoorAdapter (stack object) deletes the legacy controller it owns.
     // ---------------------------------------------------------------
     delete labRoom;
     delete scienceBuilding;

     cout << "\nCampusGuard demonstration complete.\n";
     return 0;
}