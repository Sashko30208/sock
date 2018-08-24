/* Creating a simple UDP server with main functions*/
#include <stdio.h>
#include <string.h> //memset()
#include <stdlib.h>  //exit()
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <unistd.h>//close()

#define BUFLEN 512 //max Buffer length
#define port 8888
#define REPLY " Is_Reply\n"

void die (char *s)
{
perror(s);
exit(1);
}

int main()
{
struct sockaddr_in si_me, si_others;
int s, i, slen = sizeof(si_me), recv_len;
char buf[BUFLEN];
char *str;
//creating of socket
if((s=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))== -1)
{
	die("socket");
}

memset((char *) &si_me, 0, sizeof(si_me));//makes sizeof()counts bytes is zero

si_me.sin_family = AF_INET;
si_me.sin_port = htons(port);
si_me.sin_addr.s_addr = htonl(INADDR_ANY);

//bind socket to port
if( bind(s, (struct sockaddr*)&si_me,sizeof(si_me))== -1)
{
	die("bind");
}

//keep listening
while(1)
{
memset((char *)&buf, 0, BUFLEN);
printf("Waiting for data..");
fflush(stdout);


//trying to receive some data
if((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*) &si_others, &slen)) == -1)
//<read datagram
{
	die("recvfrom()");
}

printf("Received packet from %s: %d\n", inet_ntoa(si_others.sin_addr), ntohs(si_others.sin_port));
// ntoa = ip net format to string | ntohs = netshort to uint16
printf("Data: %s\n", buf);

printf("BUFLEN %d; len buf %d\n",BUFLEN, strlen(buf));

*str = malloc(sizeof(char)*(strlen(buf)+strlen(REPLY)+1));
//+1 because strlen() can't see the "\n" symbol

if (sizeof(str)<BUFLEN)
{
//strcpy(buf,buf+REPLY);
//*(&buf+strlen(buf))=REPLY;
sprintf((buf+(strlen(buf)-1)*sizeof(char)),REPLY);
//sprintf(*(&buf), "%s%s\n",buf, REPLY);
printf("%d\n",strlen(buf));
}

if (sendto(s, buf, strlen(buf), 0, (struct sockaddr*) &si_others,slen) == -1)
{
	die("sendto()");
}
//free(str);
}
close(s);
return 0;
}
