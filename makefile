CC = gcc
CFLAGS = -Wall
executables = wavinfo

all: ${executables}

wavinfo: wavinfo.c
	${CC} ${CFLAGS} wavinfo.c -o wavinfo