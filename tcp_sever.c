#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

// ./tcp_server 127.0.0.1 8080
static void usage(const char* arg)
{
    printf("%s [local_ip] [local_port]\n",arg);
}

int CreatSock( char* _ip, int _port)
{
    int sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
     {
       perror("socket\n");
       exit(2);
     }

    int opt=1;
    int ret=setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if(ret<0)
    {
        perror("setsockopt");
        exit(7);
    }
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(_port);
    server.sin_addr.s_addr=inet_addr(_ip);

    if(bind(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        perror("bind\n");
        exit(3);
    }

    if(listen(sock,5)<0)
    {
        perror("listen\n");
        exit(4);
    }

    return sock;
}
void* handlerRequest(void* arg)
{
    int AcceptFd=(int)arg;
    while(1)
    {
        char buf[1024];
        ssize_t r=read(AcceptFd,buf,sizeof(buf)-1);
        if(r>0)
        {
            buf[r]=0;
            printf("client say:%s\n",buf);
            write(AcceptFd,buf,strlen(buf));
        }
        else
        {
            printf("read done...\n");
            break;
        }
    }
}

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        usage(argv[0]);
        exit(1);
    }

    int listenSock=CreatSock(argv[1],atoi(argv[2]));
    while(1)
    {
        struct sockaddr_in client;
        socklen_t len=sizeof(client);
        int AcceptFd=accept(listenSock, (struct sockaddr*)&client, &len);
        if(AcceptFd<0)
        {
            perror("accept\n");
            break;
        }

       //pthread_t id;
       //pthread_create(&id,NULL,handlerRequest,(void*)AcceptFd);
       //pthread_detach(id);

        //version 2
        pid_t fd=fork();
        if(fd<0)
       {
            perror("fork\n");
            exit(6);
        }
        else if(fd==0)
        {//child
            close(listenSock);
            if(fork()>0)
            {
                exit(0);
            }
            while(1)
            {
                char buf[1024];
                ssize_t _s=read(AcceptFd,buf,sizeof(buf)-1);
                if(_s>0)
                {
                    buf[_s]=0;
                    printf("client say:%s\n",buf);
                    write(AcceptFd,buf,strlen(buf));
                }
                else
                {
                    printf("read done...\n");
                    break;
                }
            }
            close(AcceptFd);
        }
        else
        {//father
            close(AcceptFd);
        }


       //version1
       // while(1)
        //{
           // char buf[1024];
           // ssize_t s=read(AcceptFd,buf,sizeof(buf)-1);
           // if(s>0)
            //{
                //buf[s]=0;
                //printf("client say:%s\n",buf);
                //write(AcceptFd,buf,strlen(buf));
            //}
            //else
            //{
                //printf("read done ...\n");
                //break;
            //}
        //}
    }
    return 0;
}
