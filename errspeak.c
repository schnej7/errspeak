#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * get_path( char * program_name ){
  char * complete_path = getenv( "PATH" );
  char * my_path = (char *) malloc( strlen(complete_path) + 1);
  strncpy( my_path, complete_path, strlen(complete_path) );
  my_path[strlen(complete_path)] = '\0';

  char * a_path = strtok ( my_path, ":" );
  
  FILE * fd;
  while( 1 ){
    fd = NULL;
    char * full_path = (char *) malloc( 2 + strlen(program_name) + strlen(a_path) );

    int i;
    for( i = 0; i < strlen(a_path); i++ ){
      full_path[i] = a_path[i];
    }
    full_path[i] = '/';
    for( i = 0; i < strlen(program_name); i++ ){
      full_path[strlen(a_path) + i + 1] = program_name[i];
    }
    full_path[strlen(a_path) + 1 + i] = '\0';

    fd = fopen( full_path, "r" );

    if( fd ){
      while( a_path ) a_path = strtok( NULL, ":" );
      close( fd );
      free(my_path);
      return full_path;
    }
    free( full_path );

    a_path = strtok ( NULL, ":" );

    if( a_path == NULL ){
      printf("Done\n");
      free( my_path );
      break;
    }
  }
  return NULL;
}

