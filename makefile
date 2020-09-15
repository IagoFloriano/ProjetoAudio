# GRR20196049 Iago Mello Floriano
CC = gcc
CFLAGS = -Wall
executables = wavinfo

all: ${executables}

# compiling of programs
wavinfo: wavinfo.o wavlib.o wavflags.o

# compiling objects
wavlib.o: wavlib.c wavlib.h
wavflags.o: wavflags.c wavflags.h
wavinfo.o: wavinfo.c wavlib.h wavflags.h

# deletion of temporary files
clean: 
	rm -f *.o

# deletion of everything that isnt source code
purge: clean
	rm -f ${executables}