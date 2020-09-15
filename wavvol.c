// GRR20196049 Iago Mello Floriano
#include "wavflags.h"
#include "wavlib.h"
#include <stdio.h>

void printUsage(char *program) {
  fprintf(stderr, "Correct usage is %s -i input.wav -o output.wav\n", program);
}

int main(int argc, char *argv[]) {
  WAV_t wav;
  WavFlags_t flags;

  // flags configuration
  if (wavflags(argc, argv, "iol", &flags) == -1)
    printUsage(argv[0]);
  //recieve input
  FILE *f;
  if (flags.iFlag > 0)
    initializeWav(argv[flags.iFlag], &wav, &f);
  else
    initializeWav(NULL, &wav, &f);

  readAudioData(f, &wav);
  fclose(f);

  //change volume

  //output
  writeWav(stdout, &wav);

  return 0;
}