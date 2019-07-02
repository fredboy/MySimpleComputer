#ifndef MYSIMPLECOMPUTER_MYBIGCHARS_H
#define MYSIMPLECOMPUTER_MYBIGCHARS_H

#include "myTerm.h"

#define ENTER_MODE "\E(0"
#define EXIT_MODE "\E(B"


int bc_printA(char *);

int bc_box(int, int, int, int);

int bc_printbigchar(int *, int, int, enum colors, enum colors);

int bc_setbigcharpos(int *, int, int, int);

int bc_getbigcharpos(int *, int, int, int *);

int bc_bigcharwrite(int, int *, int);

int bc_bigcharread(int, int *, int, int *);

void bc_getbigchar(int *, int);

#endif //MYSIMPLECOMPUTER_MYBIGCHARS_H
