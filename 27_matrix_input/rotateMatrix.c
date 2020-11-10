#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIXSIZE 10
#define LINESIZE MATRIXSIZE+2

void rotate(char matrix[MATRIXSIZE][MATRIXSIZE]){
  int temp = 0;
  unsigned matSize = MATRIXSIZE;

  // tranpose matrix
  for (int i = 0; i < matSize; i++){
    for (int j = 0; j < i; j++){
      temp = matrix[i][j];
      matrix[i][j] = matrix[j][i];
      matrix[j][i] = temp;
    }
  }

  // swap column
  for (int i = 0; i < matSize; i++){
    for (int j = 0; j < matSize/2; j++){
      temp = matrix[i][j];
      matrix[i][j] = matrix[i][matSize - 1 - j];
      matrix[i][matSize - 1 - j] = temp;
    }
  }
}

int main(int argc, char ** argv){
  char matrix[MATRIXSIZE][MATRIXSIZE] = { {0},{0} };
  char line[LINESIZE] = {'\0'};
  int row = 0, col = 0;

  if (argc != 2) {
    fprintf(stderr,"Usage: rotateMatrix inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  while(fgets(line, LINESIZE, f) != NULL){
    if (strchr(line, '\n') == NULL){
      fprintf(stderr,"Data too long on row %d\n",row);
      return EXIT_FAILURE;
    }

    if (row >= MATRIXSIZE){
      fprintf(stderr,"Row number more than allowed size\n");
      return EXIT_FAILURE;
    }

    for(col = 0; col < MATRIXSIZE; col++){
      if (line[col] == '\n'){
	fprintf(stderr,"Data too short on row %d\n",row);
      }
      matrix[row][col] = line[col];
    }
    row++;
  }

  if (!feof(f)){
    fprintf(stderr,"End of file not reached\n");
    return EXIT_FAILURE;
  }

  if (ferror(f)){
    fprintf(stderr,"Error reading input file");
    return EXIT_FAILURE;
  }

  if (row < MATRIXSIZE){
    fprintf(stderr,"Row number less than required size\n");
    return EXIT_FAILURE;
  }

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  rotate(matrix);

  for (int i = 0; i < 10; i++){
    for (int j = 0; j < 10; j++){
      printf("%c",matrix[i][j]);
    }
    printf("\n");
  }

  return EXIT_SUCCESS;
}
