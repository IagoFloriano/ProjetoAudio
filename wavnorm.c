// GRR20196049 Iago Mello Floriano

#include "wavflags.h"
#include "wavio.h"
#include "wavlib.h"
#include <stdio.h>
#include <stdlib.h>

// multiplies a int8_t array by mult, not letting overflow happen
void multArray1b(int8_t *array, int size, float mult) {
  for (int i = 0; i < size; i++) {
    if (array[i] * mult > INT8_MAX)
      array[i] = INT8_MAX;
    else if (array[i] * mult < INT8_MIN)
      array[i] = INT8_MIN;
    else
      array[i] = array[i] * mult;
  }
}
// multiplies a int16_t array by mult, not letting overflow happen
void multArray2b(int16_t *array, int size, float mult) {
  for (int i = 0; i < size; i++) {
    if (array[i] * mult > INT16_MAX)
      array[i] = INT16_MAX;
    else if (array[i] * mult < INT16_MIN)
      array[i] = INT16_MIN;
    else
      array[i] = array[i] * mult;
  }
}
// multiplies a int32_t array by mult, not letting overflow happen
void multArray3b(int32_t *array, int size, float mult) {
  for (int i = 0; i < size; i++) {
    if (array[i] * mult > INT32_MAX)
      array[i] = INT32_MAX;
    else if (array[i] * mult < INT32_MIN)
      array[i] = INT32_MIN;
    else
      array[i] = array[i] * mult;
  }
}
// multiplies a int64_t array by mult, not letting overflow happen
void multArray4b(int64_t *array, int size, float mult) {
  for (int i = 0; i < size; i++) {
    if (array[i] * mult > INT64_MAX)
      array[i] = INT64_MAX;
    else if (array[i] * mult < INT64_MIN)
      array[i] = INT64_MIN;
    else
      array[i] = array[i] * mult;
  }
}

// multiplies the whole array in data checking the type and not letting overflow happen
void multWav(WAVData_t *data, float mult) {
  switch (data->numbytes) {
  case 1:
    multArray1b(data->array1b, data->audioSize, mult);
    break;
  case 2:
    multArray2b(data->array2b, data->audioSize, mult);
    break;
  case 3:
    multArray3b(data->array3b, data->audioSize, mult);
    break;
  case 4:
    multArray4b(data->array4b, data->audioSize, mult);
    break;
  }
}

// returns the value that will normalize the audio
float getmult(WAVData_t *data) {
  int64_t max = 0;
  float mult;

  switch (data->numbytes) {
  case 1:
    for (int i = 0; i < data->audioSize; i++)
      if (abs((data->array1b)[i] > max))
        max = (data->array1b)[i];
    mult = (float)INT8_MAX / max;
    break;
  case 2:
    for (int i = 0; i < data->audioSize; i++)
      if (abs((data->array2b)[i] > max))
        max = (data->array2b)[i];
    mult = (float)INT16_MAX / max;
    break;
  case 3:
    for (int i = 0; i < data->audioSize; i++)
      if (abs((data->array3b)[i] > max))
        max = (data->array3b)[i];
    mult = (float)INT32_MAX / max;
    break;
  case 4:
    for (int i = 0; i < data->audioSize; i++)
      if (abs((data->array4b)[i] > max))
        max = (data->array4b)[i];
    mult = (float)INT64_MAX / max;
    break;
  }

  return mult;
}

int main(int argc, char **argv) {
  WAV_t wav;
  WavFlags_t flags;
  //get input
  wavflags(argc, argv, "i:o:", &flags);
  checkInput(flags, &wav);

  // gets the value to multiply by
  float mult = getmult(&(wav.data));
  // normalizes the audio
  multWav(&(wav.data), mult);

  checkOutput(flags, &wav);

  // Frees space used
  free(wav.data.array1b);

  return 0;
}