#ifndef MYSIMPLECOMPUTER_MYTERM_H
#define MYSIMPLECOMPUTER_MYTERM_H

#define BGCOLOR "\E[4%dm"
#define FGCOLOR "\E[3%dm"
#define CLS "\E[H\E[J"
#define POS "\E[%d;%dH"
#define HIDEC "\E[?25l"
#define SHOWC "\E[?25h"
#define TERM "/dev/tty"

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

enum colors {
    DEFAULT = 9, BLACK = 0, WHITE = 7, GREEN = 2, RED = 1, BLUE = 4
};


int mt_clrscr();

int mt_setcurs(int);

int mt_goto(int, int);

int mt_getscreensize(int *, int *);

int mt_setfgcolor(enum colors);

int mt_setbgcolor(enum colors);


#endif //MYSIMPLECOMPUTER_MYTERM_H
