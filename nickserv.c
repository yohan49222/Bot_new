#include "main.h"

extern Config *myconfig;

Nick_Resa *Allnickresa = NULL;

static char *me = "NickServ";

void init_nickserv()
{
	if(get_clone(me))
		return;

	new_clone(me,myconfig->flags,myconfig->real,NULL);

	load_db_nickserv();

	Create_Raw_Bot("CONNECT"	,&NICKSERV_CONNECT	,me);
	Create_Raw_Bot("NICK"		,&NICKSERV_NICK		,me);
	Create_Raw_Bot("PRIVMSG"  	,&NICKSERV_PRIVMSG	,me);
	Create_Raw_Bot("KILL"  		,&NICKSERV_KILL		,me);
	Create_Raw_Bot("KICK"  		,&NICKSERV_KICK		,me);

	Create_Com("help" , me, &nickserv_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");
	Create_Com("identify" , me, &nickserv_identify ,"?","/msg %s IDENTIFY <pass>","Permet de s'indentifer comme prorietaire de votre pseudo");
	Create_Com("register" , me, &nickserv_register ,"?","/msg %s REGISTER <pass> <email>","Permet d'enregistrer votre pseudo actuel et d'en devenir propriétaire");
	Create_Com("drop" , me, &nickserv_drop ,"?","/msg %s DROP <pseudo> <pass>","Permet de supprimer l'enregistrement de votre pseudo");
	Create_Com("ghost" , me, &nickserv_ghost ,"?","/msg %s GHOST <pseudo> <pass>","Permet de déconnecter un utilisateur fantome ayant votre pseudo réservé");
	Create_Com("sendpass" , me, &nickserv_sendpass ,"?","/msg %s SENDPASS","Permet de récupérer votre pass , et de le recevoir dans votre boite email");
	Create_Com("setpass" , me, &nickserv_setpass ,"?","/msg %s SETPASS motdepass","Permet de modifier votre pass");
	Create_Com("setmail" , me, &nickserv_setmail ,"?","/msg %s SETMAIL email","Permet de modifier votre email");

	new_timer(100000,86400,&savebd_nick_resa,"NICKSERVSAVEBD","NICKSERVSAVEBD");
}

void load_db_nickserv()
{
	FILE *db;
	Nick_Resa *tmp;
	char ligne[512];
	char *nick , *pass, *email, *vhost, *p;
	long expire, score;

	db = fopen("base/nickserv.db", "r");
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
			email = strtok(NULL, ":");
			vhost = strtok(NULL, ":");
			expire = atol( strtok(NULL, ":") );
			score = atol( strtok(NULL, "\n") );
			tmp = new_nickresa(nick,pass,email,vhost,expire,score);
		}
	}
	fclose(db);

	fsend_service(me,CHAR_BD_OK,"Pseudo R\xe9serv\xe9");

}

void unload_nickserv()
{
	clear_nickresa();
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}

void savebd_nick_resa()
{
	extern Nick_Resa *Allnickresa;
	FILE *db;
	Nick_Resa *tmp;
	Nick_Resa *tmp2;
	long t;
	char buffer[1024];
	t = time(NULL);
	tmp = Allnickresa;

	db = fopen("base/nickserv.db", "w");
	if(!db)
	{
		fsend_service(me,"\0034Erreur\0031 : Impossible d'ouvrir BD NickServ");
		return;
	}
	while(tmp)
	{
		if(t < tmp->expire)
		{
			fprintf(db,"%s:%s:%s:%s:%ld:%ld\n",tmp->nick,tmp->pass,tmp->email,tmp->vhost,tmp->expire,tmp->point_jeux);
			tmp = tmp->suivant;
		}
		else
		{
			sprintf(buffer,"\0034Expire\0031 : la r\xe9servation du pseudo\0033 %s \0031a expir\xe9",tmp->nick);
			send_service(me,buffer);
			tmp2 = tmp->suivant;
			del_nickresa(tmp->nick);
			tmp = tmp2;
		}

	}
	fclose(db);
	fsend_service(me,SAVE_BD_OK,"Pseudo R\xe9serv\xe9");
}

/**
	*********************************
	** Gestions des nicks reserve **
	*********************************
**/

