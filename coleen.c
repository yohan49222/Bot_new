#include "main.h"

extern Config *myconfig;

static char *me = "Coleen";
char *coleen_pseudo = "coleen";
char *coleen_channel[] = { "#ircop-admin" , "#sysop" , NULL };

Coleen_Access *pColeen_Access = NULL;


void init_coleen()
{
	if(get_clone(me))
		return;

	User *use = new_clone(me,myconfig->flags,myconfig->real,NULL);
	if(!use)
		return;

	load_db_access();
	Create_Raw_Bot("PRIVMSG"  	,&COLEEN_PRIVMSG, me);
	Create_Raw_Bot("KILL"  		,&COLEEN_KILL		,me);
	Create_Raw_Bot("KICK"  		,&COLEEN_KICK		,me);

	Create_Com("help" , me, &coleen_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");
	Create_Com("auth" , me, &coleen_auth ,"?","/msg %s AUTH <pseudo> <pass>","Permet de s'indentifer");
	Create_Com("deauth" , me, &coleen_deauth ,"?","/msg %s DEAUTH","Permet de vous desidentifer");
	Create_Com("kill" , me, &coleen_kill ,"?","/msg %s KILL <pseudo> [<motif>]","Permet d'explulser l'use du serveur , le motif est optionnel");
	Create_Com("gline" , me, &coleen_gline ,"?","/msg %s GLINE <pseudo> <duree> [<motif>]","Permet de poser un gline sur le host de l'use , le motif est optionnel");
	Create_Com("say" , me, &coleen_say ,"?","/msg %s SAY <channel|pseudo> <message>","De faire parler le robot");

	Create_Com("add_access" , me, &coleen_add_access ,"?","/msg %s ADD_ACCESS <pseudo> <pass> <CSA|GEO>","Ajout un nouvel access");
	Create_Com("suspend" , me, &coleen_suspend ,"?","/msg %s SUSPEND <pseudo>","Suspend l'access du pseudo");
	Create_Com("reactive" , me, &coleen_reactive ,"?","/msg %s REACTIVE <pseudo>","Reative l'access du pseudo");
	Create_Com("deluser" , me, &coleen_deluser ,"?","/msg %s DELUSER <pseudo>","Supprime définitivement l'access du pseudo");
	Create_Com("setpass" , me, &coleen_setpass ,"?","/msg %s SETPASS <pseudo> <newpass>","Modifie le pass du pseudo");
	Create_Com("setaccess" , me, &coleen_setaccess ,"?","/msg %s SETACCESS <pseudo> <CSA|GEO>","Modifie le niveau d'access du pseudo");
	Create_Com("accesslist" , me, &coleen_accesslist ,"?","/msg %s ACCESSLIST","Vous affiche l'accesslist complete");


	Create_Com("op" , me, &coleen_op ,"?","/msg %s OP <chan> <pseudo>","Permet d'op l'user sur le chan");
	Create_Com("deop" , me, &coleen_deop ,"?","/msg %s DEOP <chan> <pseudo>","Permet de deop l'user sur le chan");

	Create_Com("voice" , me, &coleen_voice ,"?","/msg %s VOICE <chan> <pseudo>","Permet de voice l'user sur le chan");
	Create_Com("devoice" , me, &coleen_devoice ,"?","/msg %s DEVOICE <chan> <pseudo>","Permet de devoice l'user sur le chan");

	Create_Com("halfop" , me, &coleen_half ,"?","/msg %s HALFOP <chan> <pseudo>","Permet de halfop l'user sur le chan");
	Create_Com("dehalfop" , me, &coleen_dehalf ,"?","/msg %s DEHALFOP <chan> <pseudo>","Permet de dehalfop l'user sur le chan");


	Create_Com("mop" , me, &coleen_mop ,"?","/msg %s MOP <chan>","Permet d'op tous les users sur le chan");
	Create_Com("mdeop" , me, &coleen_mdeop ,"?","/msg %s MDEOP <chan>","Permet de deop tous les users sur le chan");

	Create_Com("mvoice" , me, &coleen_mvoice ,"?","/msg %s MVOICE <chan>","Permet de voice tous les users sur le chan");
	Create_Com("mdevoice" , me, &coleen_mdevoice ,"?","/msg %s MDEVOICE <chan>","Permet de devoice tous les users sur le chan");

	Create_Com("mhalfop" , me, &coleen_mhalf ,"?","/msg %s MHALFOP <chan>","Permet de halfop tous les users sur le chan");
	Create_Com("mdehalfop" , me, &coleen_mdehalf ,"?","/msg %s MDEHALFOP <chan>","Permet de dehalfop tous les users sur le chan");

	Create_Com("mkick" , me, &coleen_mkick ,"?","/msg %s MKICK <channel> [<motif>]","Permet de kicker tous les users du channel");


	Create_Com("ungline" , me, &coleen_ungline ,"?","/msg %s UNGLINE <host>","Permet de suprimer le Gline sur le host");
	Create_Com("cleargline" , me, &coleen_cleargline ,"?","/msg %s CLEARGLINE","Permet de vider la liste des Gline");
	Create_Com("glinelist" , me, &coleen_glinelist ,"?","/msg %s GLINELIST","Permet de voir la liste des Gline");


	Create_Com("kick" , me, &coleen_kick ,"?","/msg %s KICK <channel> <pseudo>","Permet de kicker le pseudo du channel");

	Create_Com("sajoin" , me, &coleen_sajoin ,"?","/msg %s SAJOIN <channel> <pseudo>","Permet de faire joindre le pseudo sur le channel");
	Create_Com("sapart" , me, &coleen_sapart ,"?","/msg %s SAPART <channel> <pseudo>","Permet de faire partir le pseudo du channel");


	Create_Com("swhois" , me, &coleen_swhois ,"?","/msg %s SWHOIS <pseudo>","Permet de retrouver toutes les informations sur le pseudo geree par les services");

	bot_join(me, "#ircop-admin" , "+o");
	bot_join(me, "#sysop" , "+o");
	bot_join(me, myconfig->service , "+o");
}

void unload_coleen()
{
	clear_access();
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}


void load_db_access()
{
	FILE *db;
	char ligne[512];
	char *nick , *pass, *p;
	int niveau = 0, actif = 0;

	db = fopen("base/access.db", "r");
	if(!db)
		return;

	while(fgets(ligne, sizeof ligne, db))
	{
		if( (ligne[0] != '#') && (strlen(ligne) > 1 ))
		{
			p = strchr(ligne, '\n');
			if (p)
				*p = '\0';

			p = strchr(ligne, '\r');
			if (p)
				*p = '\0';

			nick = strtok(ligne, ":");
			pass = strtok(NULL, ":");
			niveau = atoi( strtok(NULL, ":") );
			actif = atoi( strtok(NULL, ":") );
			new_Coleen_Access(nick,pass,niveau,actif);
		}
	}
	fclose(db);
	fsend_service(me,CHAR_BD_OK,"Access");

}

void save_Coleen_access()
{
	Coleen_Access *n;
	FILE *myFile = fopen("base/access.db", "w");
	if(!myFile)
		return;

	n = pColeen_Access;
	while(n)
	{
		fprintf(myFile,"%s:%s:%d:%d\n",n->nick,n->pass,n->niveau,n->actif);
		n = n->suivant;
	}
	fclose(myFile);
	fsend_service(me,SAVE_BD_OK,"Access");
}


Coleen_Access *new_Coleen_Access(char *nick,char *pass,int niveau,int actif)
{
	Coleen_Access *n;

	if(!*nick || !*pass || niveau == 0)
		return NULL;

	n = (Coleen_Access*)malloc(sizeof(Coleen_Access));
	if(!n)
		return NULL;

	STRDUP(n->nick,nick);
	STRDUP(n->pass,pass);
	n->niveau = niveau;
	n->actif = actif;

	n->precedent = NULL;
	n->suivant = pColeen_Access;
	if (pColeen_Access)
    		pColeen_Access->precedent = n;
	pColeen_Access = n;

	switch(n->niveau)
	{
		case 1:
			fsend_service(me,"\0034ACCESS\0031 : pseudo :\0034 %s\0031 , niveau :\0034 %s",n->nick,"Géo");
			break;

		case 2:
			fsend_service(me,"\0034ACCESS\0031 : pseudo :\0034 %s\0031 , niveau :\0034 %s",n->nick,"Csa");
			break;

		case 3:
			fsend_service(me,"\0034ACCESS\0031 : pseudo :\0034 %s\0031 , niveau :\0034 %s",n->nick,"Ircop");
			break;	
	}
	return pColeen_Access;
}

int del_Coleen_Access(char *nick)
{
	Coleen_Access *n = get_Coleen_Access(nick);
	if(!n)
		return 0;

	if(n->suivant)
		n->suivant->precedent = n->precedent;

	if(n->precedent)
		n->precedent->suivant = n->suivant;

	if(n == pColeen_Access)
		pColeen_Access = n->suivant;

	FREE(n->nick);
	FREE(n->pass);
	FREE(n);

	return 1;
}

int clear_access()
{
	Coleen_Access *n;
	while (pColeen_Access)
	{
		n = pColeen_Access;
		pColeen_Access = pColeen_Access->suivant;
		FREE(n->nick);
		FREE(n->pass);
		FREE(n);
		n = NULL;
	}
	pColeen_Access = NULL;
	return 1;
}

Coleen_Access *get_Coleen_Access(char *nick)
{
	Coleen_Access *n = pColeen_Access;
	while(n)
	{
		if(!strcasecmp(n->nick,nick))
			return n;

		n = n->suivant;
	}
	return NULL;
}

void set_geo(User *use,int onoff)
{
	if(onoff)
		use->Access_Coleen |= COLEEN_FLAGS_GEO;
	else
		use->Access_Coleen &= (0xFFFFFFFF ^ COLEEN_FLAGS_GEO);
}

void set_csa(User *use,int onoff)
{
	if(onoff)
		use->Access_Coleen |= COLEEN_FLAGS_CSA;
	else
		use->Access_Coleen &= (0xFFFFFFFF ^ COLEEN_FLAGS_CSA);
}

void set_ircop(User *use,int onoff)
{
	if(onoff)
		use->Access_Coleen |= COLEEN_FLAGS_IRCOP;
	else
		use->Access_Coleen &= (0xFFFFFFFF ^ COLEEN_FLAGS_IRCOP);
}

void COLEEN_PRIVMSG(message_irc *message)
{
	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	if(strcasecmp(message->RAW[2],me))
		return;

	executeCom( use, message , me);
}

void COLEEN_KILL(message_irc *message)
{
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
		bot_join(me, "#ircop-admin" , "+o");
		bot_join(me, "#sysop" , "+o");
		bot_join(me, myconfig->service , "+o");
	}
}

