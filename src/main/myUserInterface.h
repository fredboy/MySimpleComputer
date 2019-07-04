#ifndef MYSIMPLECOMPUTER_MYUSERINTERFACE_H
#define MYSIMPLECOMPUTER_MYUSERINTERFACE_H

#include "myReadKey.h"

int promptForInt(const char *);

char *promptForString(const char *, char *);

void printValue(int, int);

void displayMemory();

void displayAccumulator();

void displayBigCharArea();

void displayCounter();

void displayOperation();

void displayFlags();

void displayMenu();

void displayAll();

void reset();

#endif //MYSIMPLECOMPUTER_MYUSERINTERFACE_H
