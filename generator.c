#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#include "option_parse.h"

#define TRUE 1
#define FALSE 0
#define FREEFILE if(o_flag)free(output_file);

char* getUsername();
int compareInt(const void * a, const void * b);

int main(int argc, char *argv[], char *envp[]){

  char* set = malloc(sizeof(char) * 12);
  set = "un:m:M:s:o:";
  
  int h = initializeOptions(argc, argv, set);
  
  if(h == 1){
    exit(1);
  }
  
  FILE* output = NULL;
  time_t t;
  srand((unsigned int)time(&t));
  int* matrix = malloc(sizeof(int) * num_int);
  memset(matrix, 0, sizeof(int) *num_int);

  for(int i = 0; i < num_int; i++){
    if(s_flag){
      srand(seed);
    }
  }

  //Generate int
  for(int i = 0; i < num_int; i++){
    matrix[i] = (rand() + min_int) % max_int;
  }

  
  if(o_flag){
    output = fopen(output_file, "w");
    fprintf(output, "%d\n", num_int);
  }else{
    printf("%d\n", num_int);
  }
  

  for(int i = 0; i < num_int; i++){
    if(o_flag){
      fprintf(output, "%d\n", matrix[i]);
    }else{
      printf("%d\n", matrix[i]);
    }
  }

  if(o_flag){
    fclose(output);
  }

  FREEFILE;
  
  return 0;
}
