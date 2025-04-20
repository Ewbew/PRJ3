#pragma once

class VarHandler {
public:
    void setVar1(const int& newValue);
    int getVar1() const;
    void setVar2(const int& newValue);
    int getVar2() const;

private:
    int value1;
    int value2;
};
