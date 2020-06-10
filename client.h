#ifndef client_h
#define client_h

#include <sys/stat.h>
#include <libgen.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <rina/api.h>
#include <time.h>


#include "../network/network.h"

//Global variables
clock_t start, end;
double cpu_time_used;
struct stat stat_buffer;
char filePath[128];
char* buff;
int fd;

void file_read(int connection_fd, char* buffer);
void sr_feedback(int connection_fd);

#endif
