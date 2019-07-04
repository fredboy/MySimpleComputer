#include <string.h>

#include "parser.h"

int parse_address(const char *line) {
    if (line[0] < '0' || line[0] > '9' || line[1] < '0' || line[1] > '9') return -1;
    return 10 * (line[0] - '0') + (line[1] - '0');
}

int parse_opcode(const char *line) {
    int i = 2;
    while (line[i] == ' ') i++;
    if (line[i] == '\0') return -1;
    int j = i;
    while (line[j] != ' ') {
        j++;
        if (line[j] == '\0') return -1;
    }
    char opname[8];
    memcpy(opname, &line[i], (j - i) * sizeof(char));
    opname[j - i] = '\0';

    if (strcmp(opname, "READ") == 0) return 0x10;
    else if (strcmp(opname, "WRITE") == 0) return 0x11;
    else if (strcmp(opname, "LOAD") == 0) return 0x20;
    else if (strcmp(opname, "STORE") == 0) return 0x22;
    else if (strcmp(opname, "ADD") == 0) return 0x30;
    else if (strcmp(opname, "SUB") == 0) return 0x31;
    else if (strcmp(opname, "DIVIDE") == 0) return 0x32;
    else if (strcmp(opname, "MUL") == 0) return 0x33;
    else if (strcmp(opname, "JUMP") == 0) return 0x40;
    else if (strcmp(opname, "JNEG") == 0) return 0x41;
    else if (strcmp(opname, "JZ") == 0) return 0x42;
    else if (strcmp(opname, "HALT") == 0) return 0x43;
    else return -1;
}

int parse_operand(const char *line) {
    int i = 2;
    while (line[i] < '0' || line[i] > '9') {
        i++;
        if (line[i] == '\0') return -1;
    }
    return 10 * (line[i] - '0') + (line[i + 1] - '0');
}

