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
#define FREEFILE if(i_flag)free(input_file);if(o_flag)free(output_file);if(c_flag)free(count_file);

char* getUsername();
int compareInt(const void * a, const void * b);


int main(int argc, char *argv[], char *envp[]){
  FILE* input = NULL;
  FILE* output = NULL;
  FILE* count = NULL;
  
  char set[13] = "un:m:M:i:o:c:";
  
  int err_check = initializeOptions(argc, argv, set);
  if(err_check == 1){
    exit(1);
  }

  err_check = recordStart();
  if(err_check < 0){
    exit(1); 
  }
  
  
  //Create unsorted matrix
  int* matrix = malloc(sizeof(int) * num_int);
  memset(matrix, 0, sizeof(int) * num_int);
  int saved_count = 0;
  int* eval = malloc(sizeof(int));

  if(i_flag){
    input = fopen(input_file, "r");
  }
  
  int check_scan = (i_flag)?fscanf(input,"%d", eval):scanf("%d", eval);

  if(*eval != num_int && n_flag){
    FREEFILE;
    if(i_flag){
      fclose(input);
    }
    fprintf(stderr, "The number of inputs does not match the indicated -n\n");
    exit(1);
  }
  
  for(int i = 0; i < num_int; i++){
    if(check_scan != 1){
      fprintf(stderr,"%d being processed when there should be at least %d values being processed\n",*eval, num_int);
      FREEFILE;
      free(matrix);
      free(eval);
      exit(1);
    }
    if(*eval >= min_int && *eval <= max_int){
      matrix[saved_count] = *eval;
      saved_count++;
    }else{
      fprintf(stderr, "The value %d is out of bounds\n", *eval);
    }
    check_scan = (i_flag)?fscanf(input,"%d", eval):scanf("%d", eval);
  }

  free(eval);
  fclose(input);
  
  realloc(matrix, sizeof(int) * (saved_count));

    
  //Sort matrix
    
  qsort(matrix,saved_count,sizeof(int), compareInt);

  /*  
  for(int i = 0; i < saved_count; i++){
    printf("Sorted Order: %d\n", matrix[i]);
    sleep(1);
  }
  */


  //Seek values
  unsigned int username_length = (unsigned int)strlen(getenv("USER"));
  char* username = getUsername();
  unsigned int* matches = malloc(sizeof(unsigned int) * (username_length));
  memset(matches, 0, sizeof(unsigned int) * username_length);

  for(int i = 0; i < saved_count; i++){
    for(int j = 0; j < username_length; j++){
      if(matrix[i] == username[j]){
	matches[j]++;
      }
    }
  }

  /*
  for(int i = 0; i < username_length; i++){
    printf("Character %c occurs %u times\n",username[i], matches[i]);
    sleep(1);
  }
  */

  if(c_flag){
    count = fopen(count_file, "w");
  }
  
  for(int i = 0; i < username_length; i++){
    if(c_flag){
      fprintf(count, "%c\t%u\t%u\n", username[i], username[i], matches[i]);
    }else{
      printf("%c\t%u\t%u\n", username[i], username[i], matches[i]);
    }
  }

  if(c_flag){
    fclose(count);
  }
  
  //Return output

  if(o_flag){
    output = fopen(output_file, "w");
  }

  for(int i = 0; i < saved_count; i++){
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
  
  
  //Emancipation
  FREEFILE;
  free(matches);
  free(matrix);
  free(username);
  return 0;
}

char* getUsername(){
  unsigned int name_length = (unsigned int)strlen(getenv("USER"));
  char* username = malloc(sizeof(char) * name_length);
  strcpy(username,getenv("USER"));
  return username;
}

int compareInt(const void * a, const void * b){
  return (*(int*)a - *(int*)b);
}

/*

  
  int opt = getopt(argc, argv, "un:m:M:i:o:c:"); 
  opterr = 1;

  while(opt != -1){
    switch(opt){
    case 'u':
      {
	fprintf(stderr, "prog1sorter: Sorts integers in ascending order\nOptions: [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
	exit(0);
	break;
      }
    case 'n':
      {
	if(n_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	n_flag = TRUE;
	num_int = 0;
	for(const char *c = optarg; isdigit(*c) != 0; c++){
	  num_int *= 10;
	  num_int += ((*c) - 48);
	}
	if(num_int <= 0 && num_int >= 1000000){
	  fprintf(stderr, "The -n option should have an integer argument that is greater than 0 and less than 1000000\n");
	  FREEFILE;
	  exit(1);
	}
	break;
      }
    case 'm':
      {
	if(m_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	m_flag = TRUE;
	min_int = 0;
	for(const char *c = optarg; isdigit(*c) != 0; c++){
	  min_int *= 10;
	  min_int += ((*c) - 48);
	}
	if(min_int < 1){
	  fprintf(stderr, "The -m option should have an integer argument that is greater than 0\n");
	  FREEFILE;
	  exit(1);
	}else if(M_flag && min_int > max_int){
	  fprintf(stderr, "The -M argument should have an integer argument that is greater than the -m argument\n");
	  FREEFILE;
	  exit(1);
	}
	break;
      }
    case 'M':
      {
	if(M_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	M_flag = TRUE;
	max_int = 0;
	for(const char *c = optarg; isdigit(*c) != 0; c++){
	  max_int *= 10;
	  max_int += ((*c) - 48);
	}
	if(max_int >= 1000000){
	  fprintf(stderr, "The -M option should have an integer argument that is greater than 0 and less than 1000000\n");
	  FREEFILE;
	  exit(1);
	}else if(max_int < min_int){
	  fprintf(stderr, "The -M argument should have an integer argument that is greater than the -m argument\n");
	  FREEFILE;
	  exit(1);
	}
	break;
      }
    case 'i':
      {
	if(i_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	if(optarg == NULL){
	  fprintf(stderr,"There must be a path for the input file after -i\n");
	  FREEFILE;
	  exit(1);
	}
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist\n", optarg);
	  FREEFILE;
	  exit(1);
	}
	input_file = malloc(sizeof(char) * strlen(optarg));
	input_file = strdup(optarg);
	
	i_flag = TRUE;
	break;
      }
    case 'o':
      {
	if(o_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	if(optarg == NULL){
	  fprintf(stderr,"There must be a path for the output file after -o\n");
	  FREEFILE;
	  exit(1);
	}
	
	output_file = malloc(sizeof(char) * strlen(optarg));
	output_file = strdup(optarg);
	o_flag = TRUE;
	break;
      }
    case 'c':
      {
	if(c_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	if(optarg == NULL){
	  fprintf(stderr,"There must be a path for the count file after -c\n");
	  FREEFILE;
	  exit(1);
	}
	count_file = malloc(sizeof(char) * strlen(optarg));
	count_file = strdup(optarg);
	c_flag = TRUE;
	break;
      }
    case '?':
      //Getopt already returns an informative string
      //fprintf(stderr, "Unrecognized option: -%c\n", optopt);
      fprintf(stderr, "Cannot pass in values through the command line\n");
      FREEFILE;
      exit(1);
     
    case ':':
      //Getopt already returns an informative string
      //fprintf(stderr, "Option -%c requires an argument\n", optopt);
      fprintf(stderr, "Cannot pass in values through the command line\n");
      FREEFILE;
      exit(1);
    default:
      {
	fprintf(stderr, "Cannot pass in values through the command line\n");
	FREEFILE;
	exit(1);
	break;
      }
    }
    opt = getopt(argc, argv, "un:m:M:i:o:c:");
  }
  
 */
