#pragma once
#include <string>

/**
 * @class VarHandler
 * @brief Handles variables and state for Bluetooth communication.
 * 
 * This class manages drive and shoot modes, message formatting,
 * obstruction state, and socket connection status for the Bluetooth thread.
 */
class VarHandler {
public:
    /**
     * @brief Constructs a VarHandler with default values.
     */
    VarHandler();

    // Drive mode
    /**
     * @brief Set the drive mode variable for the right wheel. 
     * @param newValue The new value for drive mode 1.
     */
    void setVar1DriveMode(const int& newValue);

    /**
     * @brief Get the drive mode variable for the right wheel.
     * @return The value of drive mode 1. 
     */
    int getVar1DriveMode() const;

    /**
     * @brief Set the drive mode variable for the left wheel. 
     * @param newValue The new value for drive mode 2.
     */
    void setVar2DriveMode(const int& newValue);
    /**
     * @brief Get the drive mode variable for the left wheel.
     * @return The value of drive mode 2. 
     */
    int getVar2DriveMode() const;

    // Shoot mode
    /**
     * @brief Set the shoot mode variable 1.
     * @param newValue The new value for shoot mode 1.
     */
    void setVar1ShootMode(const int& newValue);
    /**
     * @brief Get the shoot mode variable 1.
     * @return The value of shoot mode 1.
     */
    int getVar1ShootMode() const;
    /**
     * @brief Set the shoot mode variable 2.
     * @param newValue The new value for shoot mode 2.
     */
    void setVar2ShootMode(const int& newValue);
    /**
     * @brief Get the shoot mode variable 2.
     * @return The value of shoot mode 2.
     */
    int getVar2ShootMode() const;

    // Shoot state
    /**
     * @brief Set the shoot state.
     * @param newValue The new shoot state.
     */
    void setShootState(const bool& newValue);
    /**
     * @brief Get the shoot state.
     * @return The current shoot state.
     */
    bool getShootState() const;

    // Obstruction state
    /**
     * @brief Set the obstruction state.
     * @param newValue The new obstruction state.
     */
    void setObstructionState(const int& newValue);
    /**
     * @brief Get the obstruction state.
     * @return The current obstruction state.
     */
    int getObstructionState() const;

    // Control mode
    /**
     * @brief Set the control mode.
     * @param newValue The new control mode.
     */
    void setControlMode(const int& newValue);
    /**
     * @brief Get the control mode.
     * @return The current control mode.
     */
    int getControlMode() const;

    // Message handling
    /**
     * @brief Get the formatted message.
     * @return The formatted message string.
     */
    std::string getMessage();
    /**
     * @brief Set the acknowledgment state of the last message.
     * @param acknowledged True if acknowledged, false otherwise.
     */
    void setLastMessageAcknowledged(bool acknowledged);
    /**
     * @brief Check if the last message was acknowledged.
     * @return True if acknowledged, false otherwise.
     */
    bool isLastMessageAcknowledged() const;

    // Prepared message
    /**
     * @brief Set the prepared message.
     * @param message The message to prepare.
     */
    void setPreparedMessage(const std::string& message);
    /**
     * @brief Get the prepared message.
     * @return The prepared message string.
     */
    std::string getPreparedMessage() const;

    // Socket disconnection state
    /**
     * @brief Set the socket disconnection state.
     * @param disconnected True if socket is disconnected, false otherwise.
     */
    void setSocketDisconnected(bool disconnected);
    /**
     * @brief Check if the socket is disconnected.
     * @return True if disconnected, false otherwise.
     */
    bool isSocketDisconnected() const;

private:
    /**
     * @brief Stores the current control mode.
     */
    int controlMode;
    /**
     * @brief Stores the current shoot state.
     */
    bool ShootState;
    /**
     * @brief Stores the drive mode value for the right wheel.
     */
    int value1DriveMode;
    /**
     * @brief Stores the drive mode value for the left wheel.
     */
    int value2DriveMode;
    /**
     * @brief Stores the shoot mode value 1.
     */
    int value1ShootMode;
    /**
     * @brief Stores the shoot mode value 2.
     */
    int value2ShootMode;
    /**
     * @brief Indicates if the last message was acknowledged.
     */
    bool lastMessageAcknowledged;
    /**
     * @brief Stores the current obstruction state.
     */
    int ObstructionState;
    /**
     * @brief Variable to store the prepared message.
     */
    std::string preparedMessage;
    /**
     * @brief Tracks socket disconnection state.
     */
    bool socketDisconnected;
};
