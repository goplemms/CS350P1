#ifndef OPTION_PARSE_H
#define OPTION_PARSE_H

extern unsigned int num_int;
extern unsigned int min_int;
extern unsigned int max_int;
extern unsigned long int seed;
extern char* input_file;
extern char* output_file;
extern char* count_file;

extern unsigned short int n_flag;
extern unsigned short int m_flag;
extern unsigned short int M_flag;
extern unsigned short int s_flag;
extern unsigned short int i_flag;
extern unsigned short int o_flag;
extern unsigned short int c_flag;

int initializeOptions(int argc, char** argv, char* option_string);



#endif
