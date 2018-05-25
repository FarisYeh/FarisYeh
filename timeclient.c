#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<time.h>
#define PORT 7777
#define BUFLEN 600
#define SERVER "192.168.244.128"


int main()

{	
	struct sockaddr_in client;
	int cSocket,clientLen=sizeof(client);
	char msg[BUFLEN];
	char rep[BUFLEN];
	cSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	memset((char *) &client, 0, sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(PORT);
	
	inet_aton(SERVER, &client.sin_addr);
	puts("----Connected----");
		
	
	printf(" say something : ");
	scanf("%s",msg);
	sendto(cSocket,msg,strlen(msg),0,(struct sockaddr *) &client, 
clientLen);

	if(strcasecmp(msg,"time")==0)
{
	recvfrom(cSocket,msg,BUFLEN, 0, (struct sockaddr *) 
&client, &clientLen);
}	
	printf("Server say to you: ");
	puts(msg);
	
	
	printf("---Server closed !!---\n");

	close(cSocket);

	return 0;

}
