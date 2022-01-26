
#include "main.h"

extern Config *myconfig;

static char *me = "Urban-Radio";


#define AGENT "User-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:0.9.9)\r\n"
#define ENDCONNECT "Connection: close\r\n\r\n\r\n"

Radio *myRadio = NULL;

pthread_t my_Threads_radio;
static pthread_mutex_t protect_radio;

/* variable de verification de thread actif */
int x_thread = 0;

void init_radio()
{
	if(get_clone(me))
		return;


	new_clone(me,myconfig->flags,myconfig->real,NULL);
	
	/* Creation et initialisation d'un object Type Radio */
	if(!myRadio)
	{
		myRadio = (Radio*)malloc(sizeof(Radio));

		myRadio->serverradio = NULL;
		myRadio->channelradio = NULL;
		myRadio->urlradiostream = NULL;
		myRadio->urlradiomedia = NULL;
		myRadio->urlradiowinamp = NULL;
		myRadio->songtitle = NULL;
	}

	load_config_radio("bot.conf");

	/* raw privmsg */
	Create_Raw_Bot("PRIVMSG"  	,&RADIO_PRIVMSG ,me);
	Create_Raw_Bot("KILL"  		,&RADIO_KILL ,me);
	Create_Raw_Bot("KICK"  		,&RADIO_KICK ,me);
	/* commande  radio */
	Create_Com("help" , me, &radio_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est sp�cifi� , affiche le detail de cette commande");
	Create_Com("live" , me, &radio_live ,"?","/msg %s LIVE","Affiche le titre courant diffus�");


	if(USETHREAD)
	{
		creat_threads();
		new_timer(100000,60,&creat_threads,"RADIO","RADIO");
	}

	pub_radio();
	new_timer(100000,1800,&pub_radio,"RADIO","RADIO");

	bot_join(me, myRadio->channelradio , "+v");
}

void unload_radio()
{
	if(myRadio->serverradio) FREE(myRadio->serverradio);
	if(myRadio->channelradio) FREE(myRadio->channelradio);
	if(myRadio->urlradiostream) FREE(myRadio->urlradiostream);
	if(myRadio->urlradiomedia) FREE(myRadio->urlradiomedia);
	if(myRadio->urlradiowinamp) FREE(myRadio->urlradiowinamp);
	if(myRadio->songtitle) FREE(myRadio->songtitle);
	FREE(myRadio);
	myRadio = NULL;
	del_Timer("RADIO","RADIO");
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}

void RADIO_PRIVMSG(message_irc *message)
{
	printf("RADIO_PRIVMSG\n");

	if(strcasecmp(message->RAW[2],me))
		return;


	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	executeCom( use, message , me);
}

void RADIO_KILL(message_irc *message)
{
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
		bot_join(me, myRadio->channelradio , "+v");
	}
}

void RADIO_KICK(message_irc *message)
{
	if(strcasecmp(message->RAW[3],me))
		return;

	bot_join(me, message->RAW[2] , "+v");
}

void load_config_radio(char *Fichier )
{
	FILE *myFile;
	char ligne[256];
	char *var = NULL;
	char *val = NULL;
	char *p;

	if((myFile= fopen(Fichier, "r")) != NULL)
	{
		while(fgets(ligne, sizeof ligne, myFile))
		{
			if( (ligne[0] != '#') && (ligne[0] != '/') && (strlen(ligne) > 1 ))
			{
				p = strchr(ligne, '\n');
				if (p)
				{
					*p = '\0';
				}
				var = strtok(ligne , "\"");
				sscanf(var,"%s",var);
				val = strtok(NULL , "\"");
				
				if(!val)
					continue;

				if(var && val)
				{

					if(!strcmp("SERVERRADIO",var))
					{
						STRDUP(myRadio->serverradio,val);
					}
					if(!strcmp("SERVERRADIOPORT",var))
						myRadio->serverradioport = atoi(val);

					if(!strcmp("CHANNELRADIO",var))
					{
						STRDUP(myRadio->channelradio,val);
					}
					if(!strcmp("URLRADIOSTREAM",var))
					{
						STRDUP(myRadio->urlradiostream,val);
					}
					if(!strcmp("URLRADIOMEDIA",var))
					{
						STRDUP(myRadio->urlradiomedia,val);
					}
					if(!strcmp("URLRADIOWINAMP",var))
					{
						STRDUP(myRadio->urlradiowinamp,val);
					}
				}
			}
		}
		fclose(myFile);
	}
	return;
}



