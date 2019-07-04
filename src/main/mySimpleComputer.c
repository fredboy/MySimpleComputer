#include <signal.h>

#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myUserInterface.h"

#define READ        0x10
#define WRITE       0x11
#define LOAD        0x20
#define STORE       0x21
#define ADD         0x30
#define SUB         0x31
#define DIVIDE      0x32
#define MUL         0x33
#define JUMP        0x40
#define JNEG        0x41
#define JZ          0x42
#define HALT        0x43
#define JNS         0x55

int sc_memoryinit() {
    for (int i = 0; i < MEMSIZE; i++) sc_memory[i] = 0;
    instructionCounter = 0;
    return 0;
}

int sc_memoryset(int address, int value) {
    if (address >= 0 && address < MEMSIZE) {
        sc_memory[address] = value;
        return 0;
    } else {
        sc_regset(OUTOFMEM, 1);
        return -1;
    }
}

int sc_memoryget(int address, int *value) {
    if (address >= 0 && address < MEMSIZE) {
        *value = sc_memory[address];
        return 0;
    } else {
        sc_regset(OUTOFMEM, 1);
        return -1;
    }
}

int sc_memoryPrint() {
    for (int i = 0; i < 10; i++) {
        printf(" ");
        for (int j = 0; j < 10; j++) {
            printf("+%4d\t", sc_memory[(10 * i) + j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int sc_memorysave(char *filename) {
    FILE *file;
    file = fopen(filename, "wb");
    int temp;
    if (file == NULL) return -1;
    temp = fwrite(sc_memory, sizeof(*sc_memory) * MEMSIZE, 1, file);
    fclose(file);
    if (temp != 1) return -1;
    return 0;
}

int sc_memoryload(char *filename) {
    FILE *file;
    int temp;
    file = fopen(filename, "rb");
    if (file == NULL) return -1;
    temp = fread(sc_memory, sizeof(*sc_memory) * MEMSIZE, 1, file);
    fclose(file);
    if (temp != 1) return -1;
    return 0;
}

int sc_reginit() {
    sc_registry = 0;
    return 0;
}

int sc_regset(int reg, int value) {
    if (reg >= 0 && reg < REGSIZE) {
        switch (value) {
            case 0:
                sc_registry &= ~(1u << reg);
                break;
            case 1:
                sc_registry |= (1u << reg);
                break;
            default:
                return -1;
        }
    } else {
        return -1;
    }
    return 0;
}

int sc_regget(int reg, int *value) {
    if (reg >= 0 && reg < REGSIZE) {
        *value = ((sc_registry >> reg) & 1);
        return 0;
    } else return -1;
}

int sc_commandencode(int opcode, int operand, int *command) {
    if (opcode > 0xFF || operand > 0xFF) {
        sc_regset(CMDERROR, 1);
        return -1;
    } else {
        *command = (opcode << 7) | operand;
        return 0;
    }
}

int sc_commanddecode(int command, int *opcode, int *operand) {
    if (command > 0) {
        *opcode = (command >> 7) & 0x7F;
        *operand = command & 0x7F;
        return 0;
    } else {
        sc_regset(CMDERROR, 1);
        return -1;
    }
}

int sc_setaccumulator(int value) {
    if (value < 0 || value > 0xFFFF) return -1;
    accumulator = value;
}

int sc_getaccumulator(int *value) {
    *value = accumulator;
    return 0;
}

int ALU(int opcode, int operand) {
    int memval, accval;
    sc_memoryget(operand, &memval);
    sc_getaccumulator(&accval);
    switch (opcode) {
        case ADD:
            sc_setaccumulator(accval + memval);
            break;
        case SUB:
            sc_setaccumulator(accval - memval);
            break;
        case DIVIDE:
            if (memval == 0) sc_regset(DIVBYZERO, 1);
            else sc_setaccumulator(accval / memval);
            break;
        case MUL:
            sc_setaccumulator(accval * memval);
            break;
        default:
            sc_regset(CMDERROR, 1);
    }
}

int CU() {
    int command, opcode, operand, value;
    sc_memoryget(instructionCounter, &command);
    if (sc_commanddecode(command, &opcode, &operand) == -1) {
        sc_regset(CLKIGNORE, 1);
        return -1;
    }

    switch (opcode) {
        case READ:
            sc_memoryset(operand, promptForInt("Enter the value:"));
            break;
        case WRITE:
            sc_memoryget(operand, &value);
            printValue(operand, value);
            break;
        case LOAD:
            sc_memoryget(operand, &value);
            sc_setaccumulator(value);
            break;
        case STORE:
            sc_getaccumulator(&value);
            sc_memoryset(operand, value);
            break;
        case JUMP:
            instructionCounter = operand;
            break;
        case JNEG:
            if (accumulator < 0) instructionCounter = operand;
            break;
        case JZ:
            if (accumulator == 0) instructionCounter = operand;
            break;
        case JNS:
            if (accumulator > 0) instructionCounter = operand;
        case HALT:
            raise(SIGUSR1);
            break;
        default:
            ALU(opcode, operand);
    }
}
