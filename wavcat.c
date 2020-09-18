// GRR20196049 Iago Mello Floriano

#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reads the whole wav file from path
// Closes program if the were problem allocing or a problem oppening the file
void readWav(WAV_t *wav, char *path) {
  int initializeResult;
  FILE *f;
  initializeResult = initializeWav(path, wav, &f);

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

// Adds the audio information of b at the end of a
// Updates a's header to show the correct ammount of space used
// Returns 1 if there were no error
// Return -1 if there was a problem allocating space for a
int wavConcat(WAV_t *a, WAV_t *b) {
  // Temporary variable so that if realloc fails information isnt lost
  void *temp;
  // Allocation of space needed for both audios
  temp = realloc(a->data.array1b, (a->data.audioSize * a->data.numbytes) + (b->data.audioSize * b->data.numbytes));
  if (!temp)
    return -1;
  a->data.array1b = temp;
  // Coppies information
  for (int i = 0; i < b->data.audioSize; i++) {
    switch (a->data.numbytes) {
    case 1:
      (a->data.array1b)[i + a->data.audioSize] = (b->data.array1b)[i];
      break;
    case 2:
      (a->data.array2b)[i + a->data.audioSize] = (b->data.array2b)[i];
      break;
    case 3:
      (a->data.array3b)[i + a->data.audioSize] = (b->data.array3b)[i];
      break;
    case 4:
      (a->data.array4b)[i + a->data.audioSize] = (b->data.array4b)[i];
      break;
    }
  }
  // Updates a's header
  a->data.audioSize += b->data.audioSize;
  a->header.data.SubChunkSize += b->data.audioSize * a->data.numbytes;
  a->header.riff.ChunkSize += b->data.audioSize * a->data.numbytes;

  return 1;
}

// Returns the index of the -o flag in argv
// Returns -1 if there is no -o flag
// Returns -2 if the -o is the last thing in argv
// Returns -3 if -o is in the middle of the input files
int getO(int argc, char **argv) {
  // gets the index to return
  int i;
  for (i = 0; i < argc; i++) {
    if (strcmp("-o", argv[i]) == 0)
      break;
  }
  if (i == argc - 2)
    return i;
  if (i == argc)
    return -1;
  if (i < argc - 2)
    return -3;
  return -2;
}

int main(int argc, char **argv) {
  WAV_t wInput;
  WAV_t wOutput;
  // Taking care of the flag
  int iOutput;
  if ((iOutput = getO(argc, argv)) < -1) {
    fprintf(stderr, "The flag \"-o\" should be followed by a file and be placed after all the files to concatenate, closing program\n");
    return 1;
  }
  // Gets the index of the last file to be read
  int last = argc - 1;
  if (iOutput > -1)
    last -= 2;

  // Closes the program if only one file was passed
  if (last < 2) {
    fprintf(stderr, "More than one file should be passed as input\n");
    return 1;
  }

  // Saves the first file passed for input
  readWav(&wOutput, argv[1]);

  // Adds the others file to the wav to be outputed
  for (int i = 2; i <= last; i++) {
    readWav(&wInput, argv[i]);
    if (wavConcat(&wOutput, &wInput) == -1) {
      fprintf(stderr, "There was an error allocating space, stopping concatenation with %s\n", argv[i]);
      return 2;
    }
    free(wInput.data.array1b);
  }

  FILE *f = stdout;
  if (iOutput > -1) {
    f = fopen(argv[iOutput + 1], "w");
  }

  writeWav(f, &wOutput);
  fclose(f);

  free(wOutput.data.array1b);

  return 0;
}