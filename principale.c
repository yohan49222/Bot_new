#include "main.h"

extern Config *myconfig;

static char *me = "";

void init_principale()
{
	strdup(me = myconfig->botnick);
	User *use;

	if(get_clone(me))
		return;

	use = new_clone(me,myconfig->flags,myconfig->real,NULL);
	if(!use)
	{
		printf("Impossible de creer le bot principale\n");
		exit(0);
	}
	Create_Raw_Bot("PRIVMSG"  	,&PRINCIPALE_PRIVMSG, me);
	Create_Raw_Bot("KILL"  		,&PRINCIPALE_KILL		,me);
	Create_Raw_Bot("KICK"  		,&PRINCIPALE_KICK		,me);

	Create_Com("help" , me, &principale_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");

	Create_Com("rehash" , me, &principale_rehash ,"NCA","/msg %s REHASH","Permet de recharger le fichier de configuration");

	Create_Com("die" , me, &principale_die ,"NCA","/msg %s DIE","Permet de Deconnecter tous les services");
}

void unload_principale()
{
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}

void PRINCIPALE_PRIVMSG(message_irc *message)
{
	printf("PRINCIPALE_PRIVMSG\n");

	if(strcasecmp(message->RAW[2],me))
		return;


	User *use = get_user(message->RAW[0]);
	if(!use)
		return;


	executeCom( use, message , me);
}

void PRINCIPALE_KILL(message_irc *message)
{
	printf("PRINCIPALE_KILL\n");
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
	}
}

void PRINCIPALE_KICK(message_irc *message)
{
	printf("PRINCIPALE_KICK\n");
	if(!strcasecmp(message->RAW[3],me))
	{
		bot_join(me, message->RAW[2] , "+v");
	}
}

void principale_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void principale_rehash(User *use , message_irc *message)
{
	rehash();
}

void principale_die(User *use , message_irc *message)
{
	exit(1);
}

