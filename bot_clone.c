#include "main.h"

extern Config *myconfig;


/**
	***************************************************
	** Gestions du Bot principale et des bots clones **
	***************************************************
**/

bot_clone *Allclone = NULL;

User *new_clone(char *nick,char *flag,char *real,char *vhost)
{
	User *use = NULL;
	bot_clone *newclone = NULL;
	char c = '\0';
	long t_timt = time(NULL);
	char host_tmp[256];

	if(!nick || !*nick)
	{
		put_log("Tentative de creation d'un clone sans pseudo , fonction new_clone");
		exit(1);
	}

	/* allocation memoire */
	newclone = (bot_clone*)malloc(sizeof(bot_clone));
	if(!newclone)
	{
		put_log("Erreur Creation du clone , fonction new_clone");
		exit(1);
	}

	
	STRDUP(newclone->nick,nick);
	
	/* creation de son host */
	if(vhost)
	{
		STRDUP(newclone->host,vhost);
	}
	else
	{
		sprintf(host_tmp,"%s%s",newclone->nick,myconfig->hostc);
		STRDUP(newclone->host,host_tmp);
	}

	if(flag)
	{
		STRDUP(newclone->flag,flag)
	}
	else
	{
		STRDUP(newclone->flag,"iwx")
	}

	if(real)
	{
		STRDUP(newclone->real,real)
	}
	else
	{
		STRDUP(newclone->real,"Clone Service Irc")
	}

	STRDUP(newclone->handle,nick)

	newclone->handle[8] = 0;

	fsend_com(COM_SERV_NICK, newclone->nick, t_timt, newclone->handle, newclone->host , myconfig->host, newclone->flag ,newclone->real);

	use = new_user(newclone->nick,newclone->handle,newclone->host,newclone->real,t_timt,myconfig->host);

	if(!use)
	{
		put_log("Erreur Creation de l'user , fonction new_clone");
		exit(1);
	}

	use->option |= IS_CLONE;
	use->option |= IS_PROTECT;

	fsend_service(use->nick,FORMAT_CONNECT, use->nick,use->nick,use->handle,use->host,use->server,maxclone(use));

	/* application de ses flags use */
	flag = newclone->flag;
	while((c = *flag++))
		if(c!='+')
			set_flag( use , myconfig->botnick, c , TRUE);

	/* mise en liste doublement chainee */
	newclone->precedent = NULL;
	newclone->suivant = Allclone;
	if (Allclone)
    		Allclone->precedent = newclone;
	Allclone = newclone;

	Create_Com("version" , use->nick, &bot_clone_version ,"?","/msg %s VERSION" ,"Permet de voir la Version du bot");

	bot_join(use->nick, myconfig->service , "+v");

	return use;
}

void bot_join(char *botnick , char *chanName , char *mode)
{
	Channel *channel;
	User *use = get_user(botnick);
	if(!use)
		return;

	fsend_com(LINK_COM_USER_JOIN,use->nick,chanName);
	
	fsend_service(myconfig->botnick,FORMAT_JOIN ,use->nick,chanName);

	user_join(chanName,use);

	channel = get_channel(chanName);
	if(!channel)
		return;

	if(strlen(mode) != 2)
		return;

	switch(mode[0])
	{
		case '+':
			set_Mode_Status(channel ,use->nick,mode[1], TRUE);
			break;

		case '-':
			set_Mode_Status(channel ,use->nick,mode[1], FALSE);
			break;
	}

	fsend_com(LINK_COM_USER_MODE_USE,myconfig->botnick,chanName,mode,use->nick);

	fsend_service(myconfig->botnick,FORMAT_MODE ,myconfig->botnick,mode,use->nick,chanName);
}


int clear_clone()
{
	bot_clone *newclone;
	while (Allclone)
	{
		newclone = Allclone;
		Allclone = Allclone->suivant;
		FREE(newclone);
		newclone = NULL;
	}
	Allclone = NULL;
	return 1;
}

int del_clone(char *nick,char *messquit)
{
	bot_clone *clone = Allclone;
	while (clone)
	{
		if(!strcasecmp(clone->nick,nick))
		{
			if(clone->suivant)
				clone->suivant->precedent = clone->precedent;

			if(clone->precedent)
				clone->precedent->suivant = clone->suivant;

			if(clone == Allclone)
				Allclone = clone->suivant;

			FREE(clone->nick);
			FREE(clone->handle);
			FREE(clone->host);
			FREE(clone->real);
			FREE(clone->flag);
			FREE(clone);
			
			if(get_user(nick))
			{
				fsend_com(LINK_COM_USER_QUIT,nick,messquit);
				
				del_user(nick,messquit);
			}
			return 1;
		}
		clone = clone->suivant;
	}
	return 0;
}


long bot_clone_t()
{
	int count = 0;
	bot_clone *u = Allclone;
	while (u)
	{
		count++;
		u = u->suivant;
	}
	return sizeof(bot_clone) * (count+1);
}

int get_clone(char *nick)
{
	bot_clone *clone = Allclone;
	while (clone)
	{
		if(!strcasecmp(clone->nick,nick))
			return 1;

		clone = clone->suivant;
	}
	return 0;
}

void bot_clone_version(User *use , message_irc *message)
{
	char txt[MAXLEN];
	extern char *my_version;
	sprintf(txt,"Je suis un Service Operateur , developp\xe9 par yoyo49 , version %s",my_version);
	fsend_com(LINK_COM_USER_NOTICE,message->RAW[2],use->nick,txt);
}

