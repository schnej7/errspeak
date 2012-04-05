#include "errspeak.h"


ssize_t (*libc_write)(int fd, const void *buf, size_t count);
void (*libc_perror)(const char *s);
static int pin[2];


void __attribute__ ((constructor)) init(void){
	puts("errspeak.so:init()");
	*(void **)(&libc_write)=dlsym(RTLD_NEXT,"write");
	*(void **)(&libc_perror)=dlsym(RTLD_NEXT,"perror");

	pipe( pin);

	if(fork()){//parent
		dup2( pin[0], STDIN_FILENO);
		close( pin[0]);
		close( pin[1]);

		unsetenv("LD_PRELOAD");//Do you enjoy forkbombs?
		execvp("espeak",(char *const[]){"espeak","--stdin",NULL});
		exit(1);

	}else{//child
		close( pin[0]);

	}

}


void __attribute__ ((constructor)) fini(void){
	puts("errspeak.so:fini()");
}


static ssize_t speakn(const char *buf,size_t size){
	ssize_t retval=libc_write(pin[1],buf,size);
}


static ssize_t speak(const char *buf){
	return speakn(buf,strlen(buf));
}


ssize_t write(int fd, const void *buf, size_t count){
	ssize_t retval=libc_write(fd,buf,count);
	speakn(buf,count);
	return retval;
}


void perror(const char *s){
	libc_perror(s);
	speak(s);
}

