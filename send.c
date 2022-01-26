
#include "main.h"
extern Config *myconfig;


void fsend_service(char *botnick,char *format, ... )
{
	va_list arg;
	char buffer[MAXLEN];
	char buffer_send[MAXLEN];
	va_start(arg,format);
	vsprintf(buffer,format,arg);

	sprintf(buffer_send,LINK_COM_USER_PRIVMSG,botnick,myconfig->service,buffer);
printf("SEND :%s\n",buffer_send);
	_send(buffer_send);

}

void fsend_com(char *format, ... )
{
	va_list arg;
	char buffer[MAXLEN];
	va_start(arg,format);
	vsprintf(buffer,format,arg);
	printf("SEND :%s\n",buffer);
	_send(buffer);
}

void send_service(char *botnick,char *buf)
{
	char buffer[MAXLEN];

	sprintf(buffer,LINK_COM_USER_PRIVMSG,botnick,myconfig->service,buf);
printf("SEND :%s\n",buffer);

	_send(buffer);
}