char *creat_url_radiostream(char *url)
{
	char buffer[100];
	sprintf(buffer,"GET %s HTTP/1.0\n",url);
	return strdup(buffer);
}
char *creat_hostsock_radiostream(char *serveur)
{
	char buffer[100];
	sprintf(buffer,"Host: %s \r\n\r\n",serveur);
	return strdup(buffer);
}

void pub_radio()
{
	char send[1024];

	if(myRadio->urlradiomedia)
	{
		sprintf(send,"\0033Pour �couter\0034 Urban-Radio\0033 avec\0034 Media Player \0031,cliquer sur\0034 %s",myRadio->urlradiomedia);
		fsend_com(LINK_COM_USER_PRIVMSG,me,myRadio->channelradio,send);
	}

	if(myRadio->urlradiowinamp)
	{
		sprintf(send,"\0033Pour �couter\0034 Urban-Radio\0033 avec\0034 WinAmp \0031,cliquer sur\0034 %s",myRadio->urlradiowinamp);
		fsend_com(LINK_COM_USER_PRIVMSG,me,myRadio->channelradio,send);
	}
}

void radio_live(User *use ,message_irc *message)
{
	char send[1024];
	printf("%s %s\n",message->RAW[0],message->RAW[0]);
	sprintf(send,"\0033Actuellement sur\0034 Urban-Radio\0032 %s", myRadio->songtitle);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,send);
}

void Remplacer(char *ligne,char *dep, char *arr)
{
    char c1[1024];
	char c2[1024];
	char *tmp1;
	char *tmp2;
	strcpy(c2,"");
	strcpy(c1,ligne);
	tmp1 = c1;
	while(strlen(tmp1))
	{
		tmp2 = strstr(tmp1, dep);
		if (tmp2)
		{
			strncat(c2, tmp1, tmp2 - tmp1);
			strcat(c2, arr);
			tmp1 += ((tmp2 - tmp1) + strlen(dep));
		}
		else
		{
			strcat(c2, tmp1);
			tmp1 += strlen(tmp1);
		}
	}
	strcpy(ligne,c2);
}

