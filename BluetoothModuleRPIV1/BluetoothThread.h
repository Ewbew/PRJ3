#pragma once

#include <string>
#include "VarHandler.h"

void bluetoothSenderLoop(const std::string& destAddr, VarHandler* handler);
