// GRR20196049 Iago Mello FLoriano

#ifndef __WAVFLAGS__
#define __WAVFLAGS__

// Struct to save the string of the option passed for that flag
// Example: ./program -i test -o testo
// iFlag == "test"; oFlag = "testo"
typedef struct {
  char *iFlag;
  char *oFlag;
  char *lFlag;
  char *tFlag;
} WavFlags_t;

/*reads the desired flags (only gets the desired ones)
  if flag not found or undesired value will be NULL
  if flag found it will be stored the string
  returns 1 if flags used correctly, returns -1 otherwise*/
int wavflags(int argc, char **argv, char *desiredFlags, WavFlags_t *savedFlags);

#endif // __WAVFLAGS__