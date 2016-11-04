#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int logging(char *message, char *path_3)
{
    char text[1024];
/*	text = malloc(sizeof(char[1024]);*/
    int fd,ret;
    time_t rawtime;
    struct tm *info;
    char time_now[80];
    time( &rawtime );
    info = localtime( &rawtime );
    strftime(time_now,80,"%x - %I:%M:%S %p", info);
    sprintf(text, "%s : %s \n",time_now, message );
    fd =  open(path_3, O_WRONLY|O_CREAT|O_APPEND,S_IREAD|S_IWUSR|S_IWRITE|S_IWGRP|S_IRGRP);
    if (fd < 1) {
        printf("%d\n",fd);
        printf("error logging: %s\n",strerror(errno));
        return fd;
    }
    else
    {
        ret = write(fd,text,strlen(text));
        if (ret<0)
        {
            printf("Error Logging no write: %s \n",strerror(errno));
            return ret;
        }
    }
    return 0;

}

#endif // LOGGER_H
