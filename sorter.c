#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define FREEFILE if(i_flag){free(input_file);}if(o_flag){free(output_file);}if(c_flag){free(count_file);}

unsigned int* getUsername();
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
  char* input_file;
  
  //Output-File-Name
  unsigned short int o_flag = FALSE;
  char* output_file;

  //Count-File-Name
  unsigned short int c_flag = FALSE;
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
	n_flag = TRUE;
	num_int = 0;
	for(const char *c = optarg; isdigit(*c) != 0; c++){
	  num_int *= 10;
	  num_int += ((*c) - 48);
	}
	if(num_int <= 0 && num_int >= 1000000){
	  fprintf(stderr, "The -n option should have an integer argument that is greater than 0 and less than 1000000\n");
	  FREEFILE
	    exit(1);
	}
	break;
      }
    case 'm':
      {
	m_flag = TRUE;
	min_int = 0;
	for(const char *c = optarg; isdigit(*c) != 0; c++){
	  min_int *= 10;
	  min_int += ((*c) - 48);
	}
	if(min_int < 1){
	  fprintf(stderr, "The -m option should have an integer argument that is greater than 0\n");
	  FREEFILE
	    exit(1);
	}else if(M_flag && min_int > max_int){
	  fprintf(stderr, "The -M argument should have an integer argument that is greater than the -m argument\n");
	  FREEFILE
	    exit(1);
	}
	break;
      }
    case 'M':
      {
	M_flag = TRUE;
	max_int = 0;
	for(const char *c = optarg; isdigit(*c) != 0; c++){
	  max_int *= 10;
	  max_int += ((*c) - 48);
	}
	if(max_int >= 1000000){
	  fprintf(stderr, "The -M option should have an integer argument that is greater than 0 and less than 1000000\n");
	  FREEFILE
	    exit(1);
	}else if(max_int < min_int){
	  fprintf(stderr, "The -M argument should have an integer argument that is greater than the -m argument\n");
	  FREEFILE
	    exit(1);
	}
	break;
      }
    case 'i':
      {
	i_flag = TRUE;
	if(optarg == NULL){
	  fprintf(stderr,"There must be a path for the input file after -i\n");
	  FREEFILE
	    exit(1);
	}
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist", optarg);
	  FREEFILE
	    exit(1);
	}
	input_file = malloc(sizeof(char) * strlen(optarg));
	input_file = strdup(optarg);
	break;
      }
    case 'o':
      {
	o_flag = TRUE;
	if(optarg == NULL){
	  fprintf(stderr,"There must be a path for the output file after -o\n");
	  FREEFILE
	    exit(1);
	}
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist", optarg);
	  FREEFILE
	    exit(1);
	}
	output_file = malloc(sizeof(char) * strlen(optarg));
	output_file = strdup(optarg);
	break;
      }
    case 'c':
      {
	c_flag = TRUE;
	if(optarg == NULL){
	  fprintf(stderr,"There must be a path for the count file after -c\n");
	  FREEFILE
	    exit(1);
	}
	if(access(optarg, F_OK) == -1){
	  fprintf(stderr,"The file %s does not exist", optarg);
	  FREEFILE
	    exit(1);
	}
	count_file = malloc(sizeof(char) * strlen(optarg));
	count_file = strdup(optarg);
	break;
      }
    case '?':
      //Getopt already returns an informative string
      //fprintf(stderr, "Unrecognized option: -%c\n", optopt);
      fprintf(stderr, "Cannot pass in values through the command line\n");
      FREEFILE
	exit(1);
     
    case ':':
      //Getopt already returns an informative string
      //fprintf(stderr, "Option -%c requires an argument\n", optopt);
      fprintf(stderr, "Cannot pass in values through the command line\n");
      FREEFILE
	exit(1);
    default:
      {
	fprintf(stderr, "Cannot pass in values through the command line\n");
	FREEFILE
	exit(1);
	break;
      }
    }
    opt = getopt(argc, argv, "un:m:M:i:o:c:");
  }

  
  //Create unsorted matrix
  int* matrix = malloc(sizeof(int) * num_int);
  int saved_count = 0;
  if(!i_flag){
    int* eval = malloc(sizeof(int));
    int check_scan = scanf("%d", eval);
    for(; saved_count < num_int && check_scan == 1; saved_count++){
      if(*eval >= min_int && *eval <= max_int){
	matrix[saved_count] = *eval;
      }
      check_scan = scanf("%d", eval);
    }
    free(eval);
  }else{
    //read from input_file path
  }
 
  realloc(matrix, sizeof(int) * (saved_count));

    
  //Sort matrix
    
  qsort(matrix,saved_count,sizeof(int), compareInt);


  //Seek values
  unsigned int *username_array = getUsername();



  //Return output
  
  
  //Emancipation
  FREEFILE
  free(matrix);
  free(username_array);
  
  return 0;
}

unsigned int* getUsername(){
  unsigned int name_length = (unsigned int)strlen(getenv("USER"));
  unsigned int *username_array = malloc(sizeof(unsigned int) * name_length);
  char* username = malloc(sizeof(char) * name_length);
  strcpy(username,getenv("USER"));
  for(unsigned int i = 0; i < name_length; i++){
    username_array[i] = (int)username[i];
  }
  free(username);
  return username_array;
}

int compareInt(const void * a, const void * b){
  return (*(int*)a - *(int*)b);
}

