// GRR 20196049 Iago Mello Floriano
#include "wav.h"
#include <stdio.h>

// Imprime em saida "f" "num" elementos de vetor "array"
void printfCharArray(int num, char *array, FILE *f) {
  for (int i = 0; i < num; i++)
    fprintf(f, "%c", array[i]);
}

void fprintwav(FILE *f, WAV_t wav) {
  fprintf(f, "riff tag (4 bytes): \"");
  printfCharArray(4, wav.ChunkID, f);
  fprintf(f, "\"\n");

  fprintf(f, "riff size (4 bytes): %d\n", wav.ChunkSize);

  fprintf(f, "wave tag (4 bytes): \"");
  printfCharArray(4, wav.Format, f);
  fprintf(f, "\"\n");

  fprintf(f, "form tag (4 bytes): \"");
  printfCharArray(4, wav.SubChunk1ID, f);
  fprintf(f, "\"\n");

  fprintf(f, "fmt_size (4 bytes): %d\n", wav.SubChunk1Size);
  fprintf(f, "audio_format (4 bytes): %d\n", wav.AudioFormat);
}