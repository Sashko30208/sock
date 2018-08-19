/*
The simple udp client
*/
#include <stdio.h>
#include <string.h>//it's used for memset
#include <stdlib.h>//exit();
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <unistd.h>//close()

#define SERVER "192.168.1.70"
#define BUFLEN 512 //Max length of buffer
#define PORT 8888

void die(char *s)
{
perror(s);
exit(1);
}

int main()
{
struct sockaddr_in si;
int s, slen=sizeof(si);
char buf[BUFLEN];
char message[BUFLEN];

if((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)//creating of socket
{
	die("socket");
}

memset((char *) &si, 0, sizeof(si));
si.sin_family = AF_INET;
si.sin_port =htons(PORT);

if(inet_aton(SERVER, &si.sin_addr) ==0)
{
	fprintf(stderr, "inet_aton() failed \n");//die()
	exit(1);
}

while(1)
 {
	printf("Enter message: ");
	gets(message);

	if(sendto(s,message, strlen(message), 0, (struct sockaddr*) &si, slen)==-1)
	{
		die("sendto()");
	}

//clear the buffer
	memset(buf, '\0',BUFLEN);
//try to receive some data
	if (recvfrom(s,buf,BUFLEN, 0, (struct sockaddr*) &si, &slen)== -1)
	{
	die("recvfrom()");
	}

	puts(buf);
 }

close(s);
return 0;
}
