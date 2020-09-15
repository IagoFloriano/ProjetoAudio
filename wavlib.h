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
  int numbytes;  //number of bytes in each sample
  int audioSize; //number of samples
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
int readHeaderInput(char *path, WAVHEADER_t *header, FILE **f);

/*initializes the WAVData_t struct inside the WAV_t passed usign its WAVHEADER_t
  this is, configures wav.data
  allocs the space in wav.data.array#b
  returns -1 if there was an error allocing, returns 1 otherwise*/
int initializeWavData(WAV_t *wav);

/*reads the header from path and initializes wavdata (use NULL to read from stdin)
  f will be the file from where it was read
  returns 1 if there were no errors
  returns -2 if it wasnt able to open the file
  returns -1 if it wasnt able to allocate space for the audio*/
int initializeWav(char *path, WAV_t *wav, FILE **f);

/*reads the audio data from FILE that was already oppened
  wav must have been initialized*/
int readAudioData(FILE *f, WAV_t *wav);

/*writes the audio in wav form on f
  f must have been oppened before*/
void writeWav(FILE *f, WAV_t *wav);

#endif // __WAV__