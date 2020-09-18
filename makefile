# GRR20196049 Iago Mello Floriano
CC = gcc
CFLAGS = -Wall
BINARIES = wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat
WAVLIBSo = wavlib.o wavio.o wavflags.o
WAVLIBSh = wavlib.h wavio.h wavflags.h

all: ${BINARIES}

# compiling of programs
wavrev: wavrev.o ${WAVLIBSo}
wavinfo: wavinfo.o wavlib.o wavflags.o
wavvol: wavvol.o ${WAVLIBSo}
wavnorm: wavnorm.o ${WAVLIBSo}
wavecho: wavecho.o ${WAVLIBSo}
wavwide: wavwide.o ${WAVLIBSo}
wavcat: wavcat.o wavlib.o
wavmix: wavmix.o wavlib.o

# compiling objects
wavio.o: wavio.c wavio.h
wavlib.o: wavlib.c wavlib.h
wavflags.o: wavflags.c wavflags.h
wavvol.o: wavvol.c ${WAVLIBSh}
wavinfo.o: wavinfo.c wavlib.h wavflags.h
wavnorm.o: wavnorm.c ${WAVLIBSh}
wavrev.o: wavrev.c ${WAVLIBSh}
wavecho.o: wavecho.c ${WAVLIBSh}
wavwide.o: wavwide.c ${WAVLIBSh}
wavcat.o: wavcat.c wavlib.h
wavmix.o: wavmix.c wavlib.h

# deletion of temporary files
clean: 
	rm -f *.o

# deletion of everything that isnt source code
purge: clean
	rm -f ${BINARIES}