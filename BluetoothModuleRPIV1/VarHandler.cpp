#include "VarHandler.h"

void VarHandler::SetVar(const std::string& newValue) {
    value = newValue;
}

std::string VarHandler::GetVar() const {
    return value;
}