Nick_Resa *new_nickresa(char *nick,char *pass,char *email,char *vhost,long expire,long score)
{
	Nick_Resa *resaSuivant;
	char vhost_tmp[256] = "";

	if(!*nick || !*pass || !*email)
		return NULL;

	resaSuivant = (Nick_Resa*)malloc(sizeof(Nick_Resa));
	if(!resaSuivant)
		return NULL;

	STRDUP(resaSuivant->nick,nick);
	STRDUP(resaSuivant->pass,pass);
	STRDUP(resaSuivant->email,email);

	if(vhost)
	{
		STRDUP(resaSuivant->vhost,vhost)
	}
	else
	{
		sprintf(vhost_tmp,"%s%s",nick,myconfig->hostc);
		STRDUP(resaSuivant->vhost,vhost_tmp)
	}

	if(expire)
		resaSuivant->expire = expire;
	else
		resaSuivant->expire = time(NULL) + 2592000 ;

	resaSuivant->point_jeux = score;

	fsend_service(me,FORMAT_NEWRESA,nick);

	resaSuivant->precedent = NULL;
	resaSuivant->suivant = Allnickresa;
	if (Allnickresa)
    	Allnickresa->precedent = resaSuivant;
	Allnickresa = resaSuivant;
	return Allnickresa;

}

int del_nickresa(char *nick)
{
	Nick_Resa *nickresa;
	nickresa = Allnickresa;
	while (nickresa)
	{
		if(strcasecmp(nickresa->nick,nick) == 0)
		{
			if(nickresa->suivant)
				nickresa->suivant->precedent = nickresa->precedent;

			if(nickresa->precedent)
				nickresa->precedent->suivant = nickresa->suivant;

			if(nickresa == Allnickresa)
				Allnickresa = nickresa->suivant;

			FREE(nickresa->nick);
			FREE(nickresa->pass);
			FREE(nickresa->email);
			FREE(nickresa->vhost);
			FREE(nickresa);

			return 1;
		}
		nickresa = nickresa->suivant;
	}
	return 0;
}

int clear_nickresa()
{
	Nick_Resa *nickresa;
	while (Allnickresa)
	{
		nickresa = Allnickresa;
		Allnickresa = Allnickresa->suivant;
		FREE(nickresa->nick);
		FREE(nickresa->pass);
		FREE(nickresa->email);
		FREE(nickresa->vhost);
		FREE(nickresa);
		nickresa = NULL;
	}
	Allnickresa = NULL;
	return 1;
}

long Nick_Resa_t()
{
	int count = 0;

	Nick_Resa *u;
	u = Allnickresa;
	while (u)
	{
		count++;
		u = u->suivant;
	}
	return sizeof(Nick_Resa) * (count+1);
}

Nick_Resa *get_nickresa(char *nick)
{
	Nick_Resa *use;
	use = Allnickresa;
	while(use)
	{
		if(strcasecmp(use->nick,nick) == 0)
			return use;

		use = use->suivant;
	}
	return NULL;
}

/**
	Raw nickserv
**/

void NICKSERV_PRIVMSG(message_irc *message)
{
	printf("NICKSERV_PRIVMSG\n");

	if(strcasecmp(message->RAW[2],me))
		return;


	User *use = get_user(message->RAW[0]);
	if(!use)
		return;


	executeCom( use, message , me);
}

void NICKSERV_CONNECT(message_irc *message)
{
	printf("NICKSERV_CONNECT\n");
	char txt[MAXLEN];

	User *use = get_user(message->RAW[1]);
	if(!use)
		return;

	if(get_clone(use->nick))
		return;

	Nick_Resa *nickresa = get_nickresa(message->RAW[1]);
	if(!nickresa)
	{
		sprintf(txt,"\0031Votre pseudo %s n'est pas enregistr\xe9, si vous souhaitez en devenir propri\xe9taire , taper :\002 /msg %s REGISTER <pass> <email>",use->nick,me);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		return;
	}
	fsend_service(me,FORMAT_ISRESA,message->RAW[1]);

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Ce nick est enregistr\xe9 et prot\xe9g\xe9 Si c'est votre nick,");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031tapez\002 /msg NickServ IDENTIFY motdepasse.");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Sinon, veuillez choisir un nick diff\xe9rent.");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Si vous ne changez pas d'ici\0033 30 \0031secondes, je changerais votre nick.");

	if(timer_existe(use->nick , "IDENT"))
		del_Timer(use->nick , "IDENT");

	new_timer(1 , 30, &verif_ident , use->nick , "IDENT");

}

void NICKSERV_NICK(message_irc *message)
{
	printf("NICKSERV_NICK\n");

	fsend_service(me,FORMAT_NICK,message->RAW[0],message->RAW[2]);

	User *use = get_user(message->RAW[2]);
	if(!use)
		return;

	if(is_Capable(use,'r'))
	{
		set_flag(use,me, 'r' , FALSE);
		fsend_com(COM_SERV_SVSMODE,myconfig->host,use->nick,"-r");
		fsend_service(me,FORMAT_SVSMODE,me,"-r",use->nick);
	}
	if(timer_existe(message->RAW[0] , "IDENT"))
		del_Timer(message->RAW[0], "IDENT");

	Nick_Resa *nickresa = get_nickresa(message->RAW[2]);
	if(!nickresa)
		return;

	fsend_service(me,FORMAT_ISRESA,message->RAW[2]);

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Ce nick est enregistr\xe9 et prot\xe9g\xe9 Si c'est votre nick,");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031tapez\002 /msg NickServ IDENTIFY motdepasse.");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Sinon, veuillez choisir un nick diff\xe9rent.");
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Si vous ne changez pas d'ici\0033 30 \0031secondes, je changerais votre nick.");

	new_timer(1 , 30, &verif_ident , use->nick , "IDENT" );
}

