#define CTEST_MAIN

#include <ctest.h>
#include <mySimpleComputer.h>

CTEST(SC, MEMORY_SET) {
    ASSERT_EQUAL(0, sc_memoryset(64, 0xFF));
}

CTEST(SC, MEMORY_SET_OUTOFMEM) {
    ASSERT_EQUAL(-1, sc_memoryset(128, 0xFF));
}

CTEST(SC, MEMORY_GET) {
    int value = 0;
    ASSERT_EQUAL(0, sc_memoryget(64, &value));
    ASSERT_EQUAL(0xFF, value);
}

CTEST(SC, MEMORY_GET_OUTOFMEM) {
    int value = 64;
    ASSERT_EQUAL(-1, sc_memoryget(128, &value));
    ASSERT_EQUAL(64, value);
}

CTEST(SC, REG_SET) {
    sc_reginit();
    ASSERT_EQUAL(0, sc_regset(2, 1));
    ASSERT_EQUAL(4, sc_registry);
}

CTEST(SC, REG_SET_BAD) {
    sc_reginit();
    ASSERT_EQUAL(-1, sc_regset(2, 2));
    ASSERT_EQUAL(0, sc_registry);
}

CTEST(SC, REG_GET) {
    sc_registry = 8;
    int value = 0;
    ASSERT_EQUAL(0, sc_regget(3, &value));
    ASSERT_EQUAL(1, value);
}

CTEST(SC, COMMAND_ENCODE) {
    int command = 0;
    ASSERT_EQUAL(0, sc_commandencode(32, 2, &command));
    ASSERT_EQUAL(4098, command);
}

CTEST(SC, COMMAND_DECODE) {
    unsigned int opcode = 0, operand = 0;
    ASSERT_EQUAL(0, sc_commanddecode(4098, &opcode, &operand));
    ASSERT_EQUAL(32, opcode);
    ASSERT_EQUAL(2, operand);
}

int main(int argc, const char **argv) {
    sc_memoryinit();
    sc_reginit();
    return  ctest_main(argc, argv);
}