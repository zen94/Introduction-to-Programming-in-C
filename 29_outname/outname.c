#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char *ext = ".count";
  char *outputName = malloc((strlen(inputName)+strlen(ext)+1)*sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, ext);
  return outputName;
}
