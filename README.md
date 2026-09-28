# COS-214-Prac5

## Project Overview

The **Emergency Management System (EMS)** is a robust, object-oriented C++ application designed to orchestrate and automate emergency responses across a physical campus environment. It manages the entire lifecycle of an emergency incident, coordinates specialized response teams, and securely controls physical infrastructure like building locks.

Built with scalable software engineering principles, the system relies on a strict implementation of six classic Gang of Four (GoF) Design Patterns. This architecture ensures loose coupling between components, clean object ownership, and a highly extensible codebase.

### Key System Capabilities

* **Incident Lifecycle Management:** Tracks emergencies dynamically from initial report to dispatch, escalation, and final resolution.
* **Automated Team Coordination:** Seamlessly dispatches Medical, Security, and Facilities teams while keeping a Communications Service updated to broadcast alerts.
* **Action Tracking & Reversal:** Encapsulates operator actions, allowing the system to track history and recall teams or retract alerts using an undo mechanism.
* **Hierarchical Campus Control:** Interacts with the campus map uniformly, allowing operators to secure a single room or lock down an entire building with a single command.
* **Hardware Integration:** Bridges high-level system logic with legacy physical door controllers.

### Software Architecture & Design Patterns

The project utilizes 28 classes distributed across the following architectural patterns:

* **Facade (`EmergencyFacade`):** Acts as the composition root, taking ownership of the system's initialization and providing a simplified interface for external clients.
* **Mediator (`IncidentCoordinator`):** Acts as the central communication hub. It completely decouples the response units from one another, enabling complex many-to-many event notifications without direct dependencies.
* **Command (`OperatorConsole`, `IssueAlert`, etc.):** Encapsulates operator requests as discrete objects. This allows the Invoker to queue actions, track history, and execute undo operations (e.g., recalling a dispatched unit).
* **State (`Incident`, `IncidentState`):** Manages the internal state machine of an emergency. The system dynamically changes how it responds to actions based on whether the incident is currently Reported, Dispatched, Escalated, Resolved, or Canceled.
* **Composite (`CampusArea`, `Building`, `Room`):** Represents the physical campus as a tree structure, allowing the system to treat individual leaf nodes (rooms) and complex branches (buildings) interchangeably.
* **Adapter (`AccessController`, `LegacyDoorController`):** Wraps incompatible legacy hardware interfaces so the modern system can trigger physical security locks.

## Running with Docker

This project includes Docker support to ensure a consistent build and execution environment without requiring local C++ compiler configuration.

### Prerequisites
Ensure you have [Docker](https://docs.docker.com/get-docker/) installed and running on your machine.

### 1. Build the Docker Image
Navigate to the root directory of the project (where your `Dockerfile` is located) and run the following command to compile the C++ source code and build the image:

```bash
docker build -t ems-app .
