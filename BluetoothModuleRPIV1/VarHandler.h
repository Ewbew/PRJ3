#pragma once

#include <string>

class VarHandler {
public:
    void SetVar(const std::string& newValue);
    std::string GetVar() const;

private:
    std::string value;
};