void COLEEN_KICK(message_irc *message)
{
	if(!strcasecmp(message->RAW[3],me))
		bot_join(me, message->RAW[2] , "+o");
}

void coleen_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void coleen_auth(User *use , message_irc *message)
{
	char txt[MAXLEN];
	Coleen_Access *access;

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	access = get_Coleen_Access(message->ARG[1]);
	if(!access)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Il m'est impossible de vous identifier , Votre pseudo n'est pas reconnu !!");
		return;
	}

	if(strcmp(access->pass,message->ARG[2]))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Il m'est impossible de vous identifier , Votre pass n'est pas le bon !!");
		return;
	}

	if(!access->actif)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Il m'est impossible de vous identifier , Votre access est suspendu !!");
		return;
	}


	FREE(use->Access_Coleen_pseudo);
	STRDUP(use->Access_Coleen_pseudo,access->nick);

	switch(access->niveau)
	{
		case 1:
			set_geo(use,TRUE);
			set_csa(use,FALSE);
			set_ircop(use,FALSE);
			fsend_service(me,"\0034AUTH\0031 :\0034 %s \0031vient de s'indetifier , son access est\0034 G\xe9o", use->nick);
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous etes maintenant identifié , votre access est\0034 G\xe9o");
			break;

		case 2:
			set_csa(use,TRUE);
			set_geo(use,TRUE);
			set_ircop(use,FALSE);
			fsend_service(me,"\0034AUTH\0031 :\0034 %s \0031vient de s'indetifier , son access est\0034 CSA", use->nick);
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous etes maintenant identifié , votre access est\0034 CSA");
			break;

		case 3:
			set_csa(use,TRUE);
			set_geo(use,TRUE);
			set_ircop(use,TRUE);
			fsend_service(me,"\0034AUTH\0031 :\0034 %s \0031vient de s'indetifier , son access est\0034 Ircop", use->nick);
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous etes maintenant identifié , votre access est\0034 Ircop");
			break;	
	}

	if(!strcmp(message->ARG[1],"aspam"))
	{
		sprintf(txt,"%s%s",use->nick,myconfig->hostc);
		set_vhost(use->nick ,txt,me);
		fsend_com(LINK_COM_OPER_CHGHOST,myconfig->host,use->nick,txt);
		fsend_service(me,FORMAT_CHGVHOST,me,use->nick,txt);
	}
}

