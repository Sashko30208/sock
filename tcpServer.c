/* Creating a simple UDP server with main functions*/
#include <stdio.h>
#include <string.h> //memset()
#include <stdlib.h>  //exit()
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ctype.h>
#include <unistd.h>//close()

#include <sys/types.h>
#include <netinet/in.h>

#define BUFLEN 512 //max Buffer length
#define PORT 8888
#define REPLY " Is_Reply\n"
#define SA struct sockaddr
typedef struct
{
int oft;
int len;
char data[BUFLEN];
}Mem;

void die (char *s)
{
perror(s);
exit(1);
}

//char mess_serv[] = "\nHello client!";
int main()
{
	/*
	 * listener для хранения fd сокета
	 */
	int fd_s, listening;
	struct sockaddr_in si;
	char buf[BUFLEN];
	int recv_len;
	bzero(&si, sizeof(si));
/*(AF_INET(internet-домен),SOCK_STREAM(для TCP),протокол по умолчанию)*/
	if ((listening = socket(AF_INET, SOCK_STREAM, 0))==-1) //создание сокета
	{
        die("socket()");
    }
	//проверка на создание сокета, если listening -1 то не создался сокет

	
	/*заполнение сткутуры*/
	
	si.sin_family = AF_INET; //семейство адресов
	
	//Host TO Network Short - преобразование числа порядка хоста в сетевой
	si.sin_port = htons(PORT); //номер порта
	
	//Host TO Network Long - реобразование числа порядка хоста в сетевой
	// INADDR_ANY - соединения с клиентами через любой IP
	si.sin_addr.s_addr = htonl(INADDR_ANY); //IP-адрес
	
	//bind - для явного связывание с некоторым адресом
	if(bind(listening, (SA*)&si, sizeof(si)) ==-1)
    	{
		die("bind");
	}
	
	/*очередь запросов на соединение
	 * первый параметр это fd сокета
	 * второй это размер очереди запросов
	 */
	 
	listen(listening, 1);
	while(1) {
		//accept - создает для общение с клиентом новый сокет
		
		if((fd_s = accept(listening, NULL, NULL)) < 0)
        {
			die("accept");
		}
		
		while(1) {
			
			//recv - принимает данные
			;
			if((recv_len = recv(fd_s, buf, BUFLEN, 0)) <= 0) 
            {
                break;
            }

                sprintf(*(&buf), "%s%s\n",buf, REPLY);
                printf("%d\n",strlen(buf));
            //strcat(buf, mess_serv);
			//send для отправки данных 
			if (send(fd_s, buf, strlen(buf), 0)== -1)
            {
                die("sendto()");
            }
		}
		
		close(fd_s);
	}
	return 0;
}
