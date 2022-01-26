#include "main.h"

extern Config *myconfig;

static char *me = "GlobalServ";

void init_global()
{
	User *use;
	if(get_clone(me))
		return;

	use = new_clone(me,myconfig->flags,myconfig->real,NULL);
	if(!use)
		return;

	Create_Raw_Bot("PRIVMSG"  	,&GLOBAL_PRIVMSG	, me);
	Create_Raw_Bot("KILL"  		,&GLOBAL_KILL		,me);
	Create_Raw_Bot("KICK"  		,&GLOBAL_KICK		,me);


	Create_Com("help", me, &global_help ,"?","/msg %s HELP [<command>]","Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");

	Create_Com("global" , me, &global_global ,"o","/msg %s GLOBAL <message>","Permet d'envoyer un message a tous les utilisateur du serveur");

	Create_Com("globop" , me, &global_globop ,"o","/msg %s GLOBOP <message>","Permet d'envoyer un message a tous les ircop du serveur");

}

void unload_global()
{

	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}

void GLOBAL_PRIVMSG(message_irc *message)
{
	printf("GLOBAL_PRIVMSG\n");

	if(strcasecmp(message->RAW[2],me))
		return;


	User *use = get_user(message->RAW[0]);
	if(!use)
		return;


	executeCom( use, message , me);
}

void GLOBAL_KILL(message_irc *message)
{
	printf("GLOBAL_KILL\n");
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
	}
}

void GLOBAL_KICK(message_irc *message)
{
	printf("GLOBAL_KICK\n");
	if(!strcasecmp(message->RAW[3],me))
	{
		bot_join(me, message->RAW[2] , "+v");
	}
}


void global_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void global_global(User *use , message_irc *message)
{
	int i = 1;
	char txt[MAXLEN];
	char txt2[MAXLEN];
	extern User *Alluser;
	User *use2 = Alluser;

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	while(message->ARG[i])
	{
		if(i == 1)
			sprintf(txt,"%s",message->ARG[i]);
		else
			sprintf(txt,"%s %s",txt,message->ARG[i]);
		i++;
	}

	sprintf(txt2,"Message Global de \0034%s \0031:\0031%s",use->nick,txt);

	while(use2)
	{

		fsend_com(LINK_COM_USER_NOTICE,me,use2->nick,txt2);
		use2 = use2->suivant;
	}
}

void global_globop(User *use , message_irc *message)
{
	int i = 1;
	char txt[MAXLEN];
	char txt2[MAXLEN];
	extern User *Alluser;
	User *use2 = Alluser;

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	while(message->ARG[i])
	{
		if(i == 1)
			sprintf(txt,"%s",message->ARG[i]);
		else
			sprintf(txt,"%s %s",txt,message->ARG[i]);
		i++;
	}

	sprintf(txt2,"Message Global Ircop de \0034%s \0031:\0031%s",use->nick,txt);

	while(use2)
	{
		if(is_Capable(use2,'o'))
		{
			fsend_com(LINK_COM_USER_NOTICE,me,use2->nick,txt2);
		}
		use2 = use2->suivant;
	}
}



