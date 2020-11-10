#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int decryptKey(FILE * f) {
  int chararr[26] = {0};
  int c;
  int maxind = 0,maxval = 0;
  int key;

  while ((c = fgetc(f)) != EOF){
    if (isalpha(c)){
      c = tolower(c);
      c -= 'a';
      chararr[c]++;
    }
  }

  for (int i = 0; i < 26; i++){
    if (chararr[i] > maxval){
      maxval = chararr[i];
      maxind = i;
    }
  }

  key = maxind + 22;
  key = key%26;

  return key;
}

int main(int argc, char ** argv){
  if (argc != 2) {
    fprintf(stderr,"Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = decryptKey(f);
  printf("%d\n",key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
