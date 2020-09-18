// GRR20196049 Iago Mello Floriano// GRR20196049 Iago Mello Floriano

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

// Adds the the samples of a and b and stores it into a
// a can NOT have less samples than be or there will be errors
void wavMix(WAV_t *a, WAV_t *b) {
  // Adds samples
  for (int i = 0; i < b->data.audioSize; i++) {
    switch (b->data.numbytes) {
    case 1:
      (a->data.array1b)[i] += (b->data.array1b)[i];
      break;
    case 2:
      (a->data.array2b)[i] += (b->data.array2b)[i];
      break;
    case 3:
      (a->data.array3b)[i] += (b->data.array3b)[i];
      break;
    case 4:
      (a->data.array4b)[i] += (b->data.array4b)[i];
      break;
    }
  }
}

// Divides all the samples in wav by the desired ammount
void wavDiv(WAV_t *wav, int div) {
  for (int i = 0; i < wav->data.audioSize; i++) {
    switch (wav->data.numbytes) {
    case 1:
      (wav->data.array1b)[i] = (wav->data.array1b)[i] / div;
      break;
    case 2:
      (wav->data.array2b)[i] = (wav->data.array2b)[i] / div;
      break;
    case 3:
      (wav->data.array3b)[i] = (wav->data.array3b)[i] / div;
      break;
    case 4:
      (wav->data.array4b)[i] = (wav->data.array4b)[i] / div;
      break;
    }
  }
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

// Returns the index of the biggest wav in argv
// Reads the argv[1] to argv[n]
// Exits the program if unable to read a file
int getimax(int n, char **argv) {
  uint32_t max = 0;
  int imax = 0;
  WAVHEADER_t tempheader;
  FILE *f;
  int i = 1;
  do {
    // Testing if able to open file
    if (readHeaderInput(argv[i], &tempheader, &f) < 0) {
      fprintf(stderr, "Unable to read file %s, closing program\n", argv[i]);
      exit(1);
    }
    fclose(f);
    // Get the max index
    if (max < tempheader.riff.ChunkSize) {
      imax = i;
      max = tempheader.riff.ChunkSize;
    }
    i++;
  } while (i <= n);

  return imax;
}

int main(int argc, char **argv) {
  WAV_t wInput;
  WAV_t wOutput;
  // Taking care of the flag
  int iOutput;
  if ((iOutput = getO(argc, argv)) < -1) {
    fprintf(stderr, "The flag \"-o\" should be followed by a file and be placed after all the files to mix, closing program\n");
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

  fprintf(stderr, "trying to find the biggest file...\n");
  // Saves the biggest file as the one to be outputed
  int iMax = getimax(last, argv);
  fprintf(stderr, "biggest file is %s\n", argv[iMax]);
  readWav(&wOutput, argv[iMax]);
  wavDiv(&wOutput, last); // Last is also the ammount of files
  fprintf(stderr, "%s was read\n", argv[iMax]);

  // Mixing the audio
  for (int i = 1; i <= last; i++) {
    // Ensures the audio wont add to itself
    if (i != iMax) {
      readWav(&wInput, argv[i]);
      wavDiv(&wInput, last);
      wavMix(&wOutput, &wInput);
      fprintf(stderr, "%s was mixed with %s\n", argv[i], argv[iMax]);
      free(wInput.data.array1b);
      fprintf(stderr, "%s was freed\n", argv[i]);
    }
  }

  // Outputing
  FILE *f = stdout;
  if (iOutput > -1) {
    f = fopen(argv[iOutput + 1], "w");
  }

  writeWav(f, &wOutput);
  fclose(f);

  free(wOutput.data.array1b);

  return 0;
}