// GRR20196049 Iago Mello Floriano

#include "wavflags.h"
#include "wavio.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

void echoChannel(WAVData_t *audio, int channel, int numchannels, float echolevel, int echodelay, int sampleRate) {
  // goes backwards to the channel so there wont be echo of echo
  int iGetEchoFrom = echodelay * sampleRate / 1000; // how many indexes back from this channel the echo will be taken from
  for (int i = audio->audioSize - 1 + (channel - numchannels); i - (iGetEchoFrom * numchannels) >= 0; i -= numchannels) {
    switch (audio->numbytes) {
    case 1:
      // Test if a positive value overflows to negative
      if ((audio->array1b)[i] + echolevel * (audio->array1b)[i - (iGetEchoFrom * numchannels)] > INT8_MAX)
        (audio->array1b)[i] = INT8_MAX;
      // Test if a negative value overflows to positive
      else if ((audio->array1b)[i] + echolevel * (audio->array1b)[i - (iGetEchoFrom * numchannels)] < INT8_MIN)
        (audio->array1b)[i] = INT8_MIN;
      else
        (audio->array1b)[i] += echolevel * (audio->array1b)[i - (iGetEchoFrom * numchannels)];
      break;
    case 2:
      // Test if a positive value overflows to negative
      if ((audio->array2b)[i] + echolevel * (audio->array2b)[i - (iGetEchoFrom * numchannels)] > INT16_MAX)
        (audio->array2b)[i] = INT16_MAX;
      // Test if a negative value overflows to positive
      else if ((audio->array2b)[i] + echolevel * (audio->array2b)[i - (iGetEchoFrom * numchannels)] < INT16_MIN)
        (audio->array2b)[i] = INT16_MIN;
      else
        (audio->array2b)[i] += echolevel * (audio->array2b)[i - (iGetEchoFrom * numchannels)];
      break;
    case 3:
      // Test if a positive value overflows to negative
      if ((audio->array3b)[i] + echolevel * (audio->array3b)[i - (iGetEchoFrom * numchannels)] > INT32_MAX)
        (audio->array3b)[i] = INT32_MAX;
      // Test if a negative value overflows to positive
      else if ((audio->array3b)[i] + echolevel * (audio->array3b)[i - (iGetEchoFrom * numchannels)] < INT32_MIN)
        (audio->array3b)[i] = INT32_MIN;
      else
        (audio->array3b)[i] += echolevel * (audio->array3b)[i - (iGetEchoFrom * numchannels)];
      break;
    case 4:
      // Test if a positive value overflows to negative
      if ((audio->array4b)[i] + echolevel * (audio->array4b)[i - (iGetEchoFrom * numchannels)] > INT64_MAX)
        (audio->array4b)[i] = INT64_MAX;
      // Test if a negative value overflows to positive
      else if ((audio->array4b)[i] + echolevel * (audio->array4b)[i - (iGetEchoFrom * numchannels)] < INT64_MIN)
        (audio->array4b)[i] = INT64_MIN;
      else
        (audio->array4b)[i] += echolevel * (audio->array4b)[i - (iGetEchoFrom * numchannels)];
      break;
    }
  }
}

void printUsage(char *program) {
  fprintf(stderr, "Incorrect usage of program, example of correct usage:\n%s -t 500 -l 0.5 -i input.wav -o output.wav\n", program);
  exit(1);
}

int main(int argc, char **argv) {
  WAV_t wav;
  WavFlags_t flags;
  //get input
  if (wavflags(argc, argv, "i:o:l:t:", &flags) == -1)
    printUsage(argv[0]);
  checkInput(flags, &wav);

  // Setting variables to apply echo
  float l = 0.5;
  if (flags.lFlag) {
    l = atof(flags.lFlag);
    if (l > 1)
      l = 1;
    if (l < 0)
      l = 0;
  }
  float t = 1000;
  if (flags.tFlag) {
    t = atoi(flags.tFlag);
    if (t < 0)
      t = 0;
  }

  // Applying echo
  for (int i = 1; i <= wav.header.fmt.NumChannels; i++) {
    echoChannel(&(wav.data), i, wav.header.fmt.NumChannels, l, t, wav.header.fmt.SampleRate);
  }

  //output file
  checkOutput(flags, &wav);

  //free used space
  free(wav.data.array1b);

  return 0;
}