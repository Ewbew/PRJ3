#pragma once
#include <iostream>
#include <string>
#include <iostream>
class VarHandler {
public:
    VarHandler();

    void setVar1DriveMode(const int& newValue);
    int getVar1DriveMode() const;
    void setVar2DriveMode(const int& newValue);
    int getVar2DriveMode() const;


    void setVar1ShootMode(const int& newValue);
    int getVar1ShootMode() const;
    void setVar2ShootMode(const int& newValue);
    int getVar2ShootMode() const;

    void setShootState(const bool& newValue);
    bool getShootState() const;

    std::string getMessage();

    void setControlMode(const int& newValue);
    int getControlMode() const;

    void setLastMessageAcknowledged(bool acknowledged);
    bool isLastMessageAcknowledged() const;

private:
    int controlMode;
    bool ShootState;

    int value1DriveMode;
    int value2DriveMode;

    int value1ShootMode;
    int value2ShootMode;

    bool lastMessageAcknowledged;
};
