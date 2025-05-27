#pragma once
#include <string>

/**
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
     * @brief Set the shoot mode variable 1 (e.g., turret horizontal).
     * @param newValue The new value for shoot mode 1.
     */
    void setVar1ShootMode(const int& newValue);

    /**
     * @brief Get the shoot mode variable 1 (e.g., turret horizontal).
     * @return The value of shoot mode 1.
     */
    int getVar1ShootMode() const;

    /**
     * @brief Set the shoot mode variable 2 (e.g., turret vertical).
     * @param newValue The new value for shoot mode 2.
     */
    void setVar2ShootMode(const int& newValue);

    /**
     * @brief Get the shoot mode variable 2 (e.g., turret vertical).
     * @return The value of shoot mode 2.
     */
    int getVar2ShootMode() const;

    // Shoot state

    /**
     * @brief Set the shoot state (trigger).
     * @param newValue True if shooting, false otherwise.
     */
    void setShootState(const bool& newValue);

    /**
     * @brief Get the shoot state (trigger).
     * @return True if shooting, false otherwise.
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
     * @brief Set the control mode (drive/shoot).
     * @param newValue The new control mode.
     */
    void setControlMode(const int& newValue);

    /**
     * @brief Get the control mode (drive/shoot).
     * @return The current control mode.
     */
    int getControlMode() const;

    // Message handling

    /**
     * @brief Get the formatted message for Bluetooth transmission.
     * @return The message string.
     */
    std::string getMessage();

    /**
     * @brief Set whether the last message was acknowledged.
     * @param acknowledged True if acknowledged.
     */
    void setLastMessageAcknowledged(bool acknowledged);

    /**
     * @brief Check if the last message was acknowledged.
     * @return True if acknowledged.
     */
    bool isLastMessageAcknowledged() const;

    // Prepared message

    /**
     * @brief Set the prepared message.
     * @param message The message to store.
     */
    void setPreparedMessage(const std::string& message);

    /**
     * @brief Get the prepared message.
     * @return The stored prepared message.
     */
    std::string getPreparedMessage() const;

    // Socket disconnection state

    /**
     * @brief Set the socket disconnection state.
     * @param disconnected True if socket is disconnected.
     */
    void setSocketDisconnected(bool disconnected);

    /**
     * @brief Check if the socket is disconnected.
     * @return True if socket is disconnected.
     */
    bool isSocketDisconnected() const;

private:
    int controlMode;                ///< Current control mode (drive/shoot)
    bool ShootState;                ///< Current shoot state

    int value1DriveMode;            ///< Drive mode variable 1 (right wheel)
    int value2DriveMode;            ///< Drive mode variable 2 (left wheel)

    int value1ShootMode;            ///< Shoot mode variable 1 (turret horizontal)
    int value2ShootMode;            ///< Shoot mode variable 2 (turret vertical)

    bool lastMessageAcknowledged;   ///< Last message acknowledged flag

    int ObstructionState;           ///< Obstruction state

    std::string preparedMessage;    ///< Variable to store the prepared message

    bool socketDisconnected;        ///< Track socket disconnection state
};
