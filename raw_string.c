
#include "main.h"
extern Config *myconfig;

void p_MSG_CONNECT(  message_irc *message  )            /* CONNECT */
{
	/*
	NICK yoyo49 1 1156183648 yohan 192.168.1.20 yoyo49.ax-proxima.net 0 :yohan
	*/
	/* new_user(char *nick,char *handle,char *host,char *real,long Ctime,int isclone,char *server) */
	new_user(message->RAW[1],message->RAW[4],message->RAW[5],message->message,atol(message->RAW[3]),message->RAW[6]);
}

void p_MSG_ERROR(  message_irc *message  )              /* ERROR */
{
	/*
	ERROR :<error message>
	*/
	sock_deconnect();
}

void p_MSG_CHGHOST(  message_irc *message  )            /* CHGHOST */
{
	/*
	:<source> CHGHOST <nick> <newvhost>
	*/
	/* set_vhost(char *nick,char *vhost,char *from) */
	set_vhost(message->RAW[2] , message->RAW[3],message->RAW[0]);
}

void p_MSG_CHGIDENT(  message_irc *message  )           /* CHGIDENT */
{
	/*
	:<source> CHGIDENT <nick> <new ident>
	*/
	/* set_handle(char *nick,char *handle,char *from) */
	set_handle(message->RAW[2],message->RAW[3],message->RAW[0]);
}

void p_MSG_CHGNAME(  message_irc *message  )            /* CHGNAME */
{
	/*
	:<source> CHGNAME <nick> :<new real name string>
	*/
	/* set_real(char *nick,char *handle,char *from) */
	set_real(message->RAW[2],message->message,message->RAW[0]);
}

void p_MSG_SETHOST(  message_irc *message  )            /* SETHOST */
{
	/*
	:<source> SETHOST <host>
	*/
	/* set_vhost(char *nick,char *vhost,char *from) */
	set_vhost(message->RAW[0], message->RAW[2],NULL);
}

void p_MSG_SETNAME(  message_irc *message  )            /* SETNAME */
{
	/*
	:<source> SETNAME :<newrealname
	*/
	set_real(message->RAW[0], message->message,NULL);
}

void p_MSG_SETIDENT(  message_irc *message  )           /* SETIDENT */
{
	/*
	:<source> SETIDENT <new ident>
	*/
	set_handle(message->RAW[0], message->RAW[2],NULL);
}

void p_MSG_NOTICE(  message_irc *message  )             /* NOTICE */
{
	p_MSG_PRIVMSG(  message  );
}

void p_MSG_PING(  message_irc *message  )               /* PING */
{
	char buffer[256];
	sprintf(buffer,COM_USER_PONG,message->ARG[0]);
	_send(buffer);
}

void p_MSG_PART(  message_irc *message  )               /* PART */
{
	/*
		:<source> PART <channel> :<message part string>
	*/
	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	set_Ltime(use->nick);

	/* int user_part(char *name,User *use) */
	user_part(message->RAW[2] ,use);
}

void p_MSG_JOIN(  message_irc *message  )               /* JOIN */
{
	/*
	:<source> JOIN <channel>,<channel>,<channel>
	*/
	/* int user_join(char *name,User *use) */
	char *ptr,*sav;
	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	set_Ltime(use->nick);

	STRDUP(sav,message->RAW[2])
	ptr = strtok(sav,",");
	while( ptr != NULL)
	{
		user_join( ptr, use);
		ptr = strtok(NULL,",");
	}
	FREE(sav);
}