void NICKSERV_KILL(message_irc *message)
{
	printf("NICKSERV_KILL\n");
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
	}
}

void NICKSERV_KICK(message_irc *message)
{
	printf("NICKSERV_KICK\n");
	if(!strcasecmp(message->RAW[3],me))
	{
		bot_join(me, message->RAW[2] , "+v");
	}
}

/**
	commandes nickserv
**/

void nickserv_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void nickserv_identify(User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	Nick_Resa *nickresa = get_nickresa(use->nick);
	if(!nickresa)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Votre pseudo n'est pas encore reservé");
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031tapez\002 /msg NickServ REGISTER motdepasse email.");
		return;
	}

	
	if(strcmp(message->ARG[1],nickresa->pass))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le mot de pass indiqu\xe9 ne correspond pas");
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031tapez\002 /msg NickServ IDENTIFY motdepasse.");
		return;
	}

	set_flag(use,me, 'r' , TRUE);
	fsend_com(COM_SERV_SVSMODE,myconfig->host,use->nick,"+r");

	fsend_service(me,FORMAT_OKRESA,nickresa->nick);

	fsend_service(me,FORMAT_SVSMODE,me,"+r",nickresa->nick);
	
	if(strcmp(use->vhost,nickresa->vhost))
	{
		set_vhost(use->nick , nickresa->vhost,me);
		fsend_com(LINK_COM_OPER_CHGHOST,myconfig->host,use->nick,nickresa->vhost);
		fsend_service(me,FORMAT_CHGVHOST,me,nickresa->nick,nickresa->vhost);
	}

	nickresa->expire = time(NULL) + 2592000;

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous etes maintenant identifi\xe9, bon t'chat a vous !!");

	if(timer_existe(use->nick , "IDENT"))
		del_Timer(use->nick , "IDENT");

	
}

void nickserv_register(User *use , message_irc *message)
{
	char txt[MAXLEN];

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	Nick_Resa *nickresa = get_nickresa(use->nick);
	if(nickresa)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Votre pseudo est d\xe9ja reserv\xe9");
		return;
	}

	sprintf(txt,"%s%s",use->nick,myconfig->hostc);
	nickresa = new_nickresa(use->nick,message->ARG[1],message->ARG[2],txt,time(NULL) + 2592000,0);

	savebd_nick_resa();

	set_flag(use,me, 'r' , TRUE);
	fsend_com(COM_SERV_SVSMODE,myconfig->host,use->nick,"+r");

	fsend_service(me,FORMAT_OKRESA,nickresa->nick);

	fsend_service(me,FORMAT_SVSMODE,me,"+r",nickresa->nick);

	if(strcmp(use->vhost,nickresa->vhost))
	{
		set_vhost(use->nick , nickresa->vhost,me);
		fsend_com(LINK_COM_OPER_CHGHOST,myconfig->host,use->nick,nickresa->vhost);
		fsend_service(me,FORMAT_CHGVHOST,me,nickresa->nick,nickresa->vhost);
	}


	sprintf(txt,"\0031A l'avenir , a chaque demande d'identification de %s taper :\002 /msg %s IDENTIFY %s",me,me,nickresa->pass);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);

	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous etes maintenant identifi\xe9, bon t'chat a vous !!");

}

void nickserv_drop(User *use , message_irc *message)
{
	User *userbis = NULL;

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	Nick_Resa *nickresa = get_nickresa(message->ARG[1]);
	if(!nickresa)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le pseudo indiqu\xe9 n'est pas reserv\xe9");
		return;
	}

	if(strcmp(nickresa->pass,message->ARG[2]))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le mot de pass indiqu\xe9 ne correspond pas");
		return;
	}

	del_nickresa(nickresa->nick);
	fsend_service(me,FORMAT_DELRESA,use->nick,message->ARG[1]);
	savebd_nick_resa();

	userbis = get_user(message->ARG[1]);
	if(userbis && is_Capable(userbis,'r'))
	{
		set_flag(userbis,me, 'r' , FALSE);
		fsend_com(COM_SERV_SVSMODE,myconfig->host,userbis->nick,"-r");
		fsend_service(me,FORMAT_SVSMODE,me,"-r",userbis->nick);


		fsend_com(LINK_COM_USER_NOTICE,me,userbis->nick,"\0031Vous n'avez plus de pseudo r\xe9serv\xe9 !!");
	}

	if(strcmp(use->nick,message->ARG[1]))
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le pseudo n'est plus r\xe9serv\xe9 !!");
}

