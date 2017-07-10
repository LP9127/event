#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


int CreatSock(const char* _ip,int _port)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket\n");
        exit(2);
    }
    return sock;
}

void usage(const char* arg)
{
    printf("%s [sever_ip] [sever_port]\n",arg);
}
int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        usage(argv[0]);
        exit(1);
    }

    int sock=CreatSock(argv[1],atoi(argv[2]));
    struct sockaddr_in remote;
    remote.sin_family=AF_INET;
    remote.sin_port=htons(atoi(argv[2]));
    remote.sin_addr.s_addr=inet_addr(argv[1]);

    if(connect(sock,(struct sockaddr*)&remote,sizeof(remote))<0)
    {
        perror("connect\n");
        exit(2);
    }

    while(1)
    {
        char buf[1024];
        printf("please enter:");
        fflush(stdout);
        ssize_t s=read(0,buf,sizeof(buf)-1);
        if(s>0)
        {
            buf[s-1]=0;
            write(sock,buf,strlen(buf));
            ssize_t S=read(sock,buf,sizeof(buf)-1);
            if(S>0)
            {
                buf[S]=0;
                printf("sever echo:%s\n:",buf);
            }
        }
    }
    return 0;
}
