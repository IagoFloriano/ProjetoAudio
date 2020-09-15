// GRR20196049 Iago Mello FLoriano

#ifndef __WAVFLAGS__
#define __WAVFLAGS__

// Struct to save the index of the next element to the flag in argv
// Example: ./program -i test -o testo
// argv[iFlag] == "test"; argv[oFlag] = "testo"
typedef struct {
  int iFlag;
  int oFlag;
  int lFlag;
  int tFlag;
} WavFlags_t;

/*reads the desired flags (only gets the desired ones)
  if flag not found or undesired value will be -1
  if flag found it will be stored the value of the index
  returns 1 if flags used correctly, returns -1 otherwise*/
int wavflags(int argc, char **argv, char *desiredFlags, WavFlags_t *savedFlags);

#endif // __WAVFLAGS__