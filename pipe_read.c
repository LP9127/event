#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
    int fd=open("/tmp/pipe.tmp",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        exit(1);
    }

    char buf[100];
    while(1)
    {
        ssize_t s=read(fd,buf,sizeof(buf));
        if(s>0)
        {
            buf[s]=0;
            printf("%s\n",buf);
            if(strncmp(buf,"quit",4)==0)
            {
                break;
            }
        }
    }
    close(fd);
    return 0;
}
