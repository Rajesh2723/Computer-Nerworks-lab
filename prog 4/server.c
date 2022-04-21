#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#define SERV_TCP_PORT 6880
#define SERV_HOST_ADDR "127.0.0.1"
int main()
{
int sockfd,newsockfd,client;
struct sockaddr_in cli_addr,serv_addr;
char filename[25],buf[1000];
int n,m,fd,size;
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
serv_addr.sin_port=htons(SERV_TCP_PORT);

    if((sockfd=(socket(AF_INET,SOCK_STREAM,0)))<0)
        {
        printf("Server: can’t open stream socket\n");
        exit(0);
        }
    else
        printf("Server: stream socket opened successfully\n");
    if((bind(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)))<0)
        {
        printf("Server:cant bind local address\n");
        exit(0);
        }
    else
        printf("Server: bind to local address\n");
    listen(sockfd,5);

    printf("\n SERVER : Waiting for client...\n");
    client =sizeof(cli_addr);
    newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&client);


if(newsockfd<0)
    {
    printf("server:accept error\n");
    exit(0);
    }
else
    printf("Server: accepted\n");

n=read(newsockfd,filename,25);
filename[n]='\0';
printf("\n SERVER : %s is found and ready to transfer \n",filename);
fd=open(filename,O_RDONLY);

if(fd==-1)
    {
    write(newsockfd,"File doesn’t exists",25);
    exit(0);
    }
    size=lseek(fd,0,2);
    lseek(fd,0,0);
    n=read(fd,buf,size);
    buf[n]='\0';
    write(newsockfd,buf,n);
    printf("\n transfer success\n");
    puts(buf);
    close(newsockfd);
    exit(0);
}
