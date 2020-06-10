#ifndef server_h
#define server_h

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rina/api.h>
#include <time.h>
#include <sys/types.h>


#include "../network/network.h"

clock_t start, end;
double cpu_time_used;

int Client_ID = 0;
struct pollfd fds[2];
int nt_timeout, filesize;

//char filename[2048];
//char filesizeChar[2048];
//char APP_Name[100];
char* filesizeChar;
char* filename;
char APP_Name[100];

//Functions
//void getAppName(int res);
//editttt
//void getname(int res);
//void getsize(int res);
//myedit
char* getname(int res);
char* getsize(int res);
void getcont(int res, char* buf);
void setcont(char* buf);



#endif /* server_h */
