#include "server.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rina/api.h>
#include <time.h>
#include <sys/types.h>


#include "../network/network.h"

//Main Function

/*int main(){
    filesizeChar = (int*)malloc(100 * sizeof(int));
    filename = (int*)malloc(100 * sizeof(int));
    APP_Name = (int*)malloc(100 * sizeof(int));
}*/


int loadServer()
{
    loadNetwork(1);
    int pl;

    while (1)
    {
        pid_t pr = fork();

        if (pr < 0)
        {
            perror("fork");
        }

        else
        {
            if (pr > 0) //Parent proccess
            {
                //      Client_ID++;
                //      printf("\nClient_ID = %d", Client_ID);
                loadAppNetwork(1);
            }

            else if (pr == 0) //child proccess
            {

                Client_ID++;
                printf("\nClient_ID = %d", Client_ID);
                //                      getAppName(respond_fd);
                getname(respond_fd);
                getsize(respond_fd);

                char b[filesize];

                getcont(respond_fd, b);
                setcont(b);

                close(respond_fd);
                close(accept_fd);
                break;
            }
        }
    }
    return 0;
}



/*void getAppName(int res)
{
    if (res > 0)
    {
        read(res, APP_Name);
        printf("Applicaton_Name: %s", APP_Name);
    }
}*/
//editttt
//Getting file name
/*void getname(int res)
{
    if (res > 0)
    {
        read(res, filename);
        printf("\nFile_name: %s", filename);
        ftruncate(res, 0);
    }
}*/

//Getting file size
/*void getsize(int res)
{
    if (res > 0)
    {
        read(res, filesizeChar);
        filesize = atoi(filesizeChar);
        printf("\nFile_size: %d", filesize);
    }
}*/


//myedit
char* getname(int res)   /* no need to pass num by pointer */
{
    char* names;
    names = malloc(res * sizeof(char*));
    return names;
}
char* getsize(int res)   /* no need to pass num by pointer */
{
    char* names;
    names = malloc(res * sizeof(char*));
    return names;
}

//Getting file content
void getcont(int res, char* buf)
{
    //Total amount of bytes read until current interation
    int total_read = 0;
    //Amount of bytes to read during current iteration
    int to_read = 0;
    //Amount of bytes read during current iteration
    int loop_read;

    while (total_read < filesize) {

        int to_read = 1400;

        if (total_read + to_read > filesize)
            to_read = filesize - total_read;

        loop_read = read(res, &buf[total_read], to_read);
        if (loop_read <= 0) break;
        total_read += loop_read;
        printf("%d", total_read / filesize);
    }
    if (res > 0)
    {
        printf("\nFile_content: %s\n", buf);
    }
}

//Creating file with name, size and content
void setcont(char* buf)
{
    FILE* object;

    if ((object = fopen(strcat(filename, "New"), "w")) != NULL)
    {
        fwrite(buf, 1, filesize, object);
        fclose(object);

        //empty the buffer
        for (int i = 0; i <= filesize; i++)
        {
            buf[i] = '\0';
        }
    }
    else
    {
        printf("fopen error\n");
    }
}

