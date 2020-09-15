// GRR20196049 Iago Mello Floriano
#include <stdint.h>
#include <stdio.h>
#ifndef __WAVLIB__
#define __WAVLIB__

// Structs for the header
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
// End of structs for the header

// The header struct
typedef struct {
  riff_t riff;
  fmt_t fmt;
  data_t data;
} WAVHEADER_t;

// Struct for the samples
typedef struct {
  union {
    uint8_t *array1b;
    uint16_t *array2b;
    uint32_t *array3b;
    uint64_t *array4b;
  };
  int numbytes;
  int audioSize;
} WAVData_t;

// The whole wav struct;
typedef struct {
  WAVHEADER_t header;
  WAVData_t data;
} WAV_t;

/*reads the header input from path
  path should be NULL to read from stdin
  returns 1 if able to read sucssessfully
  returns -1 if unable to open file*/
int readHeaderInput(char *path, WAVHEADER_t *header);

/*initializes the WAVData_t struct inside the WAV_t passed usign its WAVHEADER_t*/
int initializeWavData(WAV_t *wav);

/*reads the audio data usign argv[iInput] as path
  iInput should be -1 to read from stdin
  returns 1 if read from stdin
  2 if read from file
  -1 if not able to open file*/
int readAudioData(char *path, WAV_t *wav);

#endif // __WAV__