//GRR20196049 Iago Mello Floriano
#include "wavflags.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int wavflags(int argc, char **argv, char *desiredFlags, WavFlags_t *savedFlags) {
  savedFlags->iFlag = savedFlags->lFlag = savedFlags->oFlag = savedFlags->tFlag = -1; //Initialization
  int option;

  // set the index values for the variables
  while ((option = getopt(argc, argv, desiredFlags)) != -1) {
    switch (option) {
    case 'i':
      if (savedFlags->iFlag == -1)
        savedFlags->iFlag = optind;
      if (savedFlags->iFlag >= argc) {
        savedFlags->iFlag = -1;
        return -1;
      }
      break;
    case 'o':
      if (savedFlags->oFlag == -1)
        savedFlags->oFlag = optind;
      if (savedFlags->oFlag >= argc) {
        savedFlags->oFlag = -1;
        return -1;
      }
      break;
    case 'l':
      if (savedFlags->lFlag == -1)
        savedFlags->lFlag = optind;
      if (savedFlags->lFlag >= argc) {
        savedFlags->lFlag = -1;
        return -1;
      }
      break;
    case 't':
      if (savedFlags->tFlag == -1)
        savedFlags->tFlag = optind;
      if (savedFlags->tFlag >= argc) {
        savedFlags->tFlag = -1;
        return -1;
      }
      break;
    default:
      return -1;
    }
  }

  return 1;
}