void p_MSG_MODE(  message_irc *message  )               /* MODE */
{
	/*
		:<source> MODE <target> :<mode>
		:<source> MODE <target> <mode> <nick> <timestamp>
		:<source> MODE <target> <mode> <timestamp>
	*/
	/* void set_Mode_Chan(Channel *channel , char *from , char mode , int on_off) */
	/* void set_Mode_Status(Channel *channel , char *nick, char *from , char mode , int on_off) */
	User *use;
	Channel *channel;
	int action = FALSE;
	char m[30];
	char c,d;
	int i = 0;
	int u = 4;
	long time_t = 0; /* for banlist */

	printf("nRaw %d\n",message->n_raw);
	printf("nArg %d\n",message->n_arg);

	if(message->ARG[0] != NULL)
	{
		use = get_user(message->RAW[0]);
		if(!use)
			return;

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
					set_flag(use,use->nick, c , action);
					break;
			}
		}
	}
	else
	{
		if(strlen(message->RAW[3]) == 1)
			return;

		channel = get_channel(message->RAW[2]);
		if(!channel)
			return;

		strcpy(m,message->RAW[3]);
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

				case 'o':
				case 'v':
				case 'q':
				case 'h':
				case 'a':
					set_Mode_Status(channel , message->RAW[u++],  c , action);
					break;

				case 'b':
					if(message->RAW[message->n_raw] != NULL)
						time_t = atol(message->RAW[message->n_raw]);
					else
						time_t = time(NULL);

					if(action == FALSE)
						del_ban(channel,message->RAW[u++],time_t);
					else
						new_ban(channel,message->RAW[u++],time_t);
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
					set_Mode_Chan(channel , c , action);
					break;
			}
		}
	}
}

void p_MSG_QUIT(  message_irc *message  )               /* QUIT */
{
	/*
		:<source> QUIT :<quit message>
	*/
	del_user(message->RAW[0],message->message);
}

void p_MSG_PRIVMSG(  message_irc *message  )            /* PRIVMSG */
{
/**

	
	extern Com_IN *pCom_IN;
	Com_IN *myCom;
	User *use;
	int i = 0 ;
	char *ptr;
	int porte = 0;
	int is_commande = 0;

	if(message->ARG[0] == NULL) 
		return;

	while(message->ARG[i] != NULL)
	{
		retirecouleur(message->ARG[i],message->ARG[i]);
		i++;
	}
	i = 0 ;

	if(message->RAW[2][0] == '#')
		porte = 1;
	else
		porte = 2;

	if(message->ARG[0][0] == '!')
	{
		message->ARG[0]++;
	}

	STRDUP(ptr = message->ARG[0]);

	myCom = pCom_IN;
	while(myCom)
	{
		if(myCom->porte == 1 && porte == 1)
		{
			if(!strcasecmp(myCom->ComName, ptr))
			{
				use = get_user(get_source(message->RAW[0],1));
				if(!use)
					return;

				set_Ltime(use->nick);

				if(myCom->ComFlag[0] != '?')
					if(!is_valide(use , myCom->ComFlag,myCom->niveau))
						return;

				myCom->func(message);
				is_commande = 1;
	
			}
		}
		if(myCom->porte == 2 && porte == 2)
		{
			if(!strcasecmp(myCom->ComName, ptr) && !strcasecmp(myCom->ComBot, message->RAW[2]))
			{
				use = get_user(get_source(message->RAW[0],1));
				if(!use)
					return;

				set_Ltime(use->nick);

				if(myCom->ComFlag[0] != '?' && myCom->niveau != 0)
					if(!is_valide(use , myCom->ComFlag,myCom->niveau))
						return;

				myCom->func(message);
				is_commande = 1;
			}
		}
		myCom = myCom->suivant;
	}

	if(is_commande == 0)
	{
		if(USEANTISPAM)
		{
			find_spam(message);
		}
	}

	FREE(ptr);
**/
}

void p_MSG_NICK(  message_irc *message  )               /* NICK */
{
	/*
		:<source> NICK <new nick>
	*/
	set_Ltime(message->RAW[0]);
	set_nick(message->RAW[0],message->RAW[2]);
}

void p_MSG_KICK(  message_irc *message  )               /* KICK */
{
	/*
		:<source> KICK <channel> <target> :<motif string>
	*/
	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	set_Ltime(message->RAW[0]);

	use = get_user(message->RAW[3]);
	user_part(message->RAW[2],use);
}

void p_MSG_INVITE(  message_irc *message  )             /* INVITE */
{
	/*
	:<source> INVITE <target> :<channel>
	*/
}

