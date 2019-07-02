#include "myTerm.h"

int mt_clrscr() {
    printf(CLS);
    return 0;
}

int mt_setcurs(int curs) {
    if (curs < 0 || curs > 1) return -1;
    printf(curs ? SHOWC : HIDEC);
    return 0;
}

int mt_goto(int y, int x) {
    if ((x >= 0) && (y >= 0)) {
        printf(POS, y, x);
        return 0;
    } else return -1;
}

int mt_getscreensize(int *rows, int *cols) {
    struct winsize w;
    if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) {
        *rows = w.ws_row;
        *cols = w.ws_col;
        return 0;
    } else return -1;
}

int mt_setfgcolor(enum colors color) {
    printf(FGCOLOR, color);
    return 0;
}

int mt_setbgcolor(enum colors color) {
    printf(BGCOLOR, color);
    return 0;
}

