#ifndef MYSIMPLECOMPUTER_MYSIMPLECOMPUTER_H
#define MYSIMPLECOMPUTER_MYSIMPLECOMPUTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define MEMSIZE 100
#define CMDSIZE 30
#define REGSIZE 5

#define OPOVERFLOW 0
#define DIVBYZERO  1
#define CLKIGNORE  2
#define OUTOFMEM   3
#define CMDERROR   4

int sc_memory[MEMSIZE];
int sc_registry, instructionCounter;

int sc_memoryinit();

int sc_memoryset(int, int);

int sc_memoryget(int, int *);

int sc_memorysave(char *);

int sc_memoryload(char *);

int sc_reginit();

int sc_regset(int, int);

int sc_regget(int, int *);

int sc_commandencode(int, int, int *);

int sc_commanddecode(int, int *, int *);


#endif //MYSIMPLECOMPUTER_MYSIMPLECOMPUTER_H
