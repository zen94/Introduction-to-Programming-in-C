#include <stdio.h>
#include <stdlib.h>

void rotate(char matrix[10][10]){
  int matSize = 10;
  int temp = 0;

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
