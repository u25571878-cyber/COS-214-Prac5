#include "DoorController.h"

int DoorController::sendCommand(int code){
    int zone = code / 10;
    int action = code % 10;

    if(zone <= 10){
        return 0;
    }

    if (action != 0 && action != 1) {
        return 0;
    }

    return 1;
}