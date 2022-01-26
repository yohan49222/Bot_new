#include "main.h"

extern Config *myconfig;

static char *me = "ProxiServ";

Proxi_List *pProxy = NULL;
pthread_t Threads_proxy = 0;
#define PROXYSERVER "irc1.ax-proxima.net"
#define PROXYPORT 6667

/**
	initalisation du service
**/
void init_proxy()
{
	/**
		verifie que ce clone n'est pas dejas charg�
	**/
	if(get_clone(me))
		return;

	/**
		creation du clone
	**/
	new_clone(me,myconfig->flags,myconfig->real,NULL);

	
	/**
		creation des commandes
	**/
	Create_Com("help" , me, &antiproxy_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est sp�cifi� , affiche le detail de cette commande");

	Create_Com("add" , me, &antiproxy_add ,"o","/msg %s ADD <pseudo>" ,"Permet d'ajouter l'ip du pseudo dans la liste des ips bannis , kill tous les users ayant la meme ip");

	/**
		chargement de la liste des proxy banni
	**/
	load_db_proxy();

	/**
		creation des raws
	**/
	Create_Raw_Bot("CONNECT"  	,&ANTIPROXY_CONNECT	,me);
	Create_Raw_Bot("PRIVMSG"  	,&ANTIPROXY_PRIVMSG	,me);
	Create_Raw_Bot("KILL"  		,&ANTIPROXY_KILL	,me);
	Create_Raw_Bot("KICK"  		,&ANTIPROXY_KICK	,me);
}

/**
	liberation memoire de tout ce qui ne sert plus et quit du bot
**/
void unload_proxy()
{
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}

/**
	Raw proxy
**/
void ANTIPROXY_CONNECT(message_irc *message)
{
	User *use = get_user(message->RAW[1]);
	if(!use)
		return;

	if(use->option & IS_PROTECT)
		return;

	fsend_service(me,FORMAT_CONNECTPROXY, use->nick,use->nick,use->handle,use->host,use->ip);

	if(!strncmp(use->host,"192.168",7))
		return;

	/**
		verifie si l'ip est dans la liste des ips banni !! si oui kill de l'user
	**/
	if(get_proxy_ban(use->ip))
	{
		fsend_service(me,FORMAT_PROXYOK,use->ip,"IP BANNI");
		fsend_service(me,"\0034SVSKILL\0031 : %s kill %s pour : %s", me,use->nick,"Pas de proxy autorise sur ce serveur");
		fsend_com(COM_SERV_SVSKILL,myconfig->host,use->nick,"Pas de proxy autorise sur ce serveur");
		del_user(use->nick,"Pas de proxy autorise sur ce serveur");
	
	}
	else
	{
		/**
			vefir si l'ip n'est pas dejas en cours de scan
		**/
		fsend_service(me,FORMAT_NOBLACK,use->ip);	
		creat_thread_proxy(use);
	}
}

void ANTIPROXY_PRIVMSG(message_irc *message)
{
	if(strcasecmp(message->RAW[2],me))
		return;

	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	executeCom( use, message , me);
}

void ANTIPROXY_KILL(message_irc *message)
{
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
	}
}

void ANTIPROXY_KICK(message_irc *message)
{
	if(!strcasecmp(message->RAW[3],me))
		bot_join(me, message->RAW[2] , "+v");
}

/**
	commande proxy
**/
void antiproxy_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void antiproxy_add(User *use , message_irc *message)
{
	User *target;
	char txt[MAXLEN];
	char *ip;
	extern User *Alluser;
	User *usebis = Alluser;

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	target = get_user(message->ARG[1]);
	if(!target)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	if(target->option & IS_PROTECT)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_PROTECT);
		return;
	}

	STRDUP(ip,target->ip)

	while(usebis)
	{
		if(!strcmp(usebis->ip,ip))
		{

			fsend_service(me,FORMAT_KILL,me,usebis->nick,"Proxy interdit sur ce serveur");
			sprintf(txt,"[%s] Local kill by %s (Proxy interdit sur ce serveur)",myconfig->host,me);
			fsend_com(COM_SERV_SVSKILL,myconfig->host,usebis->nick,txt,myconfig->host,me);
			del_user(usebis->nick,"Spam interdit sur ce serveur");
			usebis = Alluser;
			continue;
		}
		usebis = usebis->suivant;
	}
	new_proxy_ban(ip);
	save_db_proxy();
	FREE(ip);
}

