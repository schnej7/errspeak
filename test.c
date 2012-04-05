#include <stdlib.h>
#include <stdio.h>
#include "errspeak.h"


int main( int argv, char * argc[] ){
  perror("THIS IS AN ERROR!");
  return EXIT_SUCCESS;
}