void coleen_deauth(User *use , message_irc *message)
{
	if(use->Access_Coleen & COLEEN_FLAGS_CSA)
	{
		set_csa(use,FALSE);
		set_geo(use,FALSE);
		set_ircop(use,FALSE);
		fsend_service(me,"\0034DEAUTH\0031 :\0034 %s \0031vient de se desidentifier",use->nick);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous etes maintenant desidentifié");
	}
}

void coleen_kill(User *use , message_irc *message)
{
	User *use2;
	char motif[MAXLEN];
	char txt[MAXLEN];
	int i = 2;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
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

	if(use2->option & IS_PROTECT)
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
	sprintf(txt,"[%s] Local kill by %s (%s)",myconfig->host,me,motif);
	fsend_service(me,FORMAT_KILL,me,use2->nick,txt);

	fsend_com(COM_SERV_SVSKILL,myconfig->host,use2->nick,txt,myconfig->host,me);
	del_user(use2->nick,motif);
}

void coleen_gline(User *use , message_irc *message)
{
	User *use2;
	char motif[MAXLEN];
	int i = 2;
	long t = time(NULL);
	long expire = 0;
	char *date_fr;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	if(!atoi(message->ARG[2]))
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

	if(use2->option & IS_PROTECT)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_PROTECT);
		return;
	}

	expire = t + atoi(message->ARG[2]);
	date_fr = time_fr(expire);

	
	if(!message->ARG[3])
	{
		strcpy(motif,"Vous etes le maillon faible , aurevoir");
	}
	else
	{
		i = 3;

		while(message->ARG[i])
		{
			if(i == 3)
				sprintf(motif,"%s",message->ARG[i]);
			else
				sprintf(motif,"%s %s",motif,message->ARG[i]);

			i++;
		}
	}

	/** finalise le motif a le pseudo de l'emeteur **/
	sprintf(motif,"%s par %s",motif,use->nick);

	fsend_com(LINK_TKL,myconfig->host,use2->host,me,expire,t,motif,date_fr);
	fsend_service(me,FORMAT_GLINE,use->nick,use2->host,motif);
	del_user(use2->nick,motif);

	FREE(date_fr);
}

