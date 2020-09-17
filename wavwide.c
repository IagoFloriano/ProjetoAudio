// GRR20196049 Iago Mello Floriano

#include "wavflags.h"
#include "wavio.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

void printUsage(char *program) {
  fprintf(stderr, "Program was used incorreclty, example of how to use:\n%s -i input.wav -o output.wav -l 5.2\n", program);
  exit(1);
}

// Aplies the desired effect
void applyWide(WAVData_t *audio, float k) {
  for (int i = 0; i + 1 < audio->audioSize; i += 2) {
    int64_t diff;
    switch (audio->numbytes) {
    case 1:
      diff = (audio->array1b)[i] - (audio->array1b)[i + 1];
      (audio->array1b)[i] += k * diff;
      (audio->array1b)[i] -= k * diff;
      break;
    case 2:
      diff = (audio->array2b)[i] - (audio->array2b)[i + 1];
      (audio->array2b)[i] += k * diff;
      (audio->array2b)[i] -= k * diff;
      break;
    case 3:
      diff = (audio->array3b)[i] - (audio->array3b)[i + 1];
      (audio->array3b)[i] += k * diff;
      (audio->array3b)[i] -= k * diff;
      break;
    case 4:
      diff = (audio->array4b)[i] - (audio->array4b)[i + 1];
      (audio->array4b)[i] += k * diff;
      (audio->array4b)[i] -= k * diff;
      break;
    }
  }
}

int main(int argc, char **argv) {
  WAV_t wav;
  WavFlags_t flags;
  // Read desired file
  if (wavflags(argc, argv, "i:o:l:", &flags) == -1)
    printUsage(argv[0]);
  checkInput(flags, &wav);

  // Tests if audio is stereo
  if (wav.header.fmt.NumChannels != 2) {
    fprintf(stderr, "Input audio doesn't have 2 channels so there is nothing to be done\n");
    free(wav.data.array1b);
    return (2);
  }

  // Prepares variables so the effect can be applied correctly
  float k = 1.0;
  if (flags.lFlag) {
    k = atof(flags.lFlag);
    if (k > 10.0)
      k = 10.0;
    else if (k < 0.0)
      k = 0.0;
  }

  // Applies the effect
  applyWide(&(wav.data), k);

  // Output file
  checkOutput(flags, &wav);

  // frees used space
  free(wav.data.array1b);

  return 0;
}