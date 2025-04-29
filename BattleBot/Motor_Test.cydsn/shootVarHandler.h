#ifndef SHOOTVARHANDLER_H
#define SHOOTVARHANDLER_H

// Gør strukturen synlig udenfor .c-filen
typedef struct {
    int desiredPos1;
    int desiredPos2;
    int shootMode;
} shootVarHandler;

// Getter-funktioner
int shootVarHandler_getDesiredPos1(void);
int shootVarHandler_getDesiredPos2(void);
int shootVarHandler_getShootMode(void);

// Setter-funktioner
void shootVarHandler_setDesiredPos1(int newPos1);
void shootVarHandler_setDesiredPos2(int newPos2);
void shootVarHandler_setShootMode(int newMode);

#endif // SHOOTVARHANDLER_H