void coleen_add_access(User *use , message_irc *message)
{
	Coleen_Access *access;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2] || !message->ARG[3])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	access = get_Coleen_Access(message->ARG[1]);
	if(access)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031D\xe9ol\xe9 , cet access est déjas en place !!");
		return;
	}

	if(!strcasecmp(message->ARG[3],"GEO"))
	{
		new_Coleen_Access(message->ARG[1],message->ARG[2],1,1);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031L'access a bien été ajouté , niveau CSA");
		save_Coleen_access();
		return;
	}

	if(!strcasecmp(message->ARG[3],"CSA"))
	{
		new_Coleen_Access(message->ARG[1],message->ARG[2],2,1);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031L'access a bien été ajouté , niveau CSA");
		save_Coleen_access();
		return;
	}

	if(!strcasecmp(message->ARG[3],"IRCOP"))
	{
		new_Coleen_Access(message->ARG[1],message->ARG[2],3,1);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031L'access a bien été ajouté , niveau IRCOP");
		save_Coleen_access();
		return;
	}

	help_on_error(use,message->ARG[0],me);
}

void deauth_user(char *nick)
{
	extern User *Alluser;
	User *use = Alluser;
	while(use)
	{
		if(!strcmp(use->Access_Coleen_pseudo,nick))
		{
			set_csa(use,FALSE);
			set_geo(use,FALSE);
			set_ircop(use,FALSE);
			fsend_service(me,"\0034DEAUTH\0031 :\0034 %s \0031vient de se desidentifier",use->nick);
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous etes maintenant desidentifié");
		}
		use = use->suivant;
	}
}


