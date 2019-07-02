#include <fcntl.h>

#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "myUserInterface.h"
#include "myTerm.h"
#include "mySimpleComputer.h"

void settimer(int sec) {
    struct itimerval nval, oval;
    nval.it_interval.tv_sec = sec;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = sec;
    nval.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &nval, &oval);
}

void signalhandler(int signo) {
    switch (signo) {
        case SIGALRM:
            instructionCounter++;
            displayAll();
            break;
        case SIGUSR1:
            settimer(0);
            reset();
            break;
        default:
            exit(0);
    }
}

int main() {
    enum keys key = NONE;
    sc_memoryinit();
    sc_reginit();
    rk_terminit();
    mt_setcurs(0);
    signal(SIGALRM, signalhandler);
    signal(SIGUSR1, signalhandler);
    while (key != EXIT) {
        displayAll();
        rk_readkey(&key);
        switch (key) {
            case RIGHT:
                if (instructionCounter < MEMSIZE - 1) instructionCounter++;
                break;
            case LEFT:
                if (instructionCounter > 0) instructionCounter--;
                break;
            case UP:
                if (instructionCounter - 10 >= 0) instructionCounter -= 10;
                break;
            case DOWN:
                if (instructionCounter + 10 < MEMSIZE) instructionCounter += 10;
                break;
            case SAVE:
                sc_memorysave("memory.dat");
                break;
            case LOAD:
                sc_memoryload("memory.dat");
                break;
            case F5:
                sc_memoryset(instructionCounter, promptForInt("Enter the value:"));
                break;
            case F6:
                instructionCounter = promptForInt("Enter the pointer:");
                break;
            case RUN:
                settimer(1);
                break;
            case RESET:
                raise(SIGUSR1);
                break;
            default:
                break;
        }
    }
    mt_setcurs(1);
    return 0;
}