// GRR20196049 Iago Mello Floriano

#include "wavflags.h"
#include "wavio.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

void printUsage(char *program) {
  fprintf(stderr, "Incorrect usage, example of correct usage:\n%s -i input -o output\n", program);
}

// Inverts only the channel asked os an audio with "numchannels" channels
void invertChannel(WAVData_t *audio, int channel, int numchannels) {
  for (int i = channel - 1; i < audio->audioSize / 2; i += numchannels) {
    switch (audio->numbytes) {
    case 1:
      int8_t temp = audio->array1b[i];
      audio->array1b[i] = audio->array1b[audio->audioSize - 1 - (i * numchannels)];
      audio->array1b[audio->audioSize - 1 - (i * numchannels)] = temp;
    case 2:
      int16_t temp = audio->array2b[i];
      audio->array2b[i] = audio->array2b[audio->audioSize - 1 - (i * numchannels)];
      audio->array2b[audio->audioSize - 1 - (i * numchannels)] = temp;
    case 3:
      int32_t temp = audio->array3b[i];
      audio->array3b[i] = audio->array3b[audio->audioSize - 1 - (i * numchannels)];
      audio->array3b[audio->audioSize - 1 - (i * numchannels)] = temp;
    case 4:
      int64_t temp = audio->array4b[i];
      audio->array4b[i] = audio->array4b[audio->audioSize - 1 - (i * numchannels)];
      audio->array4b[audio->audioSize - 1 - (i * numchannels)] = temp;
    }
  }
}

int main(int argc, char **argv) {
  WAV_t wav;
  WavFlags_t flags;
  if (wavflags(argc, argv, "i:o:", &flags) == -1)
    printUsage(argv[0]);
  checkInput(flags, &wav);
}