#ifndef _ERRSPEAK_H_
#define _ERRSPEAK_H_

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>


ssize_t write(int fd, const void *buf, size_t count);
char * get_path(char * program_name);
void perror(const char *s);


#endif
