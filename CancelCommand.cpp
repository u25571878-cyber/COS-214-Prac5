#include "Command.h"

CancelCommand::CancelCommand(Command* target) : targetCommand(target) {}

bool CancelCommand::execute() {
    if (targetCommand == nullptr) {
        return false;
    }

    cout << "Executing CancelCommand: Reversing the target command." << endl;
    return targetCommand->undo();
}

bool CancelCommand::undo() {
    if (targetCommand == nullptr) {
        return false;
    }

    cout << "Undoing CancelCommand: Re-applying the target command." << endl;
    return targetCommand->execute();
}

string CancelCommand::describe() {
    if (targetCommand == nullptr) {
        return "Cancel command (no target)";
    }
    return "Cancelling command: " + targetCommand->describe() ;
}
