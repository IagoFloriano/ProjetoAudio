#include "wavio.h"
#include "wavflags.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

// Function to read the input exiting the program on exeption cases
void checkInput(WavFlags_t flags, WAV_t *wav) {
  int initializeResult;
  FILE *f;
  initializeResult = initializeWav(flags.iFlag, wav, &f);

  if (initializeResult == -1) {
    fprintf(stderr, "Unable to allocate space for the audio\n");
    exit(1);
  }
  if (initializeResult == -2) {
    fprintf(stderr, "Unable to open file\n");
    exit(2);
  }

  readAudioData(f, wav);
  fclose(f);
}

// outputs the wav file taking care of the flags used as output
void checkOutput(WavFlags_t flags, WAV_t *wav) {
  FILE *f = stdout;
  if (flags.oFlag)
    f = fopen(flags.oFlag, "w");
  if (!f) {
    fprintf(stderr, "Unable to create file %s\n", flags.oFlag);
    exit(2);
  }

  writeWav(f, wav);
  fclose(f);
}