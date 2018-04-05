#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc,char*argv[])
{	int sc;
	struct sockaddr_in server;
	char msg[1000];
	char s_reply[2000];

	sc=socket(AF_INET,SOCK_STREAM,0);
	if(sc==-1)
	{	printf("cannot create the socket");
	}
	puts("socket has created");
	server.sin_addr.s_addr=inet_addr("192.168.244.128");
	server.sin_family=AF_INET;
	server.sin_port=htons(6786);

	if(connect(sc,(struct sockaddr*)&server,sizeof(server))<0)
	{ perror("connection failed");
	return 1;
	}
	puts("----Connected----");
	
	
	 printf("Say something to server please : ");
	 scanf("%s",msg);
	
	if(send(sc,msg,strlen(msg),0)<0)
	{
		puts("send failed.....");
		return 1;
	}

	if(recv(sc,s_reply,2000,0)<0)
	{	puts("received failed !!" );
	
	}
	printf("Server say to you : ");
	puts(s_reply);
	printf("---Server closed !!---\n");
	close(sc);
	return 0;
}
