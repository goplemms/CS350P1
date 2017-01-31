#include "option_parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define FREEFILE if(i_flag)free(input_file);if(o_flag)free(output_file);if(c_flag)free(count_file);

#define TRUE 1
#define FALSE 0

unsigned int num_int = 100;
unsigned int min_int = 1;
unsigned int max_int = 255;
unsigned long int seed = 0;
char* input_file = NULL;
char* output_file = NULL;
char* count_file = NULL;

unsigned short int n_flag = FALSE;
unsigned short int m_flag = FALSE;
unsigned short int M_flag = FALSE;
unsigned short int s_flag = FALSE;
unsigned short int i_flag = FALSE;
unsigned short int o_flag = FALSE;
unsigned short int c_flag = FALSE;

int initializeOptions(int argc, char** argv, char* option_string){
   
  int opt = getopt(argc, argv, "un:m:M:i:o:c:s:"); 
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
	  return 1;
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
	  return 1;
	}else if(M_flag && min_int > max_int){
	  fprintf(stderr, "The -M argument should have an integer argument that is greater than the -m argument\n");
	  FREEFILE;
	  return 1;
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
	  return 1;
	}else if(max_int < min_int){
	  fprintf(stderr, "The -M argument should have an integer argument that is greater than the -m argument\n");
	  FREEFILE;
	  return 1;
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
	  return 1;
	}
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist\n", optarg);
	  FREEFILE;
	  return 1;
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
	  return 1;
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
    case 'c':
      {
	if(c_flag){
	  fprintf(stderr, "Duplicate %c option. Ignoring\n", optopt);
	  break;
	}
	if(optarg == NULL){
	  fprintf(stderr,"There must be a path for the count file after -c\n");
	  FREEFILE;
	  return 1;
	}
	count_file = malloc(sizeof(char) * strlen(optarg));
	count_file = strdup(optarg);
	c_flag = TRUE;
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
    case '?':
      //Getopt already returns an informative string
      //fprintf(stderr, "Unrecognized option: -%c\n", optopt);
      fprintf(stderr, "Cannot pass in values through the command line\n");
      FREEFILE;
      return 1;
     
    case ':':
      //Getopt already returns an informative string
      //fprintf(stderr, "Option -%c requires an argument\n", optopt);
      fprintf(stderr, "Cannot pass in values through the command line\n");
      FREEFILE;
      return 1;
    default:
      {
	fprintf(stderr, "Cannot pass in values through the command line\n");
	FREEFILE;
	return 1;
	break;
      }
    }
    opt = getopt(argc, argv, "un:m:M:i:o:c:");
  }
  return 0;
}


/*
  if(access(optarg, F_OK) == -1){
  fprintf(stderr,"The file %s does not exist\n", optarg);
  FREEFILE;
  exit(1);
  }
*/
