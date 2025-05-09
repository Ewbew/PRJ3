#pragma once

#include <string>
#include "VarHandler.h"

// Function declaration for the Bluetooth sender loop
void bluetoothSenderLoop(const std::string& destAddr, VarHandler* handler);
