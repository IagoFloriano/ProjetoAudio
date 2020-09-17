// GRR20196049 Iago Mello Floriano

#include "wavflags.h"
#include "wavio.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

void printUsage(char *program) {
  fprintf(stderr, "Incorrect usage, example of correct usage:\n%s -i input -o output\n", program);
  exit(1);
}

// Inverts only the channel asked os an audio with "numchannels" channels
void invertChannel(WAVData_t *audio, int channel, int numchannels) {
  for (int i = channel - 1; i < audio->audioSize / 2; i += numchannels) {
    int indexOppsite = audio->audioSize - numchannels - i; // variable to store the value of the index that i will swap with

    // temporary varibles for swapping
    int8_t temp1b = 0;
    int16_t temp2b = 0;
    int32_t temp3b = 0;
    int64_t temp4b = 0;
    switch (audio->numbytes) {
    case 1:
      temp1b = (audio->array1b)[i];
      (audio->array1b)[i] = (audio->array1b)[indexOppsite];
      (audio->array1b)[indexOppsite] = temp1b;
      break;
    case 2:
      temp2b = (audio->array2b)[i];
      (audio->array2b)[i] = (audio->array2b)[indexOppsite];
      (audio->array2b)[indexOppsite] = temp2b;
      break;
    case 3:
      temp3b = (audio->array3b)[i];
      (audio->array3b)[i] = (audio->array3b)[indexOppsite];
      (audio->array3b)[indexOppsite] = temp3b;
      break;
    case 4:
      temp4b = (audio->array4b)[i];
      (audio->array4b)[i] = (audio->array4b)[indexOppsite];
      (audio->array4b)[indexOppsite] = temp4b;
      break;
    }
  }
}

int main(int argc, char **argv) {
  WAV_t wav;
  WavFlags_t flags;
  // Get input
  if (wavflags(argc, argv, "i:o:", &flags) == -1)
    printUsage(argv[0]);
  checkInput(flags, &wav);

  // Invert all channels
  for (int i = 1; i <= wav.header.fmt.NumChannels; i++) {
    invertChannel(&(wav.data), i, wav.header.fmt.NumChannels);
  }

  // Output file
  checkOutput(flags, &wav);

  // Free space
  free(wav.data.array1b);

  return 0;
}