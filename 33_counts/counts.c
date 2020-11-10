#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

counts_t * createCounts(void) {
  //WRITE ME
  counts_t* c = malloc(sizeof(*c));
  c->arr_counts = NULL;
  c->n_known = 0;
  c->n_unknown = 0;
  return c;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL){
    c->n_unknown++;
  }
  else{
    // if number of known is 0, we add new one
    if(c->n_known == 0){
      c->arr_counts = realloc(c->arr_counts, (c->n_known+1)*sizeof(*c->arr_counts));
      c->arr_counts[c->n_known] = malloc(sizeof(**c->arr_counts));
      c->arr_counts[c->n_known]->sz_count = malloc((strlen(name)+1)*sizeof(*c->arr_counts[c->n_known]->sz_count));
      strcpy(c->arr_counts[c->n_known]->sz_count, name);
      c->arr_counts[c->n_known]->n_count = 1;
      c->n_known++;
    }
    else{
      // iterate through number of known
      int i = 0;
      int bFound = 0;

      do{
	if (strcmp(c->arr_counts[i]->sz_count,name)==0){
	  c->arr_counts[i]->n_count++;
	  bFound = 1;
	}
	i++;
      }
      while(bFound == 0 && i < c->n_known);

      // if not found any same name, add new obj with new name
      if (bFound == 0){
	c->arr_counts = realloc(c->arr_counts, (c->n_known+1)*sizeof(*c->arr_counts));
	c->arr_counts[c->n_known] = malloc(sizeof(**c->arr_counts));
	c->arr_counts[c->n_known]->sz_count = malloc((strlen(name)+1)*sizeof(*c->arr_counts[c->n_known]->sz_count));
	strcpy(c->arr_counts[c->n_known]->sz_count, name);
	c->arr_counts[c->n_known]->n_count = 1;
	c->n_known++;
      }
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->n_known; i++){
    fprintf(outFile, "%s: %u\n", c->arr_counts[i]->sz_count, c->arr_counts[i]->n_count);
  }

  if (c->n_unknown != 0){
    fprintf(outFile, "<unknown> : %lu\n", c->n_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for(int i = 0; i < c->n_known; i++){
    free(c->arr_counts[i]->sz_count);
    free(c->arr_counts[i]);
  }
  free(c->arr_counts);
  free(c);
}
