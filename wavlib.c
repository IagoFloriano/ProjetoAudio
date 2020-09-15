// GRR 20196049 Iago Mello Floriano
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ioflags(int argc, char **argv, int *iInput, int *iOutput) {
  // test if the pointers arent NULL
  if (iInput)
    *iInput = -1;
  if (iOutput)
    *iOutput = -1;

  // test if it is possible for one of this flags to exist
  if (argc < 3)
    return;

  for (int i = 1; i < argc; i++) {
    // both tests test if the pointer of isnt null so there is the possiblity of passing NULL
    // in case of one of the flags being undesired
    if (iInput && *iInput < 0 && !strcmp(argv[i], "-i")) { // test the -i flag
      if (i + 1 != argc)
        *iInput = i + 1;
    } else if (iOutput && *iOutput < 0 && !strcmp(argv[i], "-o")) { // test the -o flag
      if (i + 1 != argc)
        *iOutput = i + 1;
    }
  }
}

// internal function do read the header
void readHeader(FILE *f, WAVHEADER_t *header) {
  fread(header, sizeof(WAVHEADER_t), 1, f);
}

int readHeaderInput(int iInput, char **argv, WAVHEADER_t *header) {
  if (iInput < 0) {
    readHeader(stdin, header);
    return 1;
  }
  // oppen file
  FILE *f = fopen(argv[iInput], "r");
  // test if file exists
  if (!f)
    return -1;
  readHeader(f, header);
  return 2;
}