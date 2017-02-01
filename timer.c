#include <time.h>
#include <stdio.h>
#include "timer.h"
#define TRUE 1
#define FALSE 0


clock_t time_start, time_end;
int started_flag = FALSE;

int recordStart(){
  if(started_flag == FALSE){
    time_start = clock();
    started_flag = TRUE;
    //Check clock_t/clock() documentation for possible error codes
    return 1;
  }else{
    return -1;
  }
  
}

int recordEnd(){
  if(started_flag == TRUE){
    time_end = clock();
    started_flag = FALSE;
    //Check clock_t/clock() documentation for possible error codes
    double elapsed_time = (double)(time_end - time_start) / CLOCKS_PER_SEC;
    fprintf(stderr, "Time measured: %f\n", elapsed_time);
    
    return 1;
  }else{
    return -1;
  }
}
