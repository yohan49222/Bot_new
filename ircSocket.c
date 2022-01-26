#include "main.h"

SOCKET my_socket = -1;	/* socket principale */

extern Config *myconfig;

int connect_serveur()
{
	struct sockaddr_in serverSockAddr;
	struct hostent *serverHostEnt;
	long hostAddr;

#ifdef WIN32
	WSADATA wsaData;
	int wsaret = WSAStartup(0x101,&wsaData);
#endif

	/*  Verif Complement d'host */
	if(!myconfig)
	{
		put_log("Erreur myconfig , fonction connect_serveur");
		return 0;
	}


	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	hostAddr = inet_addr(myconfig->server);

	if ( (long)hostAddr != (long)-1)
		memcpy(&serverSockAddr.sin_addr, &hostAddr, sizeof(hostAddr));
	else
	{
		serverHostEnt = gethostbyname(myconfig->server);
		memcpy(&serverSockAddr.sin_addr, serverHostEnt->h_addr, serverHostEnt->h_length);
	}

#ifdef WIN32
	serverSockAddr.sin_port = htons((short)myconfig->port);
#else
	serverSockAddr.sin_port = htons(myconfig->port);
#endif

	serverSockAddr.sin_family = AF_INET;

	/* creation de la socket principale */
	my_socket = socket(AF_INET,SOCK_STREAM,0);

	setsockopt(my_socket,SOL_SOCKET,SO_LINGER,0,0);
	setsockopt(my_socket,SOL_SOCKET,SO_REUSEADDR,0,0);
	setsockopt(my_socket,SOL_SOCKET,SO_KEEPALIVE,0,0);

	/* requete de connexion */
	if(connect(my_socket,(struct sockaddr *)&serverSockAddr,sizeof(serverSockAddr)))
		return 0;

	return 1;
}

void pool_one()
{
	//fsend_com("PROTOCTL NICKv2 SJOIN2 UMODE2 NOQUIT VL TKLEXT VHP");
	fsend_com(COM_SERV_PASS,myconfig->serverpass);
	fsend_com(COM_SERV_SERVER,myconfig->host,myconfig->host);
	fsend_com(COM_SERV_EOS,myconfig->host);
	sleep(2);
	init_principale();

	if(myconfig->use_nickserv) init_nickserv();
	if(myconfig->use_operserv) init_operserv();	
	if(myconfig->use_protect) init_protectserv();
	if(myconfig->use_radio) init_radio();
	if(myconfig->use_antispam) init_spam();
	if(myconfig->use_coleen) init_coleen();
	if(myconfig->use_global) init_global();
	if(myconfig->use_masstoolz) init_masstoolz();
	if(myconfig->use_antiproxy) init_proxy();
	if(myconfig->use_jeux) init_jeux();



	pool_two();
}

void pool_two()
{
	my_sock_recv_line();
	pool_tree();
}

void pool_tree()
{
	execute_timer();
	execute_timer_at_time();
	pool_two();
}

void sock_deconnect()
{
	shutdown(my_socket,2);
	close(my_socket);

	sleep(10);
	connect_serveur();
}



int my_sock_recv_line()
{
	int pos = 0;
	char c;
	int buf_len;
	char *buf_str;
	fd_set rfds;
	struct timeval tv;
	int retval;
	FD_ZERO(&rfds);
	FD_SET(my_socket, &rfds);

	tv.tv_sec = 1;
	tv.tv_usec = 0;

	retval = select(my_socket+1,&rfds, NULL, NULL, &tv);
	if(!retval)
		return 0;

	buf_str = (char *)malloc(100 * sizeof(char));
	if(!buf_str)
		return 0;

	buf_len = 100;
	c = '\0';

	while(c != '\n')
	{
		recv(my_socket,&c,sizeof(char),0);

		if(c!='\r')
		{
			buf_str[pos] = c;
			pos++;
			if(pos == buf_len)
			{
				buf_len += 100;
				buf_str = (char *)realloc(buf_str,buf_len * sizeof(char));
			}
		}
	}
	buf_str[pos] = '\0';

	if(*buf_str)
		printf("%s\n",buf_str);

	put_log(buf_str);
	traitement(buf_str);
	FREE(buf_str);
	return 0;
}


int _send(char *s)
{
	char txt[MAXLEN];
	sprintf(txt,"%s\r\n",s);

	put_log(s);
	send(my_socket,txt,(int)strlen(txt),0);
	return 1;
}



