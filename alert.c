/* 
Student Name: Connor Sparkman
Student NetID: cps260 
Compiler Used: Linux CMD
Program Description: Program opens and reads a file, converts from 2-byte element to 4-byte integer, print whether ea
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
union data{
    int number;
    char byte[4];
};


// count number of values since last alert
int alerts(int count, int times){

if(count == 0){
times = 0;
}

if(count == 1){
times += 1;
}
return times;
}

int main(int argc, char *argv[])
{
  // initialize variables
  int times = 0;
  // open & read
  int fd = open("flowData.dat", O_RDONLY);

   union data x;
   x.number = 0;

    while (1) {
    int rdVals;
    rdVals = read(fd,x.byte,2);
    if(rdVals == 0)
    	break;
    if (rdVals == -1)
    {
    	perror("read");
    	exit(EXIT_FAILURE);
    }
  // for each value in file, test to see if pressure is low, high, or fine
  if(x.number > 450 && x.number < 550){
  printf("Low pressure. %d values since last alert.\n", times);
  times = alerts(0, times);
  }
  
  // if pressure is high
  if(x.number > 1450 && x.number < 1550){
  printf("High pressure. %d values since last alert.\n", times);
  times = alerts(0, times);
  }
  
  // if pressure is fine
  if(x.number >= 550 && x.number <= 1450){
  times = alerts(1,times);
  }
}
    
// close file
(void) close(fd);
return 0;  
}