void p_MSG_KILL(  message_irc *message  )               /* KILL */
{
	/*
	<source> KILL <target> :<motif>
	*/
	del_user(message->RAW[2],message->message);	
}

void p_MSG_AWAY(  message_irc *message  )               /* AWAY */
{
	/*
		:<source> AWAY :<motif>
		ou
		:yoyo49 AWAY
	*/
	set_Ltime(message->RAW[0]);	
}

void p_MSG_SENDNO(  message_irc *message  )              /* SENDNO */
{
	/*
	:<source> SENDSNO <flag> :<message string>
	*/
}

void p_MSG_SMO(  message_irc *message  )                /* SMO */
{
	/*
	:<source> SMO <flag> :<message string>
	*/
}

void p_MSG_WALLOPS(  message_irc *message  )            /* WALLOPS */
{
	/*
	:yoyo49 WALLOPS :lololol
	*/
}

void p_MSG_NACHAT(  message_irc *message  )           /* NACHAT */
{
	/*
	:<source> NACHAT :<message string>
	*/
}

void p_MSG_CHATOPS(  message_irc *message  )           /* CHATOPS */
{
	/*
	:<source> CHATOPS :<message string>
	*/
}

void p_MSG_ADCHAT(  message_irc *message  )           /* ADCHAT */
{
	/*
	:<source> CHATOPS :<message string>
	*/
}

void p_MSG_GLOBOPS(  message_irc *message  )            /* GLOBOPS */
{
	/*
	:yoyo49 GLOBOPS :lol
	*/
}

void p_MSG_TOPIC(  message_irc *message  )              /* TOPIC */
{
	/*
		TOPIC <channel> <auteur> <timestam> :<topic string>
		ou
		:<source> TOPIC <channel> <auteur> <timestam> :<topic string>
	*/
	if(strcmp(message->RAW[0],"TOPIC") == 0)
	{
		new_channel(message->RAW[1],atol(message->RAW[3]),message->RAW[2],message->message);
	}
	else
	{
		set_topic(message->RAW[2],message->message,message->RAW[3],atol(message->RAW[4]));
	}
}

void p_MSG_WHOIS(  message_irc *message  )              /* WHOIS */
{
	/*
	:yoyo49 WHOIS InFo_BoT_V2 :InFo_BoT_V2
	*/
	extern User *commandeur;
	commandeur = get_user(message->RAW[0]);
	fsend_com(LINK_COM_USER_WHOIS,myconfig->botnick,message->RAW[2]);
}

void p_MSG_SERVER(  message_irc *message  )             /* SERVER */
{
	/*
	SERVER <server> <int> :<server identifiant>
	*//**
	Protect *tmp;
	char *ptr;
	char mask[256];
	ptr = strtok(message->RAW[1],".");
	ptr = strtok(NULL,"\0");
	sprintf(mask,"%s%s","*.",ptr);
	tmp = new_Protect(mask);
	return;**/
}

void p_MSG_NETINFO(  message_irc *message  )            /* NETINFO */
{
	/*
	NETINFO 8 1156805828 2307 MD5:32119e598a00855e91715ecbd4c07012 0 0 0 :irc.ax-proxima.net
	*/
}

void p_MSG_PROTOCTL(  message_irc *message  )           /* PROTOCTL */
{
	/*
	PROTOCTL NOQUIT TOKEN NICKv2 SJOIN SJOIN2 UMODE2 VL SJ3 NS SJB64 TKLEXT NICKIP CHANMODES=beIqa,kfL,lj,psmntirRcOAQKVCuzNSMTG NICKCHARS=
	*/
}

void p_MSG_EOS(  message_irc *message  )                /* EOS */
{

}

void p_MSG_PASS(  message_irc *message  )               /* PASS */
{
	/*
	PASS <pass>
	*/
}

void p_MSG_TKL(  message_irc *message  )                /* TKL */
{
	/*
		:<source> TKL + <type> <handle> <host cible> <host emeteur> <expire> <time> :<motif string>
		:<source> TKL - <type> <handle> <host cible> <host emeteur>
	*/
}




