#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_installed( char * program_name ){
  char * my_path = getenv( "PATH" );

  char * a_path = strtok ( my_path, ":" );
  
  FILE * fd;
  while( 1 ){
    fd = NULL;
    char * full_path = (char *) malloc( 1 + strlen(program_name) + strlen(a_path) );

    int i;
    for( i = 0; i < strlen(a_path); i++ ){
      full_path[i] = a_path[i];
    }
    full_path[i] = '/';
    for( i = 0; i < strlen(program_name); i++ ){
      full_path[strlen(a_path) + i + 1] = program_name[i];
    }

    fd = fopen( full_path, "r" );
    if( !fd ){
    }
    else{
      close( fd );
      return 1;
    }
    a_path = strtok ( NULL, ":" );

    if( a_path == NULL ){
       break;
    }
  }
  return 0;
}

