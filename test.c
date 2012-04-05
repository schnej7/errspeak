#include <stdlib.h>
#include <stdio.h>
#include "errspeak.h"


int main( int argv, char * argc[] ){
  int i;
  for( i = 1; i < argv; i++ ){
    char * path = get_path( argc[i] );
    printf("Path: %s\n", path);
  }
  return EXIT_SUCCESS;
}

