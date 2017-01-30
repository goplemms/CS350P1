#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define FREEFILE if(i_flag)free(input_file);if(o_flag)free(output_file);if(c_flag)free(count_file);

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
  
  //Input-File-Name
  unsigned short int i_flag = FALSE;
  FILE* input =NULL;
  char* input_file;
  
  //Output-File-Name
  unsigned short int o_flag = FALSE;
  FILE* output = NULL;
  char* output_file;

  //Count-File-Name
  unsigned short int c_flag = FALSE;
  FILE* count = NULL;
  char* count_file;
  
  
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
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist\n", optarg);
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
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist\n", optarg);
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

  //Create unsorted matrix
  int* matrix = malloc(sizeof(int) * num_int);
  int saved_count = 0;
  int* eval = malloc(sizeof(int));

  if(i_flag){
    input = fopen(input_file, "r");
  }
  
  int check_scan = (i_flag)?fscanf(input,"%d", eval):scanf("%d", eval);
  
  for(; saved_count < num_int; saved_count++){
    if(check_scan != 1){
      fprintf(stderr,"There should be at least %d values being processed\n", num_int);
      FREEFILE;
      free(matrix);
      free(eval);
      exit(1);
    }
    if(*eval >= min_int && *eval <= max_int){
      matrix[saved_count] = *eval;
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
  
  //Return output
  
  
  //Emancipation
  FREEFILE;
    
  if(i_flag){
    fclose(input);
  }
  if(o_flag){
    //fclose(output);
  }
  if(c_flag){
    //fclose(count);
  }
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