void coleen_suspend(User *use , message_irc *message)
{
	Coleen_Access *access;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	access = get_Coleen_Access(message->ARG[1]);
	if(!access)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	access->actif = 0;

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Cet Access est maintenant suspendu !!");

	deauth_user(access->nick);

	save_Coleen_access();
}

void coleen_reactive(User *use , message_irc *message)
{
	Coleen_Access *access;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	access = get_Coleen_Access(message->ARG[1]);
	if(!access)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	access->actif = 1;

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Cet Access est maintenant réactivé !!");

	save_Coleen_access();
}

void coleen_deluser(User *use , message_irc *message)
{
	Coleen_Access *access;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	access = get_Coleen_Access(message->ARG[1]);
	if(!access)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	deauth_user(access->nick);

	del_Coleen_Access(message->ARG[1]);

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Cet Access est maintenant supprimé !!");

	save_Coleen_access();
}

void coleen_say(User *use , message_irc *message)
{
	char txt[MAXLEN];
	int i = 2;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	else
	{
		i = 2;

		while(message->ARG[i])
		{
			if(i == 2)
				sprintf(txt,"%s",message->ARG[i]);
			else
				sprintf(txt,"%s %s",txt,message->ARG[i]);

			i++;
		}
	}
	fsend_com(LINK_COM_USER_PRIVMSG,me,message->ARG[1],txt);
}

void coleen_setpass(User *use , message_irc *message)
{
	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	Coleen_Access *access = get_Coleen_Access(message->ARG[1]);
	if(!access)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	FREE(access->pass);
	STRDUP(access->pass,message->ARG[2]);
	save_Coleen_access();
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Le pass de l'access a été modifié  !!");
}

void coleen_setaccess(User *use , message_irc *message)
{
	Coleen_Access *access;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	access = get_Coleen_Access(message->ARG[1]);
	if(!access)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	if(!strcasecmp(message->ARG[2],"GEO"))
	{
		access->niveau = 1;
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Le niveau de l'access a été modifié en GEO !!");
		save_Coleen_access();
		return;
	}

	if(!strcasecmp(message->ARG[2],"CSA"))
	{
		access->niveau = 2;
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Le niveau de l'access a été modifié en CSA !!");
		save_Coleen_access();
		return;
	}

	if(!strcasecmp(message->ARG[2],"IRCOP"))
	{
		access->niveau = 3;
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Le niveau de l'access a été modifié en IRCOP !!");
		save_Coleen_access();
		return;
	}
	help_on_error(use,message->ARG[0],me);
}