/**
	Gestion des proxy dejas scanne
**/
void load_db_proxy()
{
	
	char ligne[20];
	char *p = '\0';
	int i = 0;
	FILE *myFile = fopen("base/proxy2.db", "r");
	if(!myFile)
		return;

	while(fgets(ligne, sizeof ligne, myFile))
	{
		if( strlen(ligne) > 1 )
		{
			p = strchr(ligne, '\n');
			if (p)
				*p = '\0';

			p = strchr(ligne, '\r');
			if (p)
				*p = '\0';

			if( (*ligne != 0) && (strlen(ligne) > 1) )
			{
				new_proxy_ban(ligne);
				i++;
			}
		}
	}
	fclose(myFile);
	fsend_service(me,CHAR_BD_OK,"Proxy");
	fsend_service(me,"\0034INFO\0031 : %d proxy(s) blacklist\xe9(s)",i);
}

void save_db_proxy()
{
	
	Proxi_List *proxy = pProxy;
	FILE *myFile= fopen("base/proxy2.db", "w");
	if(!myFile)
		return;

	while(proxy)
	{
		if(proxy->ip && *proxy->ip)
		{
			fprintf(myFile,"%s\n",proxy->ip);
		}
		proxy = proxy->suivant;
	}

	fclose(myFile);
	fsend_service(me,SAVE_BD_OK,"Proxy");
	
}

Proxi_List *new_proxy_ban(char *ip)
{
	Proxi_List *proxy;

	if(get_proxy_ban(ip))
		return NULL;

	proxy = (Proxi_List*)malloc(sizeof(Proxi_List));
	if(!proxy)
		return NULL;

	if(!ip || !*ip)
	{
		FREE(proxy);
		return NULL;
	}

	STRDUP(proxy->ip , ip);

	proxy->precedent = NULL;
	proxy->suivant = pProxy;
	if (pProxy)
    	pProxy->precedent = proxy;
	pProxy = proxy;
	return pProxy;
}

void liste_proxy_ban(char *nick)
{
	char buf[200];
	Proxi_List *proxy = pProxy;
	while(proxy)
	{
		sprintf(buf,FORMAT_PROXYLI,proxy->ip);
		fsend_com(LINK_COM_USER_NOTICE,me,nick,buf);
		proxy = proxy->suivant;
	}
}

int del_proxy_ban(char *ip)
{
	Proxi_List *proxy = pProxy;
	while (proxy)
	{
		if(!strcmp(proxy->ip,ip))
		{
			if(proxy->suivant)
				proxy->suivant->precedent = proxy->precedent;

			if(proxy->precedent)
				proxy->precedent->suivant = proxy->suivant;

			if(proxy == pProxy)
				pProxy = proxy->suivant;

			FREE(proxy->ip);
			FREE(proxy);

			return 1;
		}
		proxy = proxy->suivant;
	}
	return 0;
}

int get_proxy_ban(char *ip)
{
	Proxi_List *proxy = pProxy;
	while (proxy)
	{
		if(!strcmp(proxy->ip,ip))
			return 1;

		proxy = proxy->suivant;
	}
	return 0;
}


int clear_proxy_ban()
{
	Proxi_List *proxy;
	while (pProxy)
	{
		proxy = pProxy;
		pProxy = pProxy->suivant;
		FREE(proxy->ip);
		FREE(proxy);
		proxy = NULL;
	}
	pProxy = NULL;
	return 1;
}

/**
	fonction socket
**/

char *resol_host(char *host)
{
	struct hostent *serverHostEnt;
	struct in_addr addr;
	long hostAddr;

	hostAddr = inet_addr(host);
	if ( (long)hostAddr != (long)-1)
	{
		memcpy(&addr, &hostAddr, sizeof(hostAddr));
	}
	else
	{
		serverHostEnt = gethostbyname(host);
		if(!serverHostEnt)
		{
			serverHostEnt = gethostbyname(myconfig->server);
		}
			
		memcpy(&addr, serverHostEnt->h_addr, serverHostEnt->h_length);
	}
		
	return inet_ntoa(addr);
}

unsigned int aton(char *ipaddr)
{
	int i;
	long lv;
	char *endptr;
	signed int res;
	unsigned char *bytes = (unsigned char *) &res;

	for (i = 0; i < 4; i++)
	{
		if (!*ipaddr)
			return INADDR_NONE;

		lv = strtol(ipaddr, &endptr, 10);

        	if (lv < 0 || lv > 255 || (*endptr != 0 && *endptr != '.'))
            		return INADDR_NONE;

		bytes[i] = (unsigned char) lv;
		ipaddr = (!*endptr ? endptr : ++endptr);
	}

	if (*endptr)
		return INADDR_NONE;

	return res;
}

int Sock_SetBlockMode (int sock, int blocking)
{
	int flags;
	int r;
	
	flags = fcntl (sock, F_GETFL);
	
	if (blocking == 1)
		r = fcntl (sock, F_SETFL, flags & ~O_NONBLOCK);	
	else
		r = fcntl (sock, F_SETFL, flags | O_NONBLOCK);	
	return r;
}

