#include <stdlib.h>
#include <stdio.h>

int is_installed( char * program_name ){
  char * my_path = getenv( "PATH" );
  printf("%s\n", my_path );
  return 0;
}

