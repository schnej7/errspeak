#include <stdlib.h>
#include <stdio.h>
#include "errspeak.h"

int main( int argv, char * argc[] ){
  if( argv <= 1 ) return EXIT_FAILURE;
  if (is_installed( argc[1] ) ){
    printf("%s is installed\n", argc[1]);
  }
  else{
    printf("%s is not installed\n", argc[1]);
  }
  return EXIT_SUCCESS;
}

