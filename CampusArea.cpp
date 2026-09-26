#include "CampusArea.h"

CampusArea::CampusArea(string name){
    this -> name = name;
    locked = false;
}

CampusArea::~CampusArea(){}

bool CampusArea::isLocked(){
    return locked;
}