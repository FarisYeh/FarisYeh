#include<stdio.h>
#include<string.h>
#include<net/if.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define BUFLEN 600
#define PORT 7777

int main()
{	
	struct sockaddr_in server,client;
	int cSocket,clientLen=sizeof(client), recLen;
	char msg[BUFLEN];
	char rec[BUFLEN];	
	cSocket=socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);
	memset((char *) &server, 0, sizeof(server));


	puts("socket has created");


	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(PORT);
	bind(cSocket,(struct sockaddr*)&server,sizeof(server));
	puts("Listening to the client ....");

	
	puts("---connection accept---");

	
	
	

		time_t o;
		struct tm tt;
		char b[300];
		time(&o);
		tt=*localtime(&o);
		strftime(b,sizeof(b),"%a %Y/%m/%d %H:%M:%S %Z", &tt);
//		printf("%s\n",b);		
	recvfrom(cSocket,msg,BUFLEN,0 , (struct sockaddr *) &client, 
&clientLen);	
		if(strcasecmp(msg,"time")==0){
		strcpy(msg,b);
		
		printf("%s\n",b);	
	sendto(cSocket,msg,600,0, (struct sockaddr *) &client, 
clientLen);	
}

	close(cSocket);
	return 0;

}
