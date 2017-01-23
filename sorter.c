#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

unsigned int* getUserValues();

int main(int argc, char *argv[], char *envp[]){
  //Print a usage string on stderr, then exit.
  unsigned short int u_flag = FALSE;

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
  char* input_file = NULL;

  //Output-File-Name
  unsigned short int o_flag = FALSE;
  char* output_file = NULL;

  //Count-File-Name
  unsigned short int c_flag = FALSE;
  char* count_file = NULL;
  
  
  int opt = getopt(argc, argv, "unmMioc:");
  opterr = 1;
  
  while(opt != -1){
    sleep(1);
    switch(opt){
    case 'u':
      {
	
	break;
      }
    case 'n':
      {
       n_flag = TRUE;
       //unsigned int testable = (unsigned int)*optarg;
    
       break;
      }
    case 'm':
      {
      

	break;
      }
    case 'M':
      {

      
	 break;
      }
    case 'i':
      {

      
	break;
      }
    case 'o':
      {

	
	break;
      }
    case 'c':
      {
	
	
	break;
      }
    default:
      {
	break;
      }
    }
    opt = getopt(argc, argv, "unmMioc:");
  }
  


  
  
  unsigned int *username_array = getUserValues();
  
  free(username_array);
  
  return 0;
}

unsigned int* getUserValues(){
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
