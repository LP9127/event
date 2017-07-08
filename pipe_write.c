#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    if(unlink("/tmp/pipe.tmp")<0)
    {
        perror("unlink");
        exit(3);
    }
    umask(0);
    int ret=mkfifo("/tmp/pipe.tmp",S_IFIFO|0664);
    if(ret==-1)
    {
        perror("mkfifo");
        exit(1);
    }
    int fd=open("/tmp/pipe.tmp",O_CREAT|O_RDWR);
    if(fd<0)
    {
        perror("open");
        exit(2);
    }

    char buf[100];
    while(1)
    {
        printf("please enter:");
        fflush(stdout);
        ssize_t s=read(0,buf,sizeof(buf)-1);
        if(s>0)
        {
            buf[s-1]=0;
            write(fd,buf,strlen(buf));
            if(strncmp("quit",buf,4)==0)
            {
                break;
            }
            printf("%s\n",buf);
        }
    }
    close(fd);
    return 0;
}
