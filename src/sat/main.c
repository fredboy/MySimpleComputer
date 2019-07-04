#include <stdio.h>
#include <string.h>
#include <mySimpleComputer.h>

#include "parser.h"

int main(int argc, const char **argv) {
    if (argc <= 1) {
        printf("Too few arguments\n");
        return 1;
    }
    if (argc >= 4) {
        printf("Too many arguments\n");
        return 1;
    }
    char infilename[64], outfilename[64];
    memcpy(infilename, argv[1], strlen(argv[1]) * sizeof(char));
    if (argc > 2) memcpy(outfilename, argv[2], strlen(argv[2]) * sizeof(char));
    else strcpy(outfilename, "out.o");
    FILE *infile = fopen(infilename, "r");
    FILE *outfile = fopen(outfilename, "wb");

    int read = 0;
    char *line = NULL;
    size_t len = 0;
    int address, opcode, operand, command;
    while ((read = getline(&line, &len, infile)) != -1) {
        address = parse_address(line);
        opcode = parse_opcode(line);
        operand = parse_operand(line);
        if (address == -1 || opcode == -1 || operand == -1) {
            printf("Error while parsing the file.\n");
            return 1;
        }
        fwrite(&address, sizeof(address), 1, outfile);
        sc_commandencode(opcode, operand, &command);
        fwrite(&command, sizeof(command), 1, outfile);
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}
