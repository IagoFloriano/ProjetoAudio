// GRR20196049 Iago Mello Floriano
#include <stdint.h>
#include <stdio.h>
#ifndef __WAVLIB__
#define __WAVLIB__

typedef struct {
  char ChunkID[4];
  uint32_t ChunkSize;
  char Format[4];
} riff_t;

typedef struct {
  char SubChunkID[4];
  uint32_t SubChunkSize;
  uint16_t AudioFormat;
  uint16_t NumChannels;
  uint32_t SampleRate;
  uint32_t ByteRate;
  uint16_t BlockAlign;
  uint16_t BitsPerSample;
} fmt_t;

typedef struct {
  char SubChunkID[4];
  uint32_t SubChunkSize;
} data_t;

typedef struct {
  riff_t riff;
  fmt_t fmt;
  data_t data;
} WAVHEADER_t;

/*iInput will recieve the index of the first -i flag +1
  iOutput will recieve the index of the first -o flag +1
  if the flag is not found the variable will recieve -1
  the variable will also recieve -1 if is the last argument
  NULL is a valid option if one of the flags is undesired*/
void ioflags(int argc, char **argv, int *iInput, int *iOutput);

/*returns 1 if read from stdin
  2 if read from file
  -1 if not able to open file
  iInput should be the index of the string to be input (-1) if stdin*/
int readHeaderInput(int iInput, char **argv, WAVHEADER_t *header);

#endif // __WAV__