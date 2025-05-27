#pragma once
#include <string>
#include "VarHandler.h"
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

/**
 * @brief Klassen BluetoothSender håndterer forbindelse til PSoC og kommunikation mellem controller og PSoC.
 */
class BluetoothSender {
public:
    /**
     * @brief Konstruktør, initialiserer BluetoothSender med adresse og handler.
     * @param destAddr Bluetooth-adresse på modtageren.
     * @param handler Pointer til VarHandler-objektet.
     */
    BluetoothSender(const std::string& destAddr, VarHandler* handler);

    /**
     * @brief Starter main loop for Bluetooth-kommunikation.
     */
    void run();

private:
    std::string destAddr;                // Bluetooth-adresse på PSoC
    VarHandler* handler;                 // Pointer til VarHandler-objektet
    struct sockaddr_rc addr;             // Bluetooth socket-adresse
    int s;                               // Socket descriptor
    char buffer[1024];                   // Buffer til modtagelse af data
    std::string receivedMessageBuffer;   // Modtaget besked
    std::string lastSentMessage;         // Sidst sendte besked
    bool resendLastMessage;              // Flag for om sidste besked skal gensendes
    int retryCount;                      // Antal forsøg
    const int maxRetries = 5;            // Maksimalt antal forsøg

    /**
     * @brief Forsøger at oprette forbindelse til Bluetooth-enheden, indtil det lykkes.
     */
    void connectLoop();

    /**
     * @brief Sætter modtagelsestimeout på socket.
     */
    void setTimeout();

    /**
     * @brief Forsøger at genoprette forbindelse, hvis forbindelsen mistes.
     */
    void reconnect();

    /**
     * @brief Sender beskeder og håndterer modtagelse af ACK/NACK.
     */
    void sendAndReceive();

};

/**
 * @brief Wrapper-funktionen anvendes til at starte BluetoothSender.
 * @param destAddr Bluetooth-adresse på modtageren.
 * @param handler Pointer til VarHandler-objektet.
 */
void bluetoothSenderLoop(const std::string& destAddr, VarHandler* handler);