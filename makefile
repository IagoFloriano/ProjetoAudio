# GRR20196049 Iago Mello Floriano
CC = gcc
CFLAGS = -Wall
executables = wavinfo wavvol wavnorm

all: ${executables}

# compiling of programs
wavinfo: wavinfo.o wavlib.o wavflags.o
wavvol: wavvol.o wavlib.o wavflags.o wavio.o
wavnorm: wavnorm.o wavlib.o wavflags.o wavio.o

# compiling objects
wavio.o: wavio.c wavio.h
wavlib.o: wavlib.c wavlib.h
wavflags.o: wavflags.c wavflags.h
wavvol.o: wavvol.c wavflags.h wavlib.h wavio.h
wavinfo.o: wavinfo.c wavlib.h wavflags.h
wavnorm.o: wavnorm.c wavlib.h wavlib.h wavio.h

# deletion of temporary files
clean: 
	rm -f *.o

# deletion of everything that isnt source code
purge: clean
	rm -f ${executables}