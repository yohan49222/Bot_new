#include "main.h"

extern Config *myconfig;

Protect *Allprotect = NULL;

static char *me = "ProtectServ";


void init_protectserv()
{
	if(get_clone(me))
		return;

	new_clone(me,myconfig->flags,myconfig->real,NULL);

	load_bd_protect();

	Create_Raw_Protect("CONNECT"  	,&PROTECTSERV_CONNECT);
	Create_Raw_Bot("PRIVMSG"  	,&PROTECTSERV_PRIVMSG	,me);
	Create_Raw_Bot("KILL"  		,&PROTECTSERV_KILL		,me);
	Create_Raw_Bot("KICK"  		,&PROTECTSERV_KICK		,me);

	Create_Com("help" , me, &protectserv_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");
	Create_Com("add" , me , &protectserv_add ,"ACN","/msg %s ADD <mask>","Ajoute un mask a la liste des protections");
	Create_Com("del" , me , &protectserv_del ,"ACN","/msg %s DEL <mask>","Supprime le mask de la liste des protections");
	Create_Com("list" , me , &protectserv_list ,"ACN","/msg %s LIST <mask>","Liste tous les mask protégés");
}

void unload_protectserv()
{
	clear_Protect();
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}
void PROTECTSERV_CONNECT(message_irc *message)
{
	printf("PROTECTSERV_CONNECT\n");

	User *use = get_user(message->RAW[1]);
	if(!use)
		return;

	get_Protect(use);
}

void PROTECTSERV_PRIVMSG(message_irc *message)
{
	printf("PROTECTSERV_PRIVMSG\n");

	if(strcasecmp(message->RAW[2],me))
		return;


	User *use = get_user(message->RAW[0]);
	if(!use)
		return;


	executeCom( use, message , me);


}

void PROTECTSERV_KILL(message_irc *message)
{
	printf("PROTECTSERV_KILL\n");
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
	}
}

void PROTECTSERV_KICK(message_irc *message)
{
	printf("PROTECTSERV_KICK\n");
	if(!strcasecmp(message->RAW[3],me))
	{
		bot_join(me, message->RAW[2] , "+v");
	}
}


void load_bd_protect()
{
	FILE *myFile;
	char ligne[256];
	char *var = NULL;
	char *p;

	/* chargement des protection */
	if((myFile= fopen("base/protect.db", "r")) != NULL)
	{
		while(fgets(ligne, sizeof ligne, myFile))
		{
			if( (ligne[0] != '#') && (strlen(ligne) > 0 ))
			{
				p = strchr(ligne, '\n');
				if (p)
					*p = '\0';

				p = strchr(ligne, '\r');
				if (p)
					*p = '\0';

				var = strtok(ligne , " ");
				if(var)
				{
					sscanf(var,"%s",var);
					new_Protect(var);
				}
			}
		}
	}
	fclose(myFile);
}

/*
	Ajout d'un Mask Protect return NULL si erreur
*/
Protect *new_Protect(char *mask)
{
	Protect *newProtect;

	if(!*mask)
		return NULL;

	newProtect = (Protect*)malloc(sizeof(Protect));
	if(!newProtect)
		return NULL;

	STRDUP(newProtect->mask,mask);

	fsend_service(me,FORMAT_NEWPROTECT,mask);
	
	newProtect->precedent = NULL;
	newProtect->suivant = Allprotect;
	if (Allprotect)
    		Allprotect->precedent = newProtect;
	Allprotect = newProtect;
	return Allprotect;

}

/*
	supression d'un Mask Protect return 1 si success sinon return 0
*/
int del_Protect(char *mask)
{
	Protect *nprotect;
	nprotect = Allprotect;
	while (nprotect)
	{
		if(strcasecmp(nprotect->mask,mask) == 0)
		{
			if(nprotect->suivant)
				nprotect->suivant->precedent = nprotect->precedent;

			if(nprotect->precedent)
				nprotect->precedent->suivant = nprotect->suivant;

			if(nprotect == Allprotect)
				Allprotect = nprotect->suivant;

			fsend_service(me,FORMAT_DELPROTECT,mask);
			
			FREE(nprotect->mask);
			FREE(nprotect);

			return 1;
		}
		nprotect = nprotect->suivant;
	}
	return 0;
}

int clear_Protect()
{
	Protect *nprotect;
	while (Allprotect)
	{
		nprotect = Allprotect;
		Allprotect = Allprotect->suivant;
		FREE(nprotect->mask);
		FREE(nprotect);
		nprotect = NULL;
	}
	Allprotect = NULL;
	return 1;
}

void get_Protect(User *use)
{
	Protect *nprotect;
	nprotect = Allprotect;
	while(nprotect)
	{
		if(match(nprotect->mask,use->host) == 1)
		{
			fsend_service(me,FORMAT_PROTECTOK,use->nick);
			use->option |= IS_PROTECT;
			return;
		}
		nprotect = nprotect->suivant;
	}
}

long Protect_t()
{
	int count = 0;

	Protect *u;
	u = Allprotect;
	while (u)
	{
		count++;
		u = u->suivant;
	}
	return sizeof(Protect) * (count+1);
}

void protectserv_add( User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	
	new_Protect(message->ARG[1]);

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le mask est maintenant prot\xe9g\xe9.");
}

void protectserv_del( User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	
	del_Protect(message->ARG[1]);

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le mask n'est plus prot\xe9g\xe9.");
}

void protectserv_list( User *use , message_irc *message)
{

	Protect *nprotect;
	nprotect = Allprotect;

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le(s) mask(s)  prot\xe9g\xe9(s) :");


	while(nprotect)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,nprotect->mask);

		nprotect = nprotect->suivant;
	}
}

void protectserv_help(User *use , message_irc *message)
{
	help(use,message,me);
}
