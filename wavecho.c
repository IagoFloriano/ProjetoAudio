// GRR20196049 Iago Mello Floriano

#include "wavflags.h"
#include "wavio.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

void printUsage(char *program) {
  fprintf(stderr, "Incorrect usage of program, example of correct usage:\n%s -t 500 -l 0.5 -i input.wav -o output.wav\n");
  exit(1);
}

int main(int argc, char **argv) {
  WAV_t wav;
  WavFlags_t flags;
  //get input
  if (wavflags(argc, argv, "i:o:l:t:", &flags) == -1)
    printUsage(argv[0]);
  checkInput(flags, &wav);

  //output file
  checkOutput(flags, &wav);

  //free used space
  free(wav.data.array1b);

  return 0;
}