void coleen_accesslist(User *use , message_irc *message)
{

	Coleen_Access *access = pColeen_Access;
	char txt[MAXLEN];

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"*** Accesslist ***");

	while(access)
	{
		switch(access->niveau)
		{
			case 1:
				sprintf(txt,"\0034User\0031 : %s ,\0034 Niveau\0031 : %s ,\0034 Actif\0031 : %s",access->nick,"GEO",(access->actif == 1) ? "oui" : "non");
				break;

			case 2:
				sprintf(txt,"\0034User\0031 : %s ,\0034 Niveau\0031 : %s ,\0034 Actif\0031 : %s",access->nick,"CSA",(access->actif == 1) ? "oui" : "non");
				break;

			case 3:
				sprintf(txt,"\0034User\0031 : %s ,\0034 Niveau\0031 : %s ,\0034 Actif\0031 : %s",access->nick,"IRCOP",(access->actif == 1) ? "oui" : "non");
				break;	
		}
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		access = access->suivant;
	}

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"*** Accesslist Fin ***");
}

void coleen_op(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;
	UserList *utmp;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		if(!strcmp(utmp->use->nick,use2->nick))
		{
			fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"+o",utmp->use->nick);
			set_Mode_Status(chan , utmp->use->nick, 'o' , TRUE);
			fsend_service(me,FORMAT_MODE,me,"+o",utmp->use->nick, chan->chanName);
			return;
		}
		utmp = utmp->suivant;
	}
}

void coleen_deop(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;
	UserList *utmp;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		if(!strcmp(utmp->use->nick,use2->nick))
		{
			fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"-o",utmp->use->nick);
			set_Mode_Status(chan , utmp->use->nick, 'o' , FALSE);
			fsend_service(me,FORMAT_MODE,me,"-o",utmp->use->nick, chan->chanName);
			return;
		}
		utmp = utmp->suivant;
	}
}

void coleen_voice(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;
	UserList *utmp;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		if(!strcmp(utmp->use->nick,use2->nick))
		{
			fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"+v",utmp->use->nick);
			set_Mode_Status(chan , utmp->use->nick, 'v' , TRUE);
			fsend_service(me,FORMAT_MODE,me,"+v",utmp->use->nick, chan->chanName);
			return;
		}
		utmp = utmp->suivant;
	}
}

void coleen_devoice(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;
	UserList *utmp;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		if(!strcmp(utmp->use->nick,use2->nick))
		{
			fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"-v",utmp->use->nick);
			set_Mode_Status(chan , utmp->use->nick, 'v' , FALSE);
			fsend_service(me,FORMAT_MODE,me,"-v",utmp->use->nick, chan->chanName);
			return;
		}
		utmp = utmp->suivant;
	}
}

void coleen_half(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;
	UserList *utmp;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		if(!strcmp(utmp->use->nick,use2->nick))
		{
			fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"+h",utmp->use->nick);
			set_Mode_Status(chan , utmp->use->nick, 'h' , TRUE);
			fsend_service(me,FORMAT_MODE,me,"+h",utmp->use->nick, chan->chanName);
			return;
		}
		utmp = utmp->suivant;
	}
}

void coleen_dehalf(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;
	UserList *utmp;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		if(!strcmp(utmp->use->nick,use2->nick))
		{
			fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"-h",utmp->use->nick);
			set_Mode_Status(chan , utmp->use->nick, 'h' , FALSE);
			fsend_service(me,FORMAT_MODE,me,"-h",utmp->use->nick, chan->chanName);
			return;
		}
		utmp = utmp->suivant;
	}
}

void coleen_ungline(User *use , message_irc *message)
{
	Tkl *tkl = NULL;
	char *ident, *host, *host_, *p;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	tkl = get_tkl(message->ARG[1]);
	if(!tkl)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,HOST_INCONNU);
		return;
	}
		
	STRDUP(ident,tkl->mask);
	STRDUP(host,tkl->mask);
	host_ = host;
	p = strchr(ident,'@');
	if(p)
		*p = '\0';

	host_ += strlen(ident) + 1;
		
	fsend_service(me,FORMAT_UNGLINE,use->nick,tkl->mask);
	fsend_com(COM_SERV_UNGLINE,myconfig->host,ident,host_,me);

	FREE(ident);
	FREE(host);

	del_Tkl(tkl->mask);
}