void nickserv_ghost(User *use , message_irc *message)
{
	User *userbis = NULL;
	char motif[200];

	if(!message->ARG[1] || !message->ARG[2])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	
	if(!strcmp(use->nick,message->ARG[1]))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous ne pouvez pas utiliser la commande GHOST sur vous meme");
		return;
	}

	Nick_Resa *nickresa = get_nickresa(message->ARG[1]);
	if(!nickresa)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le pseudo indiqu\xe9 n'est pas reserv\xe9 ");
		return;
	}

	if(strcmp(nickresa->pass,message->ARG[2]))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Le mot de pass indiqu\xe9 ne correspond pas");
		return;
	}

	userbis = get_user(message->ARG[1]);
	if(!userbis)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,USER_INCONNU);
		return;
	}
	fsend_service(me,FORMAT_GHOST,use->nick,userbis->nick);

	sprintf(motif,"%s (GHOST command used by %s)",me,use->nick);
	fsend_com(COM_SERV_SVSKILL,myconfig->host,userbis->nick,motif);
}

int sendmail(Nick_Resa *nickresa)
{
	FILE *mail;

	mail = popen("/usr/sbin/sendmail -t", "w");
	if(!mail)
		return 0;

	fprintf( mail, "From: %s\r\n", "services@localhost.net");
	fprintf( mail, "To: \"%s\" <%s>\r\n", nickresa->nick, nickresa->email);
	fprintf( mail, "Subject: Mail de %s pour votre pseudo %s\n",me,nickresa->nick);
	fprintf( mail, "MIME-Version: 1.0\n" );
	fprintf( mail, "Content-type: text/plain; charset=ISO-8859-15\n" );
	fprintf( mail, "Content-Transfer-Encoding: 7bit\n" );
	fprintf( mail, "X-Mailer: Sendmail\n\n" );
	fprintf( mail, "Vous avez demand\x9e a recevoir votre pass\002 %s \002 , pour le pseudo\002 %s \002.\n\n", me,nickresa->nick);
	fprintf( mail, "Votre pass est :\002 %s \002.\n\n", nickresa->pass);
	fprintf( mail, "Pour vous identifier , taper /msg %s IDENTIFY \002 %s \002\n\n", me,nickresa->pass);
	fprintf( mail, "Bonne journee\n\n" );
	pclose(mail);
	return 1;
}

void nickserv_sendpass(User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	Nick_Resa *nickresa = get_nickresa(message->ARG[1]);
	if(!nickresa)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Ce pseudo n'est pas enregistr\xe9.");
		return;
	}

	if(sendmail(nickresa))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Le pass vous a \xe9t\xe9 envoy\xe9 par email");
	}
	else
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Erreur d'envois du mail");
	}
}

void nickserv_setpass(User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}


	if(!is_Capable(use,'r'))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous devez etre identifi\xe9 pour modifier votre pass.");
		return;
	}

	Nick_Resa *nickresa = get_nickresa(use->nick);
	if(!nickresa)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Votre pseudo n'est pas enregistr\xe9.");
		return;
	}

	FREE(nickresa->pass);
	STRDUP(nickresa->pass,message->ARG[1]);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Votre pass a été modifie.");
	fsend_service(me,FORMAT_REGPASS,use->nick);
	savebd_nick_resa();
}

void nickserv_setmail(User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}


	if(!is_Capable(use,'r'))
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031Vous devez etre identifi\xe9 pour modifier votre email.");
		return;
	}

	Nick_Resa *nickresa = get_nickresa(use->nick);
	if(!nickresa)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Votre pseudo n'est pas enregistr\xe9.");
		return;
	}

	FREE(nickresa->email);
	STRDUP(nickresa->email,message->ARG[1]);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"Votre email a été modifie.");
	fsend_service(me,FORMAT_REGMAIL,use->nick,nickresa->email);
	savebd_nick_resa();
}



void verif_ident(char *nick)
{
	char newn[50];
	long t;
	int i = my_rand(50000);

	User *use = get_user(nick);
	if(!use)
		return;

	if(is_Capable(use,'r'))
		return;

	t = time(NULL);
	sprintf(newn,"UrbanRadio%d", i );
	fsend_com(COM_SERV_SVSNICK,myconfig->host,nick,newn,t);

	if(!get_clone(nick))
	{
		new_timer(1 , 2, &conn_protect , nick , "CONNPROTECT" );

		new_timer(1 , 60, &deco_protect , nick , "DECOPROTECT" );
	}
}

void conn_protect(char *nick)
{
	new_clone(nick,NULL,myconfig->real,NULL);
}

void deco_protect(char *nick)
{
	del_clone(nick,"Protection nick timeout");
}









