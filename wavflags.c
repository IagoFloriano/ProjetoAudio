//GRR20196049 Iago Mello Floriano
#include "wavflags.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int wavflags(int argc, char **argv, char *desiredFlags, WavFlags_t *savedFlags) {
  savedFlags->iFlag = savedFlags->lFlag = savedFlags->oFlag = savedFlags->tFlag = NULL; //Initialization
  int option;

  // set the strings of the flags
  while ((option = getopt(argc, argv, desiredFlags)) != -1) {
    switch (option) {
    case 'i':
      if (!savedFlags->iFlag)
        savedFlags->iFlag = optarg;
      break;
    case 'o':
      if (!savedFlags->oFlag)
        savedFlags->oFlag = optarg;
      break;
    case 'l':
      if (!savedFlags->lFlag)
        savedFlags->lFlag = optarg;
      break;
    case 't':
      if (!savedFlags->tFlag)
        savedFlags->tFlag = optarg;
      break;
    default:
      return -1;
    }
  }

  return 1;
}