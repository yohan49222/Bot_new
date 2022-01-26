#include "main.h"

extern Config *myconfig;

static char *me = "OperServ";


void init_operserv()
{
	if(get_clone(me))
		return;

	new_clone(me,myconfig->flags,myconfig->real,NULL);

	Create_Raw_Bot("PRIVMSG"  	,&OPERSERV_PRIVMSG	,me);
	Create_Raw_Bot("CONNECT"  	,&OPERSERV_CONNECT	,me);
	Create_Raw_Bot("QUIT"  		,&OPERSERV_QUIT		,me);
	Create_Raw_Bot("MODE"  		,&OPERSERV_MODE		,me);
	Create_Raw_Bot("JOIN"  		,&OPERSERV_JOIN		,me);
	Create_Raw_Bot("PART"  		,&OPERSERV_PART		,me);
	Create_Raw_Bot("NICK"  		,&OPERSERV_NICK		,me);
	Create_Raw_Bot("KICK"  		,&OPERSERV_KICK		,me);
	Create_Raw_Bot("KILL"  		,&OPERSERV_KILL		,me);
	Create_Raw_Bot("SETHOST"  	,&OPERSERV_SETHOST	,me);
	Create_Raw_Bot("CHGHOST"	,&OPERSERV_CHGHOST	,me);
	Create_Raw_Bot("CHGIDENT"	,&OPERSERV_CHGIDENT	,me);
	Create_Raw_Bot("SETIDENT"	,&OPERSERV_SETIDENT	,me);
	Create_Raw_Bot("SETNAME"	,&OPERSERV_SETNAME	,me);
	Create_Raw_Bot("CHGNAME"	,&OPERSERV_CHGNAME	,me);
	Create_Raw_Bot("AWAY"		,&OPERSERV_AWAY		,me);
	Create_Raw_Bot("TOPIC"		,&OPERSERV_TOPIC	,me);
	Create_Raw_Bot("TKL"		,&OPERSERV_TKL		,me);

	Create_Com("help" , me, &operserv_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");
	Create_Com("kill" , me, &operserv_kill ,"o","/msg %s KILL <pseudo> [<motif>]","Force la déconnection de l'usé");
	Create_Com("gline" , me, &operserv_gline ,"o","/msg %s GLINE <pseudo> [<motif>]","Pose un gline sur le host de l'usé");
	Create_Com("ungline" , me, &operserv_ungline ,"o","/msg %s UNGLINE <mask>","Leve le gline posé sur le mask");
	Create_Com("svspart" , me, &operserv_svspart ,"o","/msg %s SVSPART <pseudo> <channel> [<channel> ...]","Force le depart de l'usé sur les channels specifié");
	Create_Com("svsjoin" , me, &operserv_svsjoin ,"o","/msg %s SVSJOIN <pseudo> <channel> [<channel> ...]","Force l'usé a rejoindre les channels spécifié");
	Create_Com("svsnick" , me, &operserv_svsnick ,"o","/msg %s SVSNICK <pseudo> <newpseudo>","Forme le changement de pseudo de l'usé");
	Create_Com("svsmode" , me, &operserv_svsmode ,"o","/msg %s SVSMODE <speudo> +|-<mode>","Applique des Flags Temporairement a l'usé");
	Create_Com("jupe" , me, &operserv_jupe ,"NAC","/msg %s JUPE <server>","Déconnect le link du server");
}

void unload_operserv()
{
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}

int maxclone(User *tmp)
{
	extern User *Alluser;

	User *tmp2;

	int clone = 0;

	tmp2 = Alluser;
	while(tmp2)
	{
		if(!strcmp(tmp->host,tmp2->host))
			clone++;

		tmp2 = tmp2->suivant;
	}
	return clone;
}

char *listclone(User *tmp)
{
	extern User *Alluser;

	User *tmp2;

	char txt[MAXLEN];
	int clone = 0;

	tmp2 = Alluser;
	while(tmp2)
	{
		if(!strcmp(tmp->host,tmp2->host))
		{
			if(!clone)
				sprintf(txt,"%s",tmp2->nick);
			else
				sprintf(txt,"%s - %s",txt,tmp2->nick);
			clone++;
		}
		tmp2 = tmp2->suivant;
	}
	return strdup(txt);
}

/**
	Raw operserv 
**/

void OPERSERV_PRIVMSG(message_irc *message)
{

	printf("OPERSERV_PRIVMSG\n");

	if(strcasecmp(message->RAW[2],me))
		return;

	User *use = get_user(message->RAW[0]);
	if(!use)
		return;


	executeCom( use, message , me);
}

void OPERSERV_CONNECT(message_irc *message)
{
	printf("OPERSERV_CONNECT\n");

	User *use = get_user(message->RAW[1]);
	if(!use)
		return;

	int clone = maxclone(use);


	if(clone > 1)
	{
		char *clonelist = listclone(use);
		fsend_service(me,FORMAT_CONNECT2, use->nick,use->nick,use->handle,use->host,use->server,clonelist);
		FREE(clonelist);
	}
	else
	{
		fsend_service(me,FORMAT_CONNECT, use->nick,use->nick,use->handle,use->host,use->server);
	}

}
void OPERSERV_QUIT(message_irc *message)
{
	fsend_service(me,FORMAT_QUIT, message->RAW[0],message->message);
}

void OPERSERV_MODE(message_irc *message)
{
	printf("OPERSERV_MODE\n");

	char m[30];
	char c = 0,d = 0,ex = 0;
	int i = 0;
	int u = 4;
	char mode_channel[MAXLEN];
	mode_channel[0] = 0;

#ifdef DEBUG_IRC
	printf("nRaw %d\n",message->n_raw);
	printf("nArg %d\n",message->n_arg);
#endif
	if(message->ARG[0])
	{
fsend_service(me,FORMAT_MODE,message->RAW[0],message->ARG[0],message->RAW[2]);
/**
		strcpy(m,message->ARG[0]);
		while((c = m[i++]))
		{
			switch(c)
			{
				case '+':
					action = TRUE;
					d = '+';
					break;
				case '-':
					action = FALSE;
					d = '-';
					break;
				default:
				fsend_service(me,FORMAT_MODECHAN,message->RAW[0],d,c,message->RAW[2]);
					break;
			}
		}
**/
	}
	else
	{
		if(strlen(message->RAW[3]) == 1)
			return;

		strcpy(m,message->RAW[3]);
		while((c = m[i++]))
		{
			switch(c)
			{
				case '+':
					ex = '+';
					d = c;
					break;

				case '-':
					ex = '-';
					d = c;
					break;

				case 'o':
				case 'v':
				case 'q':
				case 'h':
				case 'a':
				case 'b':
					fsend_service(me,FORMAT_MODEUSECHAN,message->RAW[0],d,c,message->RAW[u++],message->RAW[2]);
					break;

				case 'p':
				case 's':
				case 'm':
				case 'n':
				case 't':
				case 'i':
				case 'r':
				case 'R':
				case 'c':
				case 'O':
				case 'A':
				case 'Q':
				case 'K':
				case 'V':
				case 'C':
				case 'u':
				case 'z':
				case 'N':
				case 'S':
				case 'M':
				case 'T':
				case 'G':
					if(strlen(mode_channel))
					{
						sprintf(mode_channel,"%s%c",mode_channel,ex);
						ex = 0;
					}
					else
					{
						sprintf(mode_channel,"%c",ex);
						ex = 0;
					}
					if(strlen(mode_channel))
					{
						sprintf(mode_channel,"%s%c",mode_channel,c);
					}
					else
					{
						sprintf(mode_channel,"%c",c);
					}
					break;
			}
		}
		if(strlen(mode_channel))
		{
			fsend_service(me,FORMAT_MODE,message->RAW[0],mode_channel,message->RAW[2]);
		}
	}
}



void OPERSERV_JOIN(message_irc *message)
{
	fsend_service(me,FORMAT_JOIN, message->RAW[0],message->RAW[2]);
}
void OPERSERV_PART(message_irc *message)
{
	fsend_service(me,FORMAT_PART, message->RAW[0],message->RAW[2]);
}
void OPERSERV_NICK(message_irc *message)
{
	fsend_service(me,FORMAT_NICK, message->RAW[0],message->RAW[2]);
}
void OPERSERV_KICK(message_irc *message)
{
	fsend_service(me,FORMAT_KICK, message->RAW[0],message->RAW[3],message->RAW[2],message->message);

	if(!strcasecmp(message->RAW[3],me))
	{
		bot_join(me, message->RAW[2] , "+v");
	}
}
void OPERSERV_KILL(message_irc *message)
{
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
	}
	else
	{
		fsend_service(me,FORMAT_KILL, message->RAW[0],message->RAW[2],message->message);
	}
}
void OPERSERV_SETHOST(message_irc *message)
{
	fsend_service(me,FORMAT_SETVHOST, message->RAW[0],message->RAW[2]);
}
void OPERSERV_CHGHOST(message_irc *message)
{
	fsend_service(me,FORMAT_CHGVHOST, message->RAW[0],message->RAW[2],message->RAW[3]);
}
void OPERSERV_CHGIDENT(message_irc *message)
{
	fsend_service(me,FORMAT_CHGHAND, message->RAW[0],message->RAW[2],message->RAW[3]);
}
void OPERSERV_SETIDENT(message_irc *message)
{
	fsend_service(me,FORMAT_SETHAND, message->RAW[0],message->RAW[2]);
}
void OPERSERV_SETNAME(message_irc *message)
{
	fsend_service(me,FORMAT_SETREAL, message->RAW[0],message->message);
}
void OPERSERV_CHGNAME(message_irc *message)
{
	fsend_service(me,FORMAT_CHGREAL, message->RAW[0],message->RAW[2],message->RAW[3]);
}
void OPERSERV_AWAY(message_irc *message)
{
	if(message->message && *message->message)
	{
		fsend_service(me,FORMAT_AWAY2,message->RAW[0],message->message);
	}
	else
	{
		fsend_service(me,FORMAT_AWAY1,message->RAW[0]);
	}
}

