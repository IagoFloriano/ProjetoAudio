CC = gcc
CFLAGS = -Wall
executables = wavinfo

all: ${executables}

# compiling of programs
wavinfo: wavinfo.o wavlib.o

# compiling objects
wavlib.o: wavlib.c wavlib.h
wavinfo.o: wavinfo.c wavlib.h

# deletion of temporary files
clean: 
	rm -f *.o

# deletion of everything that isnt source code
purge: clean
	rm -f ${executables}