void encode(char *phrase)
{
	Remplacer(phrase,"&#xA0;"," ");
	Remplacer(phrase,"&#xA1;","�");
	Remplacer(phrase,"&#xA2;","�");
	Remplacer(phrase,"&#xA3;","�");
	Remplacer(phrase,"&#xA4;","�");
	Remplacer(phrase,"&#xA5;","�");
	Remplacer(phrase,"&#xA6;","�");
	Remplacer(phrase,"&#xA7;","�");
	Remplacer(phrase,"&#xA8;","�");
	Remplacer(phrase,"&#xA9;","�");
	Remplacer(phrase,"&#xAA;","�");
	Remplacer(phrase,"&#xAB;","�");
	Remplacer(phrase,"&#xAC;","�");
	Remplacer(phrase,"&#xAD;","�");
	Remplacer(phrase,"&#xAE;","�");
	Remplacer(phrase,"&#xAF;","�");
	Remplacer(phrase,"&#xB0;","�");
	Remplacer(phrase,"&#xB1;","�");
	Remplacer(phrase,"&#xB2;","�");
	Remplacer(phrase,"&#xB3;","�");
	Remplacer(phrase,"&#xB4;","�");
	Remplacer(phrase,"&#xB5;","�");
	Remplacer(phrase,"&#xB6;","�");
	Remplacer(phrase,"&#xB7;","�");
	Remplacer(phrase,"&#xB8;","�");
	Remplacer(phrase,"&#xB9;","�");
	Remplacer(phrase,"&#xBA;","�");
	Remplacer(phrase,"&#xBB;","�");
	Remplacer(phrase,"&#xBC;","�");
	Remplacer(phrase,"&#xBD;","�");
	Remplacer(phrase,"&#xBE;","�");
	Remplacer(phrase,"&#xBF;","�");
	Remplacer(phrase,"&#xC0;","�");
	Remplacer(phrase,"&#xC1;","�");
	Remplacer(phrase,"&#xC2;","�");
	Remplacer(phrase,"&#xC3;","�");
	Remplacer(phrase,"&#xC4;","�");
	Remplacer(phrase,"&#xC5;","�");
	Remplacer(phrase,"&#xC6;","�");
	Remplacer(phrase,"&#xC7;","�");
	Remplacer(phrase,"&#xC8;","�");
	Remplacer(phrase,"&#xC9;","�");
	Remplacer(phrase,"&#xCA;","�");
	Remplacer(phrase,"&#xCB;","�");
	Remplacer(phrase,"&#xCC;","�");
	Remplacer(phrase,"&#xCD;","�");
	Remplacer(phrase,"&#xCE;","�");
	Remplacer(phrase,"&#xCF;","�");
	Remplacer(phrase,"&#xD0;","�");
	Remplacer(phrase,"&#xD1;","�");
	Remplacer(phrase,"&#xD2;","�");
	Remplacer(phrase,"&#xD3;","�");
	Remplacer(phrase,"&#xD4;","�");
	Remplacer(phrase,"&#xD5;","�");
	Remplacer(phrase,"&#xD6;","�");
	Remplacer(phrase,"&#xD7;","�");
	Remplacer(phrase,"&#xD8;","�");
	Remplacer(phrase,"&#xD9;","�");
	Remplacer(phrase,"&#xDA;","�");
	Remplacer(phrase,"&#xDB;","�");
	Remplacer(phrase,"&#xDC;","�");
	Remplacer(phrase,"&#xDD;","�");
	Remplacer(phrase,"&#xDE;","�");
	Remplacer(phrase,"&#xDF;","�");
	Remplacer(phrase,"&#xE0;","�");
	Remplacer(phrase,"&#xE1;","�");
	Remplacer(phrase,"&#xE2;","�");
	Remplacer(phrase,"&#xE3;","�");
	Remplacer(phrase,"&#xE4;","�");
	Remplacer(phrase,"&#xE5;","�");
	Remplacer(phrase,"&#xE6;","�");
	Remplacer(phrase,"&#xE7;","�");
	Remplacer(phrase,"&#xE8;","�");
	Remplacer(phrase,"&#xE9;","�");
	Remplacer(phrase,"&#xEA;","�");
	Remplacer(phrase,"&#xEB;","�");
	Remplacer(phrase,"&#xEC;","�");
	Remplacer(phrase,"&#xED;","�");
	Remplacer(phrase,"&#xEE;","�");
	Remplacer(phrase,"&#xEF;","�");
	Remplacer(phrase,"&#xF0;","�");
	Remplacer(phrase,"&#xF1;","�");
	Remplacer(phrase,"&#xF2;","�");
	Remplacer(phrase,"&#xF3;","�");
	Remplacer(phrase,"&#xF4;","�");
	Remplacer(phrase,"&#xF5;","�");
	Remplacer(phrase,"&#xF6;","�");
	Remplacer(phrase,"&#xF7;","�");
	Remplacer(phrase,"&#xF8;","�");
	Remplacer(phrase,"&#xF9;","�");
	Remplacer(phrase,"&#xFA;","�");
	Remplacer(phrase,"&#xFB;","�");
	Remplacer(phrase,"&#xFC;","�");
	Remplacer(phrase,"&#xFD;","�");
	Remplacer(phrase,"&#xFE;","�");
	Remplacer(phrase,"&#x26;","+");
	Remplacer(phrase,"&#xFF;"," ");
	Remplacer(phrase,"&#x27;","'");
	Remplacer(phrase,"&#x3C;","<");
	Remplacer(phrase,"&#x3E;",">");
	Remplacer(phrase,"&#x92;","'");
	Remplacer(phrase,"&equiv;","=");
	return ;
}

void creat_threads()
{
	/* verification qu'un thead radio n'est pas dejas en cours de traitement */
	if(x_thread)
		return;
	
	int result = 0;
	pthread_mutex_init (&protect_radio, NULL);
	result = pthread_create(&my_Threads_radio, NULL, get_url,NULL);
	result = pthread_detach(my_Threads_radio);

	if(result)
		x_thread = 1;	/* thread en cours */
}

