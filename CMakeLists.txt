cmake_minimum_required(VERSION 3.9)
project(mysimplecomputer C)

set(CMAKE_C_STANDARD 11)

add_executable(mysimplecomputer
        src/main/main.c
        src/main/mySimpleComputer.c
        src/main/mySimpleComputer.h
        src/main/myBigChars.c
        src/main/myBigChars.h
        src/main/myReadKey.c
        src/main/myReadKey.h
        src/main/myTerm.c
        src/main/myTerm.h
        src/main/myUserInterface.c
        src/main/myUserInterface.h)

add_executable(sat
        src/sat/main.c
        src/main/mySimpleComputer.c
        src/main/mySimpleComputer.h
        src/main/myBigChars.c
        src/main/myBigChars.h
        src/main/myReadKey.c
        src/main/myReadKey.h
        src/main/myTerm.c
        src/main/myTerm.h
        src/main/myUserInterface.c
        src/main/myUserInterface.h
        src/sat/parser.c
        src/sat/parser.h)

add_executable(mysimplecomputer_test
        src/test/main.c
        src/main/mySimpleComputer.c
        src/main/mySimpleComputer.h
        src/main/myBigChars.c
        src/main/myBigChars.h
        src/main/myReadKey.c
        src/main/myReadKey.h
        src/main/myTerm.c
        src/main/myTerm.h
        src/main/myUserInterface.c
        src/main/myUserInterface.h
        src/sat/parser.c
        src/sat/parser.h)

target_include_directories(mysimplecomputer_test PRIVATE src/main src/sat ctest)
target_include_directories(sat PRIVATE src/main)
