// GRR 20196049 Iago Mello Floriano
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// internal function do read the header
void readHeader(FILE *f, WAVHEADER_t *header) {
  fread(header, sizeof(WAVHEADER_t), 1, f);
}

int readHeaderInput(char *path, WAVHEADER_t *header) {
  // oppen file
  FILE *f = stdin;
  if (path) {
    f = fopen(path, "r");
    // test if file exists
    if (!f)
      return -1;
  }
  readHeader(f, header);
  return 2;
}