SOCKET check_connect_radio(char *iphost,int port)
{
	struct hostent *serverHostEnt;
	struct sockaddr_in serverSockAddr;
	long hostAddr;
	SOCKET s = -1;


	if((s = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		close(s);
		return 0;
	}

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

	setsockopt(s,SOL_SOCKET,SO_LINGER,0,0);
	setsockopt(s,SOL_SOCKET,SO_REUSEADDR,0,0);
	setsockopt(s,SOL_SOCKET,SO_KEEPALIVE,0,0);

	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_port = htons((short)port);

	if(connect(s,(struct sockaddr *)&serverSockAddr,sizeof(serverSockAddr)) == SOCKET_ERROR)
	{
		close(s);
		return 0;
	}
	return s;
}


void *get_url()
{
	char c;
	SOCKET radio = -1;
	char *buf_final = NULL;
	int buf_len = 1000;
	int reads = 1;
	int pos = 0;

	radio = check_connect_radio(myRadio->serverradio,myRadio->serverradioport);
	if(radio)
	{
		send(radio,creat_url_radiostream(myRadio->urlradiostream),(int)strlen(creat_url_radiostream(myRadio->urlradiostream)),0);
		send(radio,AGENT,(int)strlen(AGENT),0);
		send(radio,creat_hostsock_radiostream(myRadio->serverradio),(int)strlen(creat_hostsock_radiostream(myRadio->serverradio)),0);

		buf_final = (char *)malloc(buf_len * sizeof(char));

		while(reads >= 0)
		{
			reads = recv(radio,&c,sizeof(c),0);

			buf_final[pos++] = c;
			buf_final[pos] = '\0';

			if(pos == buf_len)
			{
				buf_len += 1000;
				buf_final = (char *)realloc(buf_final,buf_len * sizeof(char));
			}
			if(strstr(buf_final,"Unauthorized") != NULL)
			{
				fsend_service(me,"\0034Pass invalide pour consultaion xml , revoir configuration radio ");

				goto FIN;
			}

			if(strstr(buf_final,"</SONGTITLE>") != NULL)
				break;
		}

		parse_xml(buf_final);

		FREE(buf_final);
		
	}
	else
	{
		fsend_service(me,"\0034Connexion impossible sur %s , port %d",myRadio->serverradio,myRadio->serverradioport);
	}

FIN:
	if(radio)
	{
		shutdown(radio,2);
		close(radio);
	}

#ifdef USETHREAD
	pthread_exit(0);
	x_thread = 0;		/* thread termine */
#endif

	return 0;
}

void parse_xml(char *c)
{
	char *ptr = NULL;
	
#ifdef USETHREAD
	pthread_mutex_lock (&protect_radio);
#endif

	char *ptr_pos = NULL;
	char send[MAXLEN];
	int debut = 0;
	int fin = 0;

	ptr_pos = strstr (c, "<SONGTITLE>");
	if(ptr_pos)
		debut = (ptr_pos - c) + 11;

	ptr_pos = strstr (c, "</SONGTITLE>");
	if(ptr_pos)
		fin = (ptr_pos - c) - 1;

	ptr = str_sub(c, debut, fin);
	encode(ptr);
	if(!myRadio->songtitle)
	{
		STRDUP(myRadio->songtitle,ptr)
	}
	else
	{
		if(strcmp(ptr,myRadio->songtitle))
		{
			FREE(myRadio->songtitle);
			STRDUP(myRadio->songtitle,ptr);
		}
		else
		{
#ifdef USETHREAD

			pthread_mutex_unlock (&protect_radio);
#endif
			return;
		}
	}
	
	FREE(ptr);

#ifdef USETHREAD
	pthread_mutex_unlock (&protect_radio);
#endif
	memset(send,0,MAXLEN);

	sprintf(send,"\0033Actuellement sur\0034 Urban-Radio\0032 %s ",myRadio->songtitle);
	fsend_com(LINK_COM_USER_PRIVMSG,me,myRadio->channelradio,send);
}

char *str_sub (const char *s, unsigned int start, unsigned int end)
{
	char *new_s = NULL;

	if (s && start < end)
	{
/* (1)*/
		new_s = malloc (sizeof (*new_s) * (end - start + 2));
		memset(new_s,0,sizeof (*new_s) * (end - start + 2));
		if (new_s)
		{
			int i;

/* (2) */
			for (i = start; i <= end; i++)
			{
/* (3) */
				new_s[i-start] = s[i];
			}
		}
		else
		{
			fprintf (stderr, "Memoire insuffisante\n");
			return strdup("ERROR");
		}
	}
	return new_s;
}

void radio_help(User *use , message_irc *message)
{
	help(use,message,me);
}
