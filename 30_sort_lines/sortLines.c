#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printData(char** linearr, int count){
  for (int i = 0; i < count; i++){
    printf("%s",linearr[i]);
    free(linearr[i]);
  }
  free(linearr);
}

void readFile(FILE* f){
  char* line = NULL;
  char** linearr = NULL;
  size_t sz = 0;
  size_t linecount = 0;

  while(getline(&line, &sz, f) >= 0){
    linearr=realloc(linearr, (1+linecount)*sizeof(*linearr));
    linearr[linecount] = line;
    line = NULL;
    linecount++;
  }
  free(line);

  sortData(linearr,linecount);
  printData(linearr,linecount);
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if (argc < 2) {
    fprintf(stderr,"Usage: at least one argument must be provided. eg sortLines *input1* *input2* *input3* ...\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < argc-1;i++){
    FILE * f = fopen(argv[i+1], "r");
    if (f == NULL) {
      perror("Could not open file");
      return EXIT_FAILURE;
    }

    readFile(f);

    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
