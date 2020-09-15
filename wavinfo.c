#include "wavlib.h"
#include <stdio.h>

// Funtion to print just the information in the riff
void fprintRIFF(FILE *f, riff_t riff) {
  fprintf(f, "riff tag\t(4 bytes): \"%.4s\"\n", riff.ChunkID);
  fprintf(f, "riff size\t(4 bytes): %d\n", riff.ChunkSize);
  fprintf(f, "wave tag\t(4 bytes): \"%.4s\"\n", riff.Format);
}

// Funtion to print just the informations in format
void fprintFMT(FILE *f, fmt_t fmt) {
  fprintf(f, "form tag\t(4 bytes): \"%.4s\"\n", fmt.SubChunkID);
  fprintf(f, "fmt_size\t(4 bytes): %d\n", fmt.SubChunkSize);
  fprintf(f, "audio_format\t(2 bytes): %d\n", fmt.AudioFormat);
  fprintf(f, "num_channels\t(2 bytes): %d\n", fmt.NumChannels);
  fprintf(f, "sample_rate\t(4 bytes): %d\n", fmt.SampleRate);
  fprintf(f, "byte_rate\t(4 bytes): %d\n", fmt.ByteRate);
  fprintf(f, "block_align\t(2 bytes): %d\n", fmt.BlockAlign);
  fprintf(f, "bits_per_sample\t(2 bytes): %d\n", fmt.BitsPerSample);
}

// Funtion to print just the information in data
void fprintDATA(FILE *f, data_t data) {
  fprintf(f, "data tag\t(4 bytes): \"%.4s\"\n", data.SubChunkID);
  fprintf(f, "data size\t(4 bytes): %d\n", data.SubChunkSize);
}

// Funtion to print the whole information this program prints
void fprintheader(FILE *f, WAVHEADER_t header) {
  fprintRIFF(f, header.riff);
  fprintFMT(f, header.fmt);
  fprintDATA(f, header.data);
  int bytesPsample = header.fmt.BitsPerSample / 8;
  fprintf(f, "bytes per sample\t : %d\n", bytesPsample);
  fprintf(f, "samples per cahnnel\t : %d\n", header.data.SubChunkSize / bytesPsample / header.fmt.NumChannels);
}

int main(int argc, char *argv[]) {
  WAVHEADER_t hAudio;
  int iInput = 0;
  ioflags(argc, argv, &iInput, NULL);

  readHeaderInput(iInput, argv, &hAudio);

  fprintheader(stdout, hAudio);

  return 0;
}