SOCKET new_socket(char *iphost,int port)
{
	struct hostent *serverHostEnt;
	struct sockaddr_in serverSockAddr;
	long hostAddr;
	SOCKET s = -1;

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
		return 0;

	memset(&serverSockAddr, 0, sizeof(struct sockaddr_in));

	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	hostAddr = inet_addr(iphost);
	if ( (long)hostAddr != (long)-1)
		memcpy(&serverSockAddr.sin_addr, &hostAddr, sizeof(hostAddr));
	else
	{
		serverHostEnt = gethostbyname(iphost);
		if(!serverHostEnt)
			return 0;

		memcpy(&serverSockAddr.sin_addr, serverHostEnt->h_addr, serverHostEnt->h_length);
	}

	setsockopt(s, SOL_SOCKET, SO_LINGER, 0, 0);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, 0, 0);
	setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, 0, 0);

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons(port);

	Sock_SetBlockMode(s,0);

	connect(s,(struct sockaddr *)&serverSockAddr,sizeof(struct sockaddr_in)) ;

	return s ;
}

int proxy_read(SOCKET s, char *buf, size_t buflen)
{
	fd_set fds;
	struct timeval tv;

	FD_ZERO(&fds);
	FD_SET(s, &fds);

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	if(select(s+1, &fds, NULL, NULL, &tv) == 0)
	        return 0;
	else
	{
		if(FD_ISSET(s, &fds))
		{
			return recv(s, buf, buflen, 0);
		}
	}
	return 0;
}

/**
	Analyse de l'ip
**/
void creat_thread_proxy(User *use)
{
	int result = 0;
	result = pthread_create(&Threads_proxy, NULL, (void *(*)())mainproxy,use);
	result = pthread_detach(Threads_proxy);
}

void kill_pthread(User *use)
{
	if(!pthread_cancel(use->Threads_pid))
	{
		fsend_service(me,"\0034THREAD\0031 :pthread %d d\xe9truit , ip scan %s",use->Threads_pid,use->ip);
	}
}
void mainproxy(User *use)
{
	char buf[200];
	char txt[MAXLEN];
	int reponse = 0;

	use->Threads_pid = pthread_self();
	fsend_service(me,"\0034THREAD\0031 :pthread cree avec ppid %d , ip scan %s",use->Threads_pid,use->ip);

	reponse = proxy_scan(use->ip);

	if(!use || !use->ip) /** l'user a peut-etre quitte durant le scan **/
		return;

	switch(reponse)
	{
		case 0:
			fsend_service(me,FORMAT_PROXYNO,use->ip);
			use->Threads_pid = 0;
			return;

		case 1:
			sprintf(buf,"%s","SOCKS 4/5 PROXY");
			break;

		case 2:
			sprintf(buf,"%s","HTTP PROXY");
			break;

		case 3:
			sprintf(buf,"%s","WINGATE PROXY");
			break;

		case 4:
			sprintf(buf,"%s","SECURE PROXY , pas de kill");
			fsend_service(me,FORMAT_PROXYOK,use->ip,buf);
			use->Threads_pid = 0;
			return;

	}

	fsend_service(me,FORMAT_PROXYOK,use->ip,buf);

	new_proxy_ban(use->ip);
	save_db_proxy();

	fsend_service(me,FORMAT_KILL,me,use->nick,"Proxy interdit sur ce serveur");
	sprintf(txt,"[%s] Local kill by %s (Proxy interdit sur ce serveur)",myconfig->host,me);
	fsend_com(COM_SERV_SVSKILL,myconfig->host,use->nick,txt,myconfig->host,me);
	del_user(use->nick,"Spam interdit sur ce serveur");
}

int proxy_scan(char *ip)
{
	if(scan_proxy_socks(ip) == ANTI_SOCK_45)		/** sock 4 / 5 **/
		return ANTI_SOCK_45;

	if(scan_proxy_wingate(ip) == ANTI_SOCK_WINGATE)		/** sock wingate **/
		return ANTI_SOCK_WINGATE;

	if(scan_proxy_http(ip) == ANTI_SOCK_HTTP)		/** sock http 1.0 et 1.1 **/
		return ANTI_SOCK_HTTP;

	return SOCK_CLEAN;
}

