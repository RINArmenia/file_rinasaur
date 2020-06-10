#include "client.h"
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

//Functions

int loadClient()
{
    loadNetwork(2); /* 2 means that network will be configured for client */

    if (alloc_fd >= 0) {
        file_read(alloc_fd, buff);
    }

    return 0;
}

void file_read(int connection_fd, char* buffer)
{
    FILE* object;

    //Get App Name
//        printf("\nApp_name: ");
//        scanf("%s", CL_Name);

        //Get File Path
    printf("\nFile Path: ");
    scanf("%s", filePath);

    while ((object = fopen(filePath, "r")) == NULL)
    {
        filePath[128] = '\0';
        printf("\nThere is no such file, Try again\n");
        printf("\nFile Path: ");
        scanf("%s", filePath);
    }


    if ((object = fopen(filePath, "r")) != NULL)
    {
        //Getting file name
        int object_fd = fileno(object);
        char* object_name = basename(filePath);

        //Getting file size (metadata)
        fstat(object_fd, &stat_buffer);
        int object_size = stat_buffer.st_size;

        //Some informative shit
        printf("File_Name: %s", object_name);
        printf("\nFile_Size: %ld", stat_buffer.st_size);
        printf("\nFile_fd: %d", object_fd);

        //Allocate memory
        buffer = (char*)malloc(sizeof(char) * stat_buffer.st_size);

        if (buffer == NULL)
        {
            perror("Memory error");
            exit(1);
        }

        //Read from file
        if (fread(buffer, 1, stat_buffer.st_size, object) != stat_buffer.st_size) {
            perror("fread error");
            exit(1);
        }
        //send Application N
//              write(connection_fd, CL_Name , strlen(CL_Name));

                //Send file name
        write(connection_fd, object_name, strlen(object_name));

        //send file size
        dprintf(connection_fd, "%d\n", object_size);
        //send file content
        int total_written = 0;
        //Amount of bytes to read during current iteration
        int to_write = 0;
        //Amount of bytes read during current iteration
        int loop_written;

        while (total_written < object_size) {

            int to_write = 1400;

            if (total_written + to_write > object_size)
                to_write = object_size - total_written;

            loop_written = write(connection_fd, &buffer[total_written], to_write);
            if (loop_written <= 0) break;
            total_written += loop_written;
        }
        sr_feedback(connection_fd);
        fclose(object);
        free(buffer);
        close(connection_fd);
    }
    else
        perror("Error:\n");
}

void sr_feedback(int connection_fd)
{
    char f[50];
    read(connection_fd, f, 50);
    printf("\n%s\n", f);
}
