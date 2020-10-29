#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<sys/socket.h>
short SocketCreate(void)
{
short hSocket;
printf("create the socket:\n");
hSocket=socket(AF_INET,SOCK_STREAM,0);
return hSocket;
}
int BindCreatedSocket(int hSocket)
{
int iRetval=-1;
int Clientport=9000;
struct sockaddr_in remote={0};
remote.sin_family=AF_INET;
remote.sin_addr.s_addr=htonl(INADDR_ANY);
remote.sin_port=htons(Clientport);
iRetval=bind(hSocket,(struct sockaddr*)&remote,sizeof(remote));
return iRetval;
}
int main(int argc,char *argv[])
{
int socket_desc,sock,clientLen,read_size;
struct sockaddr_in server, client;
char client_message[20000]={0};
char message[100]={0};
const char *pMessage="hello article world.com";
socket_desc=SocketCreate();
if(socket_desc==-1)
{
printf("could not create socket");
return 1;
}
printf("socket created\n");
if(BindCreatedSocket(socket_desc)<0)
{
perror("bind failed");
return 1;
}
printf("bind done\n");
listen(socket_desc,3);
while(1)
{
printf("waiting for incoming connections...\n");
clientLen=sizeof(struct sockaddr_in);
sock=accept(socket_desc,(struct sockaddr*)&client,(socklen_t*)&clientLen);
if(sock<0)
{
perror("accept failed\n");
return 1;
}
printf("connection accepted \n");
memset(client_message,'\0',sizeof client_message);
memset(message,'\0',sizeof message);
if(recv(sock,client_message,19999,0)<0)
{
printf("recv failed");
break;
}
printf("client reply:%s\n",client_message);
}
return 0;
}