void coleen_cleargline(User *use , message_irc *message)
{
	extern Tkl *pTkl;
	Tkl *tkl = pTkl;
	char *ident, *host, *host_, *p;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	while(tkl)
	{
		ident = host = host_ = p = NULL;

		STRDUP(ident,tkl->mask);
		STRDUP(host,tkl->mask);
		host_ = host;
		p = strchr(ident,'@');
		if(p)
			*p = '\0';

		host_ += strlen(ident) + 1;
		
		fsend_service(me,FORMAT_UNGLINE,use->nick,tkl->mask);
		fsend_com(COM_SERV_UNGLINE,myconfig->host,ident,host_,me);
		tkl = tkl->suivant;

		FREE(ident);
		FREE(host);
	}
	clear_Tkl();
	fsend_service(me,FORMAT_GLINECLEAR,use->nick);
}

void coleen_glinelist(User *use , message_irc *message)
{
	extern Tkl *pTkl;
	Tkl *tkl = pTkl;
	char txt[MAXLEN];

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	while(tkl)
	{
		sprintf(txt,FORMAT_GLINELIST,tkl->mask);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		tkl = tkl->suivant;
	}
}

void coleen_kick(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;
	char motif[MAXLEN];
	int i = 0;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}
	if(!message->ARG[3])
	{
		strcpy(motif,"Vous etes le maillon faible , aurevoir");
	}
	else
	{
		i = 3;

		while(message->ARG[i])
		{
			if(i == 3)
				sprintf(motif,"%s",message->ARG[i]);
			else
				sprintf(motif,"%s %s",motif,message->ARG[i]);

			i++;
		}
	}
	fsend_service(me,FORMAT_KICK,use->nick,use2->nick,chan->chanName,motif);
	fsend_com(LINK_COM_USER_KICK_RAI,myconfig->host ,chan->chanName,use2->nick,motif);
	user_part(chan->chanName ,use2);
}

void coleen_sajoin(User *use , message_irc *message)
{
	User *use2;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	fsend_com(LINK_COM_OPER_SAJOIN,myconfig->host,use2->nick,message->ARG[1]);

	fsend_service(me,FORMAT_SVSJOIN, use->nick,use2->nick,message->ARG[1]);
}

void coleen_sapart(User *use , message_irc *message)
{
	User *use2;
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	use2 = get_user(message->ARG[2]);
	if(!use2)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}

	fsend_com(LINK_COM_OPER_SAPART,myconfig->host,use2->nick,chan->chanName);

	fsend_service(me,FORMAT_SVSPART, use->nick,use2->nick,chan->chanName);
}

void coleen_swhois(User *use , message_irc *message)
{
	User *use2;
	char txt[MAXLEN];
	char *t;

	if(!(use->Access_Coleen & COLEEN_FLAGS_IRCOP))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
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

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Information sur %s :",use2->nick);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Host : %s!%s@%s",use2->nick,use2->handle,use2->host);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	t = listclone(use2);
	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Ses Clones : %s",t);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
	FREE(t);

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Vhost : %s!%s@%s",use2->nick,use2->handle,use2->vhost);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 RealName : %s",use2->real);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Serveur : %s",use2->server);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Adresse ip : %s",use2->ip);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Protection : %s",(use2->option & IS_PROTECT) ? "Oui" : "Non");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Clone Service : %s",(use2->option & IS_CLONE) ? "Oui" : "Non");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	t = list_Mode_User(use2);
	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Flags : %s",t);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
	FREE(t);

	t = time_fr(use2->Ctime);
	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Connecté depuis le : %s",t);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
	FREE(t);

	t = time_fr(use2->Ltime);
	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Inactif depuis le : %s",t);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
	FREE(t);

	if(use->Access_Coleen)
	{
		sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Auth %s avec le login : %s",me,use2->Access_Coleen_pseudo);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

		if((use2->Access_Coleen & COLEEN_FLAGS_IRCOP))
		{
			sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Niveau d'access sur %s : IRCOP",me);
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
			goto CHAN;
		}
		if((use2->Access_Coleen & COLEEN_FLAGS_CSA))
		{
			sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Niveau d'access sur %s : CSA",me);
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
			goto CHAN;
		}
		if((use2->Access_Coleen & COLEEN_FLAGS_GEO))
		{
			sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 Niveau d'access sur %s : GEO",me);
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		}
	}
