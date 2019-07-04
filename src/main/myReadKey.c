#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "myReadKey.h"
#include "myTerm.h"

struct termios __term_state;

void rk_terminit() {
    rk_mytermsave(&__term_state);
}

void rk_termdefault(struct termios *termState) {
    *termState = __term_state;
}

int rk_readkey(enum keys *key) {
    int term = open(TERM, O_RDWR);
    char buf;

    struct termios termState = __term_state;
    rk_mytermregime(&termState, 0, 1, 1, 0, 0);
    read(term, &buf, 1);

    switch (buf) {
        case 'q':
            *key = EXIT;
            break;
        case 'l':
            *key = LOAD;
            break;
        case 's':
            *key = SAVE;
            break;
        case 'r':
            *key = RUN;
            break;
        case 't':
            *key = EXEC;
            break;
        case 'i':
            *key = RESET;
            break;
        case 'e':
            *key = EDIT;
            break;
        case '\E':
            read(term, &buf, 1);
            read(term, &buf, 1);
            switch (buf) {
                case 65:
                    *key = UP;
                    break;
                case 66:
                    *key = DOWN;
                    break;
                case 67:
                    *key = RIGHT;
                    break;
                case 68:
                    *key = LEFT;
                    break;
                case '1':
                    read(term, &buf, 1);
                    if (buf == '5') {
                        read(term, &buf, 1);
                        if (buf == '~') *key = F5;
                    }
                    if (buf == '7') {
                        read(term, &buf, 1);
                        if (buf == '~') *key = F6;
                    }
                    break;
                default:
                    *key = NONE;
            }
            break;
        default:
            *key = NONE;
            break;
    }
    rk_mytermregime(&termState, 1, 0, 0, 1, 1);
    close(term);
    return 0;
}

int rk_mytermregime(struct termios const *currState, int regime, int vtime, int vmin, int echo, int sigint) {
    if (regime < 0 || regime > 1 || echo < 0 || echo > 1 || sigint < 0 || sigint > 1) return -1;

    struct termios newTermState = *currState;

    if (regime == 1)
        newTermState.c_lflag |= ICANON;
    else
        newTermState.c_lflag &= ~ICANON;

    if (echo == 1)
        newTermState.c_lflag |= ECHO;
    else
        newTermState.c_lflag &= ~ECHO;

    if (sigint == 1)
        newTermState.c_lflag |= ISIG;
    else
        newTermState.c_lflag &= ~ISIG;

    newTermState.c_cc[VMIN] = vmin;
    newTermState.c_cc[VTIME] = vtime;
    tcsetattr(0, TCSANOW, &newTermState);

    return 0;
}

int rk_mytermsave(struct termios *termState) {
    return tcgetattr(1, termState);
}

int rk_mytermrestore(struct termios *termState) {
    return tcsetattr(1, TCSADRAIN, termState);
}
