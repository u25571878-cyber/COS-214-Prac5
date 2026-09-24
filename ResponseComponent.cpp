#include "Mediator.h"

ResponseComponent::ResponseComponent(ResponseMediator* m, string n): mediator(m), name(n){}

string ResponseComponent::getName(){
    return name;
}
