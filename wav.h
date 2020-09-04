#include <stdint.h>
#include <stdio.h>
#ifndef __WAV__
#define __WAV__

typedef struct {
  // RIFF
  char ChunkID[4];
  uint32_t ChunkSize;
  char Format[4];
  // FMT
  char SubChunk1ID[4];
  uint32_t SubChunk1Size;
  uint16_t AudioFormat;
  uint16_t NumChannels;
  uint32_t SampleRate;
  uint32_t ByteRate;
  uint16_t BlockAlign;
  uint16_t BitsPerSample;
  // DATA
  char SubChunk2ID[4];
  uint32_t SubChunk2Size;
} WAV_t;

void fprintwav(FILE *f, WAV_t wav);

#endif // __WAV__