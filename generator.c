#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define FREEFILE if(o_flag)free(output_file);

char* getUsername();
int compareInt(const void * a, const void * b);

//side note
/*
  FILE* title;
  title = fopen(optarg, "w");
*/


int main(int argc, char *argv[], char *envp[]){
  //Read the first n values
  unsigned short int n_flag = FALSE;
  unsigned int num_int = 100;

  //Min-Int readable
  unsigned short int m_flag = FALSE;
  unsigned int min_int = 1;
  
  //Max-Int readable
  unsigned short int M_flag = FALSE;
  unsigned int max_int = 255;

  //Seed
  time_t t;
  srand((unsigned int)time(&t));
  unsigned short int s_flag = FALSE;
  unsigned long int seed = 0;
  
  //Output-File-Name
  unsigned short int o_flag = FALSE;
  FILE* output = NULL;
  char* output_file;

  
  int opt = getopt(argc, argv, "un:m:M:s:o:"); 
  opterr = 1;
  
  while(opt != -1){
    switch(opt){
    case 'u':
      {
	fprintf(stderr, "prog1generator: Generates random integers\nOptions: [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]\n");
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
    case 's':
      {
	if(s_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	s_flag = TRUE;
	for(const char *c = optarg; isdigit(*c) != 0; c++){
	  seed *= 10;
	  seed += ((*c) - 48);
	}
	
	srand(seed);
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
	/*
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist\n", optarg);
	  FREEFILE;
	  exit(1);
	}
	*/
	
	output_file = malloc(sizeof(char) * strlen(optarg));
	output_file = strdup(optarg);
	o_flag = TRUE;
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
    opt = getopt(argc, argv, "un:m:M:s:o:");
  }

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