void OPERSERV_TOPIC(message_irc *message)
{
	if(!strcmp(message->RAW[0],"TOPIC"))
	{
		fsend_service(me,FORMAT_NEWCHAN,message->RAW[1],message->message);
	}
	else
	{
		fsend_service(me,FORMAT_TOPIC,message->RAW[0],message->RAW[2],message->message);
	}
}
//:irc3.ax-proxima.net TKL + G * ALille-151-1-64-59.w83-192.abo.wanadoo.fr //yoyo49!yohan@yoyo49.ax-proxima.net 1178292971 1178292966 :test

void OPERSERV_TKL(message_irc *message)
{
	char *nick_emet;
	STRDUP(nick_emet,message->RAW[6]);
	char *p = strchr(nick_emet,'!');
	if(p)
		*p = '\0';

	char mask[256];
	sprintf(mask,"%s@%s",message->RAW[4],message->RAW[5]);

	if(*message->RAW[2] == '+')
	{
		switch(*message->RAW[3])
		{
			case 'G':
				fsend_service(me,FORMAT_GLINE,nick_emet,mask,message->message);
				break;

			case 's':
				fsend_service(me,FORMAT_SHUN,nick_emet,mask,message->message);
				break;
		}
	}
	else
	{
		switch(*message->RAW[3])
		{
			case 'G':
				fsend_service(me,FORMAT_UNGLINE,nick_emet,mask);
				break;

			case 's':
				fsend_service(me,FORMAT_UNSHUN,nick_emet,mask);
				break;
		}
	}

	FREE(nick_emet);

	if(*message->RAW[2] == '+' && *message->RAW[3] == 'G')
	{
		if(strcmp(message->RAW[7],"0"))
			new_timer_at_time(atol(message->RAW[7]) , del_Tkl , mask);

		new_Tkl(mask);
	}

	if(*message->RAW[2] == '-' && *message->RAW[3] == 'G')
	{
		del_Tkl(mask);
		del_Timer_at_time(mask);
	}
}

