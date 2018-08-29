/*
The simple udp client
*/
#include <sys/types.h>
#include <netinet/in.h>

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

//	char message[] = "Hello server!";
//	char buf[sizeof(message)];
	
void die(char *s)
{
    perror(s);
    exit(1);
}    

int main()
{
	//int sock_id;
	//struct sockaddr_in addr;
	struct sockaddr_in si;
    int s, slen=sizeof(si);
    char buf[BUFLEN];
    char message[BUFLEN];
		/*(AF_INET(internet-домен),SOCK_STREAM(для TCP))*/	
	//проверка на создание сокета
	if((s= socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		die("socket");
	}
	memset((char *) &si, 0, slen);
	/*заполение структуры*/
	si.sin_family = AF_INET;
	si.sin_port = htons(PORT);
	//si.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(inet_aton(SERVER, &si.sin_addr) ==0)
{
	die("inet_aton() failed \n");//die()	
}
	
	//на стороне клиента connect - для установление соединения
	if(connect(s, (struct sockaddr *)&si, slen < 0)
	{
		die("connect");
	}
    while(1)
    {
        printf("Enter message: ");
	    fgets(message, BUFLEN, stdin);
    
    if(send(s,message, BUFLEN,0)==-1)
    {
        die("send()");
    }
    printf("sended\n");

    memset(buf,'\0',BUFLEN);
    printf("receiving\n");
    if(recv(s, buf, BUFLEN,0)==-1)
    {
        die("recv()");
    }
    puts(buf;)

    }
	//отправка сообщения
	//send(sock_id, message, sizeof(message), 0);
	//принятие сообщения
	//recv(sock_id, buf, 2*sizeof(message), 0);
	//printf("%s	",buf);
	close(sock_id);

	return 0;
}
