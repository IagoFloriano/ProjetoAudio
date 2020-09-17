// GRR20196049 Iago Mello Floriano

#include "wavflags.h"
#include "wavio.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

void printUsage(char *program) {
  fprintf(stderr, "Program was used incorreclty, example of how to use:\n%s -i input.wav -o output.wav -l 5\n", program);
  exit(1);
}

int main(int argc, char **argv) {
  WAV_t wav;
  WavFlags_t flags;
  // Read desired file
  if (wavflags(argc, argv, "i:o:l:", &flags) == -1)
    printUsage(argv[0]);
  checkInput(flags, &wav);

  // Output file
  checkOutput(flags, &wav);

  // frees used space
  free(wav.data.array1b);

  return 0;
}