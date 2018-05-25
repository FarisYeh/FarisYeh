#include<netinet/tcp.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include<errno.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
	int socket_desc,c_sock,c,read,hostname,cname,cp;
	int olen,opval,oplen,optval;
	struct sockaddr_in server,client;
	char c_message[3000];
	char j [2000];
	char po [300];
	char hostb[3000],s_IP[3000],c_IP[3000],
	clientn[3000],MTU[20];
	char k[] = "assalamualaikum";
	int value=1,nonvalue=0;
	hostname = gethostname(hostb,sizeof(hostb));
	struct ifreq ifr;

	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc==-1)
	{	printf("cannot create socket");
	}

	puts("socket has created");
	
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(6786);
	
	if(bind(socket_desc,(struct sockaddr *)&server,sizeof(server))<0)
	{	perror("error");
		return 1;
	}
	puts("Listening to the client ....");

	listen(socket_desc,3);
	c=sizeof(struct sockaddr_in);
	c_sock=accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);

	if(c_sock<0)
	{	perror("failed");
		return 1;
	}
	puts("---connection accept---");
	
	bzero(&server, sizeof(server));
	int len = sizeof(server);
	getsockname(c_sock, (struct sockaddr *) &server, &len);
	inet_ntop(AF_INET, &server.sin_addr, s_IP, sizeof(s_IP));
	int Port=ntohs(server.sin_port);
	char p[100];
	sprintf(po," %d" ,Port);
	int ln = sizeof(client);
	getpeername(c_sock,(struct sockaddr *) &client, &ln);
	inet_ntop(AF_INET, &client.sin_addr,c_IP, sizeof(c_IP));
	int Cport=ntohs(client.sin_port);
	char cpo[100];
	sprintf(cpo,"%d",Cport);

	while(1){
	recv(c_sock,c_message,200,0);
	strcpy(j,c_message);
	char w[]="hostip";
	char y[]="hostname";
	char x[]="clientip";
	char z[]="exit";
	char p[]="port";
	char r[]="clientport";
	char c[]="clientname";
	if(strcasecmp(j,k)==0)
	{	strcpy(c_message,"Waalaikummussalam");	}
	else if(strcasecmp(j,r)==0)
	{	strcpy(c_message,cpo);	}
	else if(strcasecmp(j,y)==0)
	{	strcpy(c_message,hostb);}
	else if(strcasecmp(j,w)==0)
	{	strcpy(c_message,s_IP);	}
	else if(strcasecmp(j,x)==0)
	{	strcpy(c_message,c_IP);	}
	else if(strcasecmp(j,z)==0)
	{	strcpy(c_message,z);	}
	else if(strcasecmp(j,p)==0)
	{	strcpy(c_message,po);	}
	else if(strcasecmp(j,"getmtu")==0)
	{	strcpy(ifr.ifr_name, "wm0");
			if(!ioctl(socket_desc,SIOCGIFMTU, &ifr))
			{	ifr.ifr_mtu;	}
			sprintf(MTU, "%d", ifr.ifr_mtu);
			strcpy(c_message,MTU);
	}
	else if(strcasecmp(j,"setmtu")==0)
	{	strcpy(c_message,"enter new  mtu : ");
		send(c_sock,c_message,100,0);
		recv(c_sock,c_message,100,0);
		strcpy(ifr.ifr_name, "wm0" );
		if(!ioctl(socket_desc, SIOCGIFMTU, &ifr))
		{	ifr.ifr_mtu;	}
		int imtu=atoi(c_message);
		ifr.ifr_mtu = imtu;
	}
	else if(strcasecmp(j,"getoob")==0)
	{	olen = sizeof(opval);
		getsockopt(socket_desc,SOL_SOCKET,SO_OOBINLINE,(char *)&opval, &oplen);
		if(opval==0)
			strcpy(c_message,"oob out of normal queue");
		else
			strcpy(c_message,"oob in normal queue");	
	}else if(strcasecmp(j,"setoob")==0)
	{	strcpy(c_message,"set in or out of the queue ");
		send(c_sock,c_message,200,0);
		recv(c_sock,c_message,200,0);
		char t[300];
		strcpy(t,c_message);
		if(strcasecmp(t,"inqueue")==0)
		{	optval=1;
			setsockopt(socket_desc, SOL_SOCKET, 
SO_OOBINLINE, (char *) &optval, sizeof(int));	}
		else if(strcasecmp(t,"outqueue")==0)
		{	optval=0;
			setsockopt(socket_desc, SOL_SOCKET, 
SO_OOBINLINE, (char *) &optval, sizeof(int));	}
	}else if(strcasecmp(j,"gettcp")==0)
	{	olen=sizeof(opval);
		cp=getsockopt(socket_desc, IPPROTO_TCP, TCP_NODELAY, 
(char *) &opval, &oplen);
		if(opval==0)
			strcpy(c_message," NoDelay : Disabled");
		else		
			strcpy(c_message,"NoDelay : Enabled");
	}else if(strcasecmp(j,"settcp")==0)
	{	strcpy(c_message," enable or disable Tcp !?");
		send(c_sock,c_message,200,0);
		recv(c_sock,c_message,200,0);
		char u[900];
		strcpy(u,c_message);
		if(strcasecmp(u,"enable")==0)
		{	optval=1;
			setsockopt(socket_desc, IPPROTO_TCP,TCP_NODELAY, 
(char*) &optval, sizeof(int));	}
		 if(strcasecmp(u,"disable")==0)
		{	optval==0;
			setsockopt(socket_desc, IPPROTO_TCP, 
TCP_NODELAY, (char *) &optval, sizeof(int));
		}
	}else if(strcasecmp(j,"getbroadcast")==0)
	{	oplen=sizeof(opval);
		getsockopt(socket_desc, SOL_SOCKET, SO_BROADCAST, (char *) &opval, &oplen);
		if(opval==0)
			strcpy(c_message,"broadcast is disabled");
		else
			strcpy(c_message,"broadcast is enabled");
	}else if(strcasecmp(j,"setbroadcast")==0)
	{
		strcpy(c_message,"enable or disable broadcast");
		send(c_sock,c_message,200,0);
		recv(c_sock,c_message,200,0);
		char ch[400];
		strcpy(ch,c_message);
		if(strcasecmp(ch,"enable")==0)
		{	optval=1;
			setsockopt(socket_desc, SOL_SOCKET, 
SO_BROADCAST, (char *) &optval, sizeof(int));
		}if(strcasecmp(ch,"disable")==0)
		{	optval=0;
			setsockopt(socket_desc, SOL_SOCKET, 
SO_BROADCAST, (char *) &optval, sizeof(int));
		}
	}else if(strcasecmp(j,"getalive")==0)
	{	olen=sizeof(opval);
		cp=getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, 
(char *)&opval, &olen);	
		if(opval==0)
			strcpy(c_message,"KEEPALIVE : Disabled ");
		else
			strcpy(c_message, "KEEPALIVE : Enabled ");
	}else if(strcasecmp(j, "setalive")==0)
	{	strcpy(c_message, "enable or disable keepAlive");
		send(c_sock,c_message,200,0);
		recv(c_sock,c_message,200,0);
		char qw[450];
		strcpy(qw,c_message);
		if(strcasecmp(qw,"enable")==0)	
		{	optval=1;
			setsockopt(socket_desc, SOL_SOCKET, 
SO_KEEPALIVE, (char *) &optval, sizeof(int));
		}
		if(strcasecmp(qw,"disable")==0)
		{	optval=0;
			setsockopt(socket_desc, SOL_SOCKET, 
SO_KEEPALIVE, (char *) &optval, sizeof(int));
		}

	}else if(strcasecmp(j,"getroute")==0)
	{	olen=sizeof(opval);
		cp=getsockopt(socket_desc,SOL_SOCKET, SO_DONTROUTE, 
(char *) &opval, &oplen);
		if(opval==0)
			strcpy(c_message, "Routing Bypass : Disabled");
		else
			strcpy(c_message, "Routing Bypass : Enabled"); 
	}else if(strcasecmp(j,"setroute")==0)
	{	strcpy(c_message,"enable or disable routing ");
		send(c_sock,c_message,200,0);
		recv(c_sock,c_message,200,0);
		char rt[250];
		strcpy(rt,c_message);
		if(strcasecmp(rt,"enable")==0)
		{	optval=1;
			setsockopt(socket_desc, SOL_SOCKET, 
SO_DONTROUTE, (char *) &optval, sizeof(int));
		}if(strcasecmp(rt,"disable")==0)
		{	optval=0;
			setsockopt(socket_desc, SOL_SOCKET,SO_DONTROUTE, 
(char *) &optval, sizeof(int));
		}

		
	}else if(strcasecmp(j,"exit")==0)
		{ break; }
		
		
	else{	
		strcpy(c_message,"wrong input");	}
		
	send(c_sock,c_message,200,0);
			
		
	}
	printf("--Client Disconnected--\n");	

	return 0;

}
