#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "timer.h"

#include "option_parse.h"

#define TRUE 1
#define FALSE 0
#define FREEFILE if(o_flag)free(output_file);

char* getUsername();
int compareInt(const void * a, const void * b);

int main(int argc, char *argv[], char *envp[]){

  char set[12] = "un:m:M:s:o:";
  
  int err_check = initializeOptions(argc, argv, set);
  
  if(err_check == 1){
    exit(1);
    }
  
  err_check = recordStart();
  if(err_check < 0){
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
  
  err_check = recordEnd();
  if(err_check < 0){
    exit(1); 
  }

  FREEFILE;
  
  return 0;
}
