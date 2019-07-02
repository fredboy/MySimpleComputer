#include <stdio.h>
#include <stdlib.h>

#include "mySimpleComputer.h"
#include "myBigChars.h"

int bc_printA(char *str) {
    printf(ENTER_MODE);
    printf("%s", str);
    printf(EXIT_MODE);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    int i;
    mt_goto(x1, y1);
    bc_printA("l");
    for (i = 0; i < y2 - 2; i++) {
        bc_printA("q");
    }
    bc_printA("k");
    for (i = 1; i <= x2 - 2; i++) {
        mt_goto(x1 + i, y1);
        bc_printA("x");
        mt_goto(x1 + i, y1 + y2 - 1);
        bc_printA("x");
    }
    mt_goto(x1 + x2 - 1, y1);
    bc_printA("m");
    for (i = 0; i < y2 - 2; i++) {
        bc_printA("q");
    }
    bc_printA("j");
    return 0;
}

int bc_printbigchar(int *big, int x, int y, enum colors fgColor, enum colors bgColor) {
    int bcByte, bcBit;
    char str[8];
    mt_goto(x, y);
    mt_setfgcolor(fgColor);
    mt_setbgcolor(bgColor);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            bcByte = (big[i] >> (j * 8)) & 0xFF;
            for (int k = 0; k < 8; k++) {
                bcBit = (bcByte & (1 << k)) >> k;
                str[k] = bcBit ? 'a' : ' ';
                mt_goto(x + (i * 4) + j, y);
                bc_printA(str);
            }
        }
    }
    return 0;
}

int bc_setbigcharpos(int *big, int x, int y, int value) {
    if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 0) return -1;

    int index = x < 4 ? 0 : 1;
    if (value == 1) big[index] |= 1 << (x * 8 + y);
    else big[index] &= ~(1 << (x * 8 + y));
    return 0;
}

int bc_getbigcharpos(int *big, int x, int y, int *value) {
    if (x < 0 || x > 7 || y < 0 || y > 7) return -1;

    int index = x < 4 ? 0 : 1;
    *value = ((big[index] >> (x * 8)) >> y) & 1;
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count) {
    while (count > 0) {
        if (write(fd, big, sizeof(int) * 2) == -1) return -1;
        count--;
    }
    return 0;
}

int bc_bigcharread(int fd, int *big, int need_count, int *count) {
    while (need_count > 0) {
        if (read(fd, big, sizeof(int) * 2) == -1) return -1;
        need_count--;
        *count = *count + 1;
    }
    return 0;
}

void bc_getbigchar(int *big, int value) {
    switch (value) {
        case '-':
            big[0] = 0b11111111000000000000000000000000;
            big[1] = 0b00000000000000000000000000000000;
            break;
        case '+':
            big[0] = 0b00011000000110000000000000000000;
            big[1] = 0b00000000000110000001100011111111;
            break;
        case '0':
            big[0] = 0b10000001100000011000000111111111;
            big[1] = 0b11111111100000011000000110000001;
            break;
        case '1':
            big[0] = 0b11000000110110001111000011100000;
            big[1] = 0b11000000110000001100000011000000;
            break;
        case '2':
            big[0] = 0b11111111110000001100000011111111;
            big[1] = 0b11111111000000110000001100000011;
            break;
        case '3':
            big[0] = 0b11111111110000001100000011111111;
            big[1] = 0b11111111110000001100000011000000;
            break;
        case '4':
            big[0] = 0b11111111110000111100001111000011;
            big[1] = 0b11000000110000001100000011000000;
            break;
        case '5':
            big[0] = 0b11111111000000110000001111111111;
            big[1] = 0b11111111110000001100000011000000;
            break;
        case '6':
            big[0] = 0b11111111000000110000001111111111;
            big[1] = 0b11111111110000111100001111000011;
            break;
        case '7':
            big[0] = 0b11000000110000001100000011111111;
            big[1] = 0b11000000110000001100000011000000;
            break;
        case '8':
            big[0] = 0b11111111110000111100001111111111;
            big[1] = 0b11111111110000111100001111000011;
            break;
        case '9':
            big[0] = 0b11111111110000111100001111111111;
            big[1] = 0b11111111110000001100000011000000;
            break;
        case 'A':
            big[0] = 0b11111111100000011000000111111111;
            big[1] = 0b10000001100000011000000110000001;
            break;
        case 'B':
            big[0] = 0b11111111001000010010000100111111;
            big[1] = 0b11111111100000011000000110000001;
            break;
        case 'C':
            big[0] = 0b00000001000000010000001011111100;
            big[1] = 0b11111100000000100000000100000001;
            break;
        case 'D':
            big[0] = 0b10000001010000010010000100011111;
            big[1] = 0b00011111001000010100000110000001;
            break;
        case 'E':
            big[0] = 0b00111111000000010000000111111111;
            big[1] = 0b11111111000000010000000100000001;
            break;
        case 'F':
            big[0] = 0b00111111000000010000000111111111;
            big[1] = 0b00000001000000010000000100000001;
            break;
        default:
            big[0] = 0;
            big[1] = 0;
            break;
    }
}