/**
	commandes operserv
**/

void operserv_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void operserv_kill(User *use , message_irc *message)
{
	User *target;
	char motif[MAXLEN];
	char txt[MAXLEN];
	int i = 2;

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

	if(!message->ARG[2])
	{
		strcpy(motif,"Vous etes le maillon faible , aurevoir");
	}
	else
	{
		i = 2;

		while(message->ARG[i])
		{
			if(i == 2)
				sprintf(motif,"%s",message->ARG[i]);
			else
				sprintf(motif,"%s %s",motif,message->ARG[i]);

			i++;
		}
	}

	sprintf(motif,"%s par \0034%s",motif,use->nick);
	sprintf(txt,"[%s] Local kill by %s (%s)",myconfig->host,me,motif);

	fsend_service(me,FORMAT_SVSKILL, use->nick,target->nick,motif);
	fsend_com(COM_SERV_SVSKILL,myconfig->host,target->nick,motif);
	del_user(target->nick,motif);
}

void operserv_gline(User *use , message_irc *message)
{
	User *target;
	char motif[MAXLEN];
	int i = 2;
	long t = time(NULL);
	long expire = t + 86400;
	char *date_fr = time_fr(expire);

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

	if(!message->ARG[2])
	{
		strcpy(motif,"Vous etes le maillon faible , aurevoir");
	}
	else
	{
		i = 2;

		while(message->ARG[i])
		{
			if(i == 2)
				sprintf(motif,"%s",message->ARG[i]);
			else
				sprintf(motif,"%s %s",motif,message->ARG[i]);

			i++;
		}
	}
	/** finalise le motif a le pseudo de l'emeteur **/
	sprintf(motif,"%s par %s",motif,use->nick);

	fsend_com(LINK_TKL,myconfig->host,target->host,me,expire,t,motif,date_fr);
	fsend_service(me,FORMAT_GLINE,use->nick,target->host,motif);
	del_user(target->nick,motif);

	FREE(date_fr);
}

