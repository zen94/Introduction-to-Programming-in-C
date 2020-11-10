#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void splitKV(char* line, kvpair_t* pair){
  char* temp = NULL;

  temp = strchr(line,'=');
  *temp = '\0';
  temp++;

  pair->key = malloc((strlen(line)+1)*sizeof(pair->key));
  strcpy(pair->key,line);

  pair->value = malloc((strlen(temp)+1)*sizeof(pair->value));
  strcpy(pair->value,temp);
}

kvpair_t * parseKV(char* line){
  kvpair_t* pair = malloc(sizeof(*pair));
  splitKV(line, pair);
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE* f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  char* line = NULL;
  size_t sz = 0;

  kvarray_t* pairs = malloc(sizeof(*pairs));
  pairs->kvpairs = NULL;
  pairs->n_kvpairs = 0;

  while(getline(&line, &sz, f) >= 0){
    if (line[strlen(line)-1] == '\n'){
      line[strlen(line)-1] = '\0';
    }
    pairs->kvpairs = realloc(pairs->kvpairs, (pairs->n_kvpairs+1)*sizeof(*pairs->kvpairs));
    pairs->kvpairs[pairs->n_kvpairs] = parseKV(line);
    pairs->n_kvpairs++;
  }
  free(line);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i = 0; i < pairs->n_kvpairs; i++){
    free(pairs->kvpairs[i]->key);
    free(pairs->kvpairs[i]->value);
    free(pairs->kvpairs[i]);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for(int i = 0; i < pairs->n_kvpairs; i++){
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i]->key, pairs->kvpairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for(int i = 0; i < pairs->n_kvpairs; i++){
    if(strcmp(pairs->kvpairs[i]->key, key)==0){
      return pairs->kvpairs[i]->value;
    }
  }
  return NULL;
}
