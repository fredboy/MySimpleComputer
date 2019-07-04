#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "myUserInterface.h"
#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"

int opcode, operand, value, big[2] = {0, 0};

int promptForInt(const char *text) {
    sc_regset(SIGIGNORE, 1);
    mt_setbgcolor(WHITE);
    mt_setfgcolor(GREEN);
    for (int i = 2; i < 84; i++) {
        for (int j = 5; j < 10; j++) {
            mt_goto(j, i);
            printf(ENTER_MODE);
            printf(" ");
            printf(EXIT_MODE);
        }
    }
    mt_setbgcolor(BLACK);
    for (int i = 5; i < 81; i++) {
        mt_goto(7, i);
        printf(ENTER_MODE);
        printf(" ");
        printf(EXIT_MODE);
    }
    mt_setbgcolor(WHITE);
    bc_box(5, 3, 5, 80);
    mt_goto(6, 5);
    mt_setfgcolor(RED);
    printf("%s", text);
    mt_goto(7, 5);
    mt_setbgcolor(BLACK);
    mt_setfgcolor(DEFAULT);
    int input;
    scanf("%i", &input);
    mt_setbgcolor(DEFAULT);
    sc_regset(SIGIGNORE, 0);
    return input;
}

char *promptForString(const char *text, char *input) {
    sc_regset(SIGIGNORE, 1);
    mt_setbgcolor(WHITE);
    mt_setfgcolor(GREEN);
    for (int i = 2; i < 84; i++) {
        for (int j = 5; j < 10; j++) {
            mt_goto(j, i);
            printf(ENTER_MODE);
            printf(" ");
            printf(EXIT_MODE);
        }
    }
    mt_setbgcolor(BLACK);
    for (int i = 5; i < 81; i++) {
        mt_goto(7, i);
        printf(ENTER_MODE);
        printf(" ");
        printf(EXIT_MODE);
    }
    mt_setbgcolor(WHITE);
    bc_box(5, 3, 5, 80);
    mt_goto(6, 5);
    mt_setfgcolor(RED);
    printf("%s", text);
    mt_goto(7, 5);
    mt_setbgcolor(BLACK);
    mt_setfgcolor(DEFAULT);
    scanf("%s", input);
    mt_setbgcolor(DEFAULT);
    sc_regset(SIGIGNORE, 0);
    return input;
}


void printValue(int pointer, int val) {
    sc_regset(SIGIGNORE, 1);
    mt_setbgcolor(WHITE);
    mt_setfgcolor(GREEN);
    for (int i = 2; i < 84; i++) {
        for (int j = 5; j < 10; j++) {
            mt_goto(j, i);
            printf(ENTER_MODE);
            printf(" ");
            printf(EXIT_MODE);
        }
    }
    bc_box(5, 3, 5, 80);
    mt_goto(6, 5);
    mt_setfgcolor(RED);
    printf("Value at 0x%04X: 0x%04X\n", pointer, val);
    mt_goto(7, 5);
    printf("Press any key to close this message.\n");
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(DEFAULT);
    enum keys key;
    rk_readkey(&key);
    sc_regset(SIGIGNORE, 0);
}

void displayMemory() {
    int k = 2;
    mt_setfgcolor(BLUE);
    mt_setbgcolor(DEFAULT);
    bc_box(1, 1, 12, 62);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(BLUE);
    mt_goto(1, 29);
    printf(" Memory ");
    mt_goto(2, 2);

    for (int i = 0; i < MEMSIZE; i++) {
        mt_setbgcolor(DEFAULT);
        if (instructionCounter == i) mt_setbgcolor(RED);
        sc_memoryget(i, &value);
        if (value >= 0) {
            printf("+%04X ", value);
        } else {
            printf("-%04X ", (-1) * value);
        }
        if ((i + 1) % 10 == 0) {
            k++;
            mt_goto(k, 2);
        }
    }
}

void displayAccumulator() {
    mt_setfgcolor(BLUE);
    mt_setbgcolor(DEFAULT);
    bc_box(1, 63, 3, 22);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(BLUE);
    mt_goto(1, 67);
    printf(" Accumulator ");
    mt_setbgcolor(DEFAULT);
    mt_goto(2, 71);
    sc_getaccumulator(&value);
    if (value >= 0) {
        printf("+%04X ", value);
    } else {
        printf("-%04X ", (-1) * value);
    }
}

void displayCounter() {
    mt_setfgcolor(BLUE);
    mt_setbgcolor(DEFAULT);
    bc_box(4, 63, 3, 22);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(BLUE);
    mt_goto(4, 64);
    printf(" instructionCounter ");
    mt_setbgcolor(DEFAULT);
    mt_goto(5, 71);
    printf("+%04X", instructionCounter);
}

void displayOperation() {
    mt_setfgcolor(BLUE);
    mt_setbgcolor(DEFAULT);
    bc_box(7, 63, 3, 22);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(BLUE);
    mt_goto(7, 68);
    printf(" Operation ");
    mt_setbgcolor(DEFAULT);
    sc_memoryget(instructionCounter, &value);
    sc_commanddecode(value, &opcode, &operand);
    mt_goto(8, 64);
    printf("OC: %2d | OP: %d", opcode, operand);
}

void displayFlags() {
    mt_setfgcolor(BLUE);
    mt_setbgcolor(DEFAULT);
    bc_box(10, 63, 3, 22);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(BLUE);
    mt_goto(10, 70);
    printf(" Flags ");
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(DEFAULT);
    for (int i = 0; i < REGSIZE; i++) {
        mt_goto(11, 74 - REGSIZE + i * 2);
        int flag = 0;
        sc_regget(i, &flag);
        printf("%x ", flag);
    }
}

void displayMenu() {
    mt_setfgcolor(BLUE);
    mt_setbgcolor(DEFAULT);
    bc_box(13, 47, 10, 38);
    mt_goto(13, 49);
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(BLUE);
    printf(" Keys: ");
    mt_setbgcolor(DEFAULT);
    mt_goto(14, 48);
    printf("L  - Load");
    mt_goto(15, 48);
    printf("S  - Save");
    mt_goto(16, 48);
    printf("R  - Run");
    mt_goto(17, 48);
    printf("T  - Execute");
    mt_goto(18, 48);
    printf("I  - Reset");
    mt_goto(19, 48);
    printf("F5 - Accumulator");
    mt_goto(20, 48);
    printf("F6 - instructionCounter");
    mt_goto(21, 48);
    printf("Q - Exit");
}

void displayBigCharArea() {
    mt_setfgcolor(BLUE);
    mt_setbgcolor(DEFAULT);
    bc_box(13, 1, 10, 46);

    char buffer[20];

    sc_memoryget(instructionCounter, &value);
    if (value >= 0) {
        sprintf(buffer, "+%04X", value);
    } else {
        sprintf(buffer, "-%04X", value);
    }

    for (int i = 0; i < 5; i++) {
        bc_getbigchar(big, buffer[i]);
        bc_printbigchar(big, 14, 2 + i * 9, DEFAULT, DEFAULT);
    }
}

void displayAll() {
    mt_clrscr();
    displayMemory();
    displayAccumulator();
    displayCounter();
    displayOperation();
    displayFlags();
    displayMenu();
    displayBigCharArea();
    mt_setfgcolor(DEFAULT);
    mt_setbgcolor(DEFAULT);
    printf("\n\n");
}

void reset() {
    sc_memoryinit();
    sc_reginit();
}
