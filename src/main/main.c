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
    int sigignore;
    sc_regget(SIGIGNORE, &sigignore);
    if (!sigignore) {
        switch (signo) {
            case SIGALRM:
                displayAll();
                CU();
                instructionCounter++;
                break;
            case SIGUSR1:
                sc_regset(CLKIGNORE, 0);
                settimer(0);
//            reset();
                break;
            default:
                exit(0);
        }
    }
}

int load_program() {
	char filename[256];
	promptForString("Path to executable:", filename);
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) return -1;
    while (!feof(file)) {
        int address, command;
        fread(&address, sizeof(address), 1, file);
        fread(&command, sizeof(command), 1, file);
        sc_memoryset(address, command);
    }
    fclose(file);
    return 0;
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
//        key = NONE;
        int ignore = 0;
        sc_regget(CLKIGNORE, &ignore);
        if (!ignore) {
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
                    sc_setaccumulator(promptForInt("Enter the value:"));
                    break;
                case F6:
                    instructionCounter = promptForInt("Enter the pointer:");
                    break;
                case RUN:
                    load_program();
                    sc_regset(CLKIGNORE, 1);
                    settimer(1);
                    break;
                case EXEC:
                    CU();
                    break;
                case RESET:
                    raise(SIGUSR1);
                    break;
                default:
                    break;
            }
        }
//        sc_reginit();
    }
    mt_setcurs(1);
    return 0;
}