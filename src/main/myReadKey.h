#ifndef MYSIMPLECOMPUTER_MYREADKEY_H
#define MYSIMPLECOMPUTER_MYREADKEY_H

#include <termios.h>

enum keys {
    NONE, F5, F6, LOAD, SAVE, RUN, STEP, RESET, EXIT, UP, LEFT, RIGHT, DOWN, EDIT
};

void rk_terminit();

void rk_termdefault(struct termios *);

int rk_readkey(enum keys *);

int rk_mytermsave(struct termios *);

int rk_mytermrestore(struct termios *);

int rk_mytermregime(struct termios const *, int, int, int, int, int);

#endif //MYSIMPLECOMPUTER_MYREADKEY_H
