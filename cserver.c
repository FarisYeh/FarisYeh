#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int socket_desc,c_sock,c,read;
	struct sockaddr_in server,client;
	char c_message[1500];
	char j [1500];
	char k[] = "assalamualaikum";

	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc==-1)
	{	printf("cannot create socket");
	}
	puts("socket has created");

	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(6786);
	
	if(bind(socket_desc,(struct sockaddr 
*)&server,sizeof(server))<0)
	{	perror("error");
		return 1;
	}
	puts("Listening to the client ....");

	listen(socket_desc,3);

	c=sizeof(struct sockaddr_in);
	c_sock=accept(socket_desc,(struct sockaddr 
*)&client,(socklen_t*)&c);
	if(c_sock<0)
	{	perror("failed");
		return 1;
	}
	puts("---connection accept---");
	
	read=recv(c_sock,c_message,1500,0);
	printf("Message from Client  : " );
	puts(c_message);
	
	strcpy(j,c_message);
	if(strcasecmp(j,k)==0)
	{
		strcpy(c_message,"Waalaikummussalam");
	}else
	{
		strcpy(c_message,"Are you a muslim");
	} 		
	write(c_sock,c_message,strlen(c_message));
	printf("Replying to client......\n");
	printf("--Client Disconnected--\n");	
	return 0;
}
