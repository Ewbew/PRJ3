#include "VarHandler.h"
#include <string>
#include <iostream>
using namespace std;



VarHandler::VarHandler() {
    value1DriveMode = 0;
    value2DriveMode = 0;
    value1ShootMode = 0;
    value2ShootMode = 0;
    ShootState = false;
    controlMode = 2;
}

//Set and get Drive mode
void VarHandler::setVar1DriveMode(const int & newValue) {
    value1DriveMode = newValue;
}

int VarHandler::getVar1DriveMode() const {
    return value1DriveMode;
}
void VarHandler::setVar2DriveMode(const int & newValue) {
    value2DriveMode = newValue;
}

int VarHandler::getVar2DriveMode() const {
    return value2DriveMode;
}


//Set and get ShootMode
void VarHandler::setVar1ShootMode(const int & newValue) {
    value1ShootMode = newValue;
}

int VarHandler::getVar1ShootMode() const {
    return value1ShootMode;
}
void VarHandler::setVar2ShootMode(const int & newValue) {
    value2ShootMode = newValue;
}

int VarHandler::getVar2ShootMode() const {
    return value2ShootMode;
}

//Set and get ShootState
void VarHandler::setShootState(const bool & newValue) {
    ShootState = newValue;
}

bool VarHandler::getShootState() const {
    return ShootState;
}


//Set and get controlMode

void VarHandler::setControlMode(const int & newValue) {
    controlMode = newValue;
}

int VarHandler::getControlMode() const {
    return controlMode;
}

//Get message
string VarHandler::getMessage(){

    // Drive mode
    if(controlMode==2){
        return "$,"+to_string(getVar1DriveMode())+","+to_string(getVar2DriveMode())+",0X"; // End with 0, since it represents shooting 
                                                                                        // mode, which is always 0 (false) in drive mode
                                                                                        // 'X' is the end char

    }
    // Shoot mode
    if(controlMode==3){
        return "@,"+to_string(getVar1ShootMode())+","+to_string(getVar2ShootMode())+","+to_string(static_cast<int>(getShootState()))+ "X"; 
                                                                                                                             // 'X' is the end char
    }
    else{
        cout<< "Get Message Failed";
        return "";
    }
}