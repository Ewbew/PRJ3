#include "shootVarHandler.h"


static shootVarHandler handler = {0, 0, 0};

// Getter-funktioner
int shootVarHandler_getDesiredPos1(void) {
    return handler.desiredPos1;
}

int shootVarHandler_getDesiredPos2(void) {
    return handler.desiredPos2;
}

int shootVarHandler_getShootMode(void) {
    return handler.shootMode;
}

// Setter-funktioner
void shootVarHandler_setDesiredPos1(int newPos1) {
    handler.desiredPos1 = newPos1;
}

void shootVarHandler_setDesiredPos2(int newPos2) {
    handler.desiredPos2 = newPos2;
}

void shootVarHandler_setShootMode(int newMode) {
    handler.shootMode = newMode;
}
