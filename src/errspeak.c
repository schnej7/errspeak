#include "errspeak.h"


ssize_t (*libc_write)(int fd, const void *buf, size_t count);


void __attribute__ ((constructor)) init(void){
	puts("errspeak.so:init()");
	*(void **)(&libc_write)=dlsym(RTLD_NEXT,"write");
}


void __attribute__ ((constructor)) fini(void){
	puts("errspeak.so:fini()");
}


ssize_t write(int fd, const void *buf, size_t count){
	puts("errspeak.so:write()");

	ssize_t retval=(libc_write)(fd,buf,count);
	return retval;
}


void perror(const char *s){
	if( !get_path("espeak") ){
		fprintf( stderr, "%s\n", s );
		return;
	}
	else if( fork()) {
		char * espeak = "espeak ";
		char * to_say = (char *) malloc (strlen(espeak) + strlen(s) + 1);
		int i;
		for( i = 0; i < strlen(espeak); i++ ){
			to_say[i] = espeak[i];
		}
		for( i = 0; i < strlen(s); i++ ){
			to_say[strlen(espeak) + i] = s[i];
		}
		to_say[strlen(espeak)+i] = '\0';
		fprintf( stderr, "%s\n", to_say );
		fclose( stdout );
		fclose( stderr );
		int rc = system( to_say );
		rc++;
		return;
	}

}


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
			fclose( fd );
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
