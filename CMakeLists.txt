cmake_minimum_required(VERSION 3.24)
project(untitled11 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled11 Card/card.c Card/card.h Terminal/terminal.h Terminal/terminal.c Server/server.c Server/server.h Application/application.c Application/application.h main.c Card/test.c STD_Types.h Terminal/testTerminal.c Server/serverTest.c Server/db.c Server/db.h)