int scan_proxy_socks(char *ip)
{
	SOCKET s = 0;
	int i;
   	signed int sip = aton(PROXYSERVER);

	sip = htonl(sip);
	
	for(i = 0; i < 2 ; i++)
	{
		s = 0;
		s = new_socket(ip, 1080);
		if(s)
		{
			/* SOCKS 4 */
			if (i == 0)
			{
				char buf[9];

				buf[0] = 4;
				buf[1] = 1;
				buf[2] = (((unsigned short) 6667) >> 8) & 0xFF;
				buf[3] = (((unsigned short) 6667) & 0xFF);
				buf[4] = (sip >> 24) & 0xFF;
				buf[5] = (sip >> 16) & 0xFF;
				buf[6] = (sip >> 8) & 0xFF;
				buf[7] = sip & 0xFF;

				send(s, buf, 8, 0);
				memset(buf, 0, sizeof(buf));

				if (proxy_read(s, buf, 2) != 2)
				{
					close(s);
					continue;
				}
				if (strlen(buf) != 2)
				{
					close(s);
					continue;
				}

				if (buf[1] == 90)
				{
					close(s);
					return ANTI_SOCK_45;
				}
			}
			if (i == 1)
			{
				/* SOCKS5 */
				char buf[10];
				snprintf(buf, 3, "%c%c%c", 5, 1, 0);
				send(s, buf, 3, 0);

				memset(buf, 0, sizeof(buf));

				if (proxy_read(s, buf, 2) != 2)
				{
					close(s);
					continue;
				}
				if (buf[0] != 5 || buf[1] != 0)
				{
					close(s);
					continue;
				}

				memset(buf, 0, sizeof(buf));

				buf[0] = 5;
				buf[1] = 1;
				buf[2] = 0;
				buf[3] = 1;
				buf[4] = (sip >> 24) & 0xFF;
				buf[5] = (sip >> 16) & 0xFF;
				buf[6] = (sip >> 8) & 0xFF;
				buf[7] = sip & 0xFF;
				buf[8] = (((unsigned short) 6667) >> 8) & 0xFF;
				buf[9] = ((unsigned short) 6667) & 0xFF;

				if (send(s, buf, 10, 0) != 10)
				{
					close(s);
					continue;
				}

				memset(buf, 0, sizeof(buf));

				if (proxy_read(s, buf, 2) != 2)
				{
					close(s);
					continue;
				}

				if (buf[0] == 5 && buf[1] == 0)
				{
					close(s);
					return ANTI_SOCK_45;
				}
			}
			close(s);
		}
	}
	return SOCK_CLEAN;
}

int scan_proxy_wingate(char *ip)
{
	char buf[128];
	int read = 0;
	SOCKET s = -1;

	s = new_socket(ip,23);
	if(s)
	{
		snprintf(buf, sizeof(buf), "%s:%d\r\n", PROXYSERVER, PROXYPORT);
		send(s, buf, (int)strlen(buf), 0);

		memset(buf, 0, sizeof(buf));

		read = proxy_read(s, buf, sizeof(buf));
		if(read)
		{
			buf[8] = '\0';
			if(!strcasecmp(buf, "Wingate>") || !strcasecmp(buf, "Too many"))
			{
				close(s);
				return ANTI_SOCK_WINGATE;
			}
		}
        	close(s);
	}
	return SOCK_CLEAN;
}


int scan_proxy_http(char *ip)
{

	int i;
	int port[5] = { 80, 8080 , 3128 , 8001 , 8002 };
	char buf[128];
	int read = 0;
	SOCKET s = -1;

	/* Scan for HTTP proxy */
	for (i = 0; i < 5; i++)
	{
		if((s = new_socket(ip,port[i])) != 0)
		{
			memset(buf, 0, sizeof(buf));

			snprintf(buf, sizeof(buf), "CONNECT %s:%d HTTP/1.0\r\n\r\n",PROXYSERVER, PROXYPORT);
			if (send(s, buf, strlen(buf), 0) == (int)strlen(buf))
			{
				memset(buf, 0, sizeof(buf));
				read = 0;

				if ((read = proxy_read(s, buf, sizeof(buf))))
				{
					if (!strncasecmp(buf, "HTTP/1.0 200", 12) || !strncasecmp(buf, "HTTP/1.1 200 Co",15))
					{
						close(s);
						return ANTI_SOCK_HTTP;
					}
					if(!strncasecmp(buf, "HTTP/1.1 407 Proxy",18))
					{
						close(s);
						return SECURE_PROXY;
					}
				}
			}
			memset(buf, 0, sizeof(buf));

			snprintf(buf, sizeof(buf), "POST http://%s:%d/ HTTP/1.0\r\nContent-type: text/plain\r\nContent-length: 5\r\n\r\nquit\r\n\r\n",PROXYSERVER, PROXYPORT);

			if (send(s, buf, strlen(buf), 0) == (int)strlen(buf))
			{
				memset(buf, 0, sizeof(buf));
				read = 0;

				if ((read = proxy_read(s, buf, sizeof(buf))))
				{
					if (!strncasecmp(buf, "HTTP/1.0 200", 12) || !strncasecmp(buf, "HTTP/1.1 200 Co",15))
					{
						close(s);
						return ANTI_SOCK_HTTP;
					}
					if(!strncasecmp(buf, "HTTP/1.1 407 Proxy",18))
					{
						close(s);
						return SECURE_PROXY;
					}
				}
			}
			close(s);
		}
		close(s);
	}
	return SOCK_CLEAN;
}


