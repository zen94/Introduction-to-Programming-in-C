#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int compareNum(int num1, int num2){
  if (num1>=num2){
    return 0;
  }
  else{
    return 1;
  }
}

size_t maxSeq(int * array, size_t n){
  if (n==0){
    return 0;
  }

  int currLen = 1;
  int maxLen = 1;
  for (int i = 0; i < n-1; i++){
    if (compareNum(array[i],array[i+1])==1){
      currLen++;
      if (currLen > maxLen){
	maxLen = currLen;
      }
    }
    else{
      currLen = 1;
    }
  }
  return maxLen;
}
