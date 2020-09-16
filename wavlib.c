// GRR 20196049 Iago Mello Floriano
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// internal function do read the header
void readHeader(FILE *f, WAVHEADER_t *header) {
  fread(header, sizeof(WAVHEADER_t), 1, f);
}

int readHeaderInput(char *path, WAVHEADER_t *header, FILE **f) {
  // oppen file
  *f = stdin;
  if (path) {
    *f = fopen(path, "r");
    // test if file exists
    if (!(*f))
      return -1;
  }
  readHeader(*f, header);
  return 2;
}

int initializeWavData(WAV_t *wav) {
  wav->data.numbytes = wav->header.fmt.BitsPerSample / 8;
  wav->data.audioSize = wav->header.data.SubChunkSize / wav->data.numbytes;
  // allocs space depending on what is needed
  switch (wav->data.numbytes) {
  case 1:
    wav->data.array1b = malloc(sizeof(int8_t) * wav->data.audioSize);
    break;
  case 2:
    wav->data.array2b = malloc(sizeof(int16_t) * wav->data.audioSize);
    break;
  case 3:
    wav->data.array3b = malloc(sizeof(int32_t) * wav->data.audioSize);
    break;
  case 4:
    wav->data.array4b = malloc(sizeof(int64_t) * wav->data.audioSize);
    break;
  }

  //test if it was possible to allocate space and returns accordingly
  return !(wav->data.array1b) ? -1 : 1;
}

int initializeWav(char *path, WAV_t *wav, FILE **f) {
  if (readHeaderInput(path, &(wav->header), f) < 0)
    return -2;
  return initializeWavData(wav);
}

int readAudioData(FILE *f, WAV_t *wav) {
  switch (wav->data.numbytes) {
  case 1:
    fread(wav->data.array1b, sizeof(int8_t), wav->data.audioSize, f);
    break;
  case 2:
    fread(wav->data.array2b, sizeof(int16_t), wav->data.audioSize, f);
    break;
  case 3:
    fread(wav->data.array3b, sizeof(int32_t), wav->data.audioSize, f);
    break;
  case 4:
    fread(wav->data.array4b, sizeof(int64_t), wav->data.audioSize, f);
    break;
  }
  return 0;
}

void writeWav(FILE *f, WAV_t *wav) {
  fwrite(&(wav->header), sizeof(WAVHEADER_t), 1, f);
  switch (wav->data.numbytes) {
  case 1:
    fwrite(wav->data.array1b, sizeof(int8_t), wav->data.audioSize, f);
    break;
  case 2:
    fwrite(wav->data.array2b, sizeof(int16_t), wav->data.audioSize, f);
    break;
  case 3:
    fwrite(wav->data.array3b, sizeof(int32_t), wav->data.audioSize, f);
    break;
  case 4:
    fwrite(wav->data.array4b, sizeof(int64_t), wav->data.audioSize, f);
    break;
  }
}