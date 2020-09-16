// GRR20196049
#include "wavflags.h"
#include "wavlib.h"

//Library to make it easier to read a wav file from one input and write it to a desired output

#ifndef __WAVIO__
#define __WAVIO__

// Function to read the input exiting the program on exeption cases
void checkInput(WavFlags_t flags, WAV_t *wav);

// outputs the wav file taking care of the flags used as output
void checkOutput(WavFlags_t flags, WAV_t *wav);

#endif //__WAVIO__