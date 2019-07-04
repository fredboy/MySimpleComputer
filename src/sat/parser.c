#include <string.h>

#include "parser.h"

int parse_address(const char *line) {
    return 10 * (line[0] - '0') + (line[1] - '0');
}