#pragma once
#include <string>

class VarHandler {
public:
    VarHandler();

    // Drive mode
    void setVar1DriveMode(const int& newValue);
    int getVar1DriveMode() const;
    void setVar2DriveMode(const int& newValue);
    int getVar2DriveMode() const;

    // Shoot mode
    void setVar1ShootMode(const int& newValue);
    int getVar1ShootMode() const;
    void setVar2ShootMode(const int& newValue);
    int getVar2ShootMode() const;

    // Shoot state
    void setShootState(const bool& newValue);
    bool getShootState() const;

    // Obstruction state
    void setObstructionState(const int& newValue);
    int getObstructionState() const;

    // Control mode
    void setControlMode(const int& newValue);
    int getControlMode() const;

    // Message handling
    std::string getMessage();
    void setLastMessageAcknowledged(bool acknowledged);
    bool isLastMessageAcknowledged() const;

    // Prepared message
    void setPreparedMessage(const std::string& message);
    std::string getPreparedMessage() const;

    // Socket disconnection state
    void setSocketDisconnected(bool disconnected);
    bool isSocketDisconnected() const;

private:
    int controlMode;
    bool ShootState;

    int value1DriveMode;
    int value2DriveMode;

    int value1ShootMode;
    int value2ShootMode;

    bool lastMessageAcknowledged;

    int ObstructionState;

    std::string preparedMessage; // Variable to store the prepared message

    bool socketDisconnected; // Track socket disconnection state
};
