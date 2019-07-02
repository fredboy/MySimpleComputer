#include "mySimpleComputer.h"
#include "myTerm.h"

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

int sc_commandencode(int opcode, int operand, int *value) {
    if (opcode > 0xFF || operand > 0xFF) {
        sc_regset(CMDERROR, 1);
        return -1;
    } else {
        *value = (opcode << 7) | operand;
        return 0;
    }
}

int sc_commanddecode(int value, int *opcode, int *operand) {
    if (value > 0) {
        *opcode = (value >> 7) & 0x7F;
        *operand = value & 0x7F;
        return 0;
    } else {
        sc_regset(CMDERROR, 1);
        return -1;
    }
}

int ALU(int command, int operand) {

}

int CU() {
    int memvalue = 0;
    sc_memoryget(instructionCounter, &memvalue);

}
