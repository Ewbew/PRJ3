#pragma once

#include <string>
#include "VarHandler.h"
/**
 * @brief Main loop til afsendelse og modtagelse af Bluetooth meddelelser.
 *
 * Håndterer Bluetooth-forbindelsen, sender beskeder genereret af Varhandler,
 * og håndterer ACK/NACK svar. Håndterer genkobling og retry-logik.
 *
 * @param destAddr Destinationsenheden, PSoC'ens bluetooth-adresse.
 * @param handler Pointer til VarHandler-objektet, som styrer generering og hånstering af beskeder.
*/
// Function declaration for the Bluetooth sender loop
void bluetoothSenderLoop(const std::string& destAddr, VarHandler* handler);