void operserv_ungline(User *use , message_irc *message)
{
	char *hand;
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	STRDUP(hand,message->ARG[1]);
	char *p  = strchr(hand,'@');
	if(p)
		*p = '\0';

	char *host = strchr(message->ARG[1],'@');
	host++;

	fsend_com(LINK_UNTKL,myconfig->host,hand,host,me);
	fsend_service(me,FORMAT_UNGLINE,use->nick,message->ARG[1]);

	FREE(hand);
}



void operserv_svsjoin(User *use , message_irc *message)
{
	User *use2;

	char channelp[MAXLEN];
	int i = 2;

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	use2 = get_user(message->ARG[1]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	memset(channelp,0,MAXLEN);
	while(message->ARG[i])
	{
		if(*channelp)
			sprintf(channelp,"%s,%s",channelp,message->ARG[i++]);
		else
			sprintf(channelp,"%s",message->ARG[i++]);
	}

	fsend_com(LINK_COM_OPER_SAJOIN,myconfig->host,use2->nick,channelp);

	fsend_service(me,FORMAT_SVSJOIN, use->nick,use2->nick,channelp);
}

void operserv_svspart(User *use , message_irc *message)
{
	User *use2;

	char channelp[MAXLEN];
	int i = 2;

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	use2 = get_user(message->ARG[1]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	memset(channelp,0,MAXLEN);
	while(message->ARG[i])
	{
		if(*channelp)
			sprintf(channelp,"%s,%s",channelp,message->ARG[i++]);
		else
			sprintf(channelp,"%s",message->ARG[i++]);
	}

	fsend_com(LINK_COM_OPER_SAPART,myconfig->host,use2->nick,channelp);
	fsend_service(me,FORMAT_SVSPART, use->nick,use2->nick,channelp);
}

void operserv_svsnick(User *use , message_irc *message)
{
	User *use2;

	long t = time(NULL);

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	use2 = get_user(message->ARG[1]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	fsend_com(COM_SERV_SVSNICK,myconfig->host,use2->nick,message->ARG[2],t);
	fsend_service(me,FORMAT_SVSNICK, use->nick,message->ARG[1],message->ARG[2]);
}

void operserv_svsmode(User *use , message_irc *message)
{
	User *use2;
	char m[20];
	char c,d;
	int action = FALSE;
	int i = 0;


	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	use2 = get_user(message->ARG[1]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	strcpy(m,message->ARG[2]);
	c = m[0];
	switch(c)
	{
		case '+':
		case '-':
			break;
		default:
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"HEU->. !! Me demander de changer des modes , je suis pas contre , mais je les + ou - :) ");
			return;
	}

	fsend_com(COM_SERV_SVSMODE,me,use2->nick,message->ARG[2]);
	fsend_service(me,FORMAT_SVSMODE,use->nick,message->ARG[2],message->ARG[1]);

	while((c = m[i++]))
	{
		switch(c)
		{
			case '+': action = TRUE; d = '+'; break;
			case '-': action = FALSE; d = '-'; break;
			default: set_flag(use2,use->nick, c ,action); break;
		}
	}
}

void operserv_jupe(User *use , message_irc *message)
{
	if(message->ARG[1] == NULL)
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	fsend_com(LINK_COM_OPER_SQUIT,me,message->ARG[1]);
	fsend_service(me,FORMAT_SVSJUPE, use->nick,message->ARG[1]);
}

