CHAN:
	t = chanList(use2);
	sprintf(txt,"\0038[\0034 SWHOIS \0038]\0031 ChanList : %s",t);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
	FREE(t);

	return;
}

void coleen_mop(User *use , message_irc *message)
{
	UserList *utmp;
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"+o",utmp->use->nick);
		set_Mode_Status(chan , utmp->use->nick, 'o' , TRUE);
		fsend_service(me,FORMAT_MODE,me,"+o",utmp->use->nick, chan->chanName);

		utmp = utmp->suivant;
	}
}

void coleen_mdeop(User *use , message_irc *message)
{
	UserList *utmp;
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"-o",utmp->use->nick);
		set_Mode_Status(chan , utmp->use->nick, 'o' , FALSE);
		fsend_service(me,FORMAT_MODE,me,"-o",utmp->use->nick, chan->chanName);

		utmp = utmp->suivant;
	}
}

void coleen_mvoice(User *use , message_irc *message)
{
	UserList *utmp;
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"+v",utmp->use->nick);
		set_Mode_Status(chan , utmp->use->nick, 'v' , TRUE);
		fsend_service(me,FORMAT_MODE, chan->chanName,"+v",utmp->use->nick,me);

		utmp = utmp->suivant;
	}
}

void coleen_mdevoice(User *use , message_irc *message)
{
	UserList *utmp;
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"-v",utmp->use->nick);
		set_Mode_Status(chan , utmp->use->nick, 'v' , FALSE);
		fsend_service(me,FORMAT_MODE,me,"-v",utmp->use->nick, chan->chanName);

		utmp = utmp->suivant;
	}
}

void coleen_mhalf(User *use , message_irc *message)
{
	UserList *utmp;
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"+h",utmp->use->nick);
		set_Mode_Status(chan , utmp->use->nick, 'h' , TRUE);
		fsend_service(me,FORMAT_MODE,me,"+h",utmp->use->nick, chan->chanName);

		utmp = utmp->suivant;
	}
}

void coleen_mdehalf(User *use , message_irc *message)
{
	UserList *utmp;
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
		return;
	}

	utmp = chan->usercourant;
	while(utmp)
	{
		fsend_com(LINK_COM_USER_MODE_USE,myconfig->host ,chan->chanName,"-h",utmp->use->nick);
		set_Mode_Status(chan , utmp->use->nick, 'h' , FALSE);
		fsend_service(me,FORMAT_MODE,me,"-h",utmp->use->nick, chan->chanName);

		utmp = utmp->suivant;
	}
}

void coleen_mkick(User *use , message_irc *message)
{
	Channel *chan;
	UserList *utmp;
	char motif[MAXLEN];
	int i = 0;

	if(!(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_IDENTNO);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(!chan)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
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

	utmp = chan->usercourant;
	while(utmp)
	{
		if(!(utmp->use->option & IS_PROTECT))
		{
			fsend_service(me,FORMAT_KICK,use->nick,utmp->use->nick,chan->chanName,motif);
			fsend_com(LINK_COM_USER_KICK_RAI,myconfig->host ,chan->chanName,utmp->use->nick,motif);
			user_part(chan->chanName ,utmp->use);
			utmp = chan->usercourant;
			continue;
		}
		utmp = utmp->suivant;
	}
}

