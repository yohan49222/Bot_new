#include "main.h"

extern Config *myconfig;

static char *me = "MassToolZ";

Channel_Off_Reg *pChannel_Off_Reg = NULL;
Channel_Prive_Close *pChannel_Prive_Close = NULL;
/** Variable d'activation **/
int close_actif = 0;


/**
	fonction masstoolz
**/

void init_masstoolz()
{
	User *use;
	if(get_clone(me))
		return;

	use = new_clone(me,myconfig->flags,myconfig->real,NULL);
	if(!use)
		return;
	
	Create_Raw_Bot("JOIN"  		,&MASSTOOLZ_JOIN		,me);
	Create_Raw_Bot("PART"  		,&MASSTOOLZ_PART		,me);
	Create_Raw_Bot("EOS"  		,&MASSTOOLZ_EOS			,me);
	Create_Raw_Bot("PRIVMSG"  	,&MASSTOOLZ_PRIVMSG		,me);
	Create_Raw_Bot("KILL"  		,&MASSTOOLZ_KILL		,me);
	Create_Raw_Bot("KICK"  		,&MASSTOOLZ_KICK		,me);

	Create_Com("help" , me, &masstoolz_help ,"?","/msg %s HELP [<command>]" ,"Permet de voir la liste des commandes , et si [<command>] est sp�cifi� , affiche le detail de cette commande");
	Create_Com("close" , me, &masstoolz_com_close ,"?","/msg %s CLOSE <channel>" ,"Permet de fermer un salon Priv\xe9 uniquement");
	Create_Com("unclose" , me, &masstoolz_com_unclose ,"?","/msg %s UNCLOSE <channel>" ,"Permet de r�ouvrir un salon Ferm\xe9");
	Create_Com("synchro" , me, &masstoolz_com_synchro ,"?","/msg %s SYNCHRO" ,"Permet de resynchroniser la bd des channels officiels apres un unreg");

	load_db_masstoolz();
	
}

void unload_masstoolz()
{
	del_command(me);
	del_Raw_Bot(me);
	del_clone(me,"Aurevoir tout le monde");
}

void masstoolz_close(Channel *chan)
{
	UserList *Utmp;

	User *use = get_user(me);
	if(!use)
		return;

	fsend_com(LINK_COM_USER_JOIN,use->nick,chan->chanName);
	fsend_service(use->nick,FORMAT_JOIN,use->nick,chan->chanName);
	user_join(chan->chanName,use);
	fsend_com(LINK_COM_USER_MODE,use->nick,chan->chanName,"+snti");
	fsend_service(use->nick,FORMAT_MODE,chan->chanName,"+snti",use->nick);

	set_Mode_Chan(chan,'s',TRUE);
	set_Mode_Chan(chan,'n',TRUE);
	set_Mode_Chan(chan,'t',TRUE);
	set_Mode_Chan(chan,'i',TRUE);

	set_Mode_Status(chan,use->nick,'o', TRUE);
	fsend_com(LINK_COM_USER_MODE_USE,myconfig->botnick,chan->chanName,"+o",use->nick);
	fsend_service(myconfig->botnick,FORMAT_MODE,use->nick,"+o",use->nick ,chan->chanName);

	Utmp = chan->usercourant;
	while(Utmp)
	{
		if(!(Utmp->use->option & IS_PROTECT))
		{
			fsend_service(use->nick,"\0034CLOSE\0031 :\0033 %s \0031, kick de\0034 %s \0034: Channel Ferm\xe9",chan->chanName,Utmp->use->nick);
			fsend_com(LINK_COM_USER_KICK_RAI,myconfig->host ,chan->chanName,Utmp->use->nick,"Channel Ferm\xe9 ");

			Utmp = user_part(chan->chanName,Utmp->use);
			continue;
		}
		else
		{
			fsend_service(use->nick,"\0034CLOSE\0031 :\0033 %s \0031, impossible de kicker\0034 %s \0031: \0034user prot\xe9g\xe9" ,chan->chanName,Utmp->use->nick);
		}
		Utmp = Utmp->suivant;
	}
}

void masstoolz_unclose(Channel *chan)
{
	User *use = get_user(me);
	if(!use)
		return;

	fsend_com(LINK_COM_USER_MODE,use->nick,chan->chanName,"-si");
	fsend_service(use->nick,FORMAT_MODE,chan->chanName,"-si",use->nick);
	fsend_com(LINK_COM_USER_PART,use->nick,chan->chanName);
	fsend_service(use->nick,FORMAT_PART ,use->nick,chan->chanName);
	user_part(chan->chanName,use);

	set_Mode_Chan(chan,'s',FALSE);
	set_Mode_Chan(chan,'i',FALSE);
}

/**
	Raw masstoolz
**/

#define FORMAT_JOIN_OFF 		"\0034JOIN\0031 : %s rejoin %s , Ce chan est enregist\xe9"
#define FORMAT_JOIN_NONOFF 		"\0034JOIN\0031 : %s rejoin %s , Ce chan n'est pas enregist\xe9"
#define FORMAT_ADD_CHAN 		"\0034REG\0031 : %s vient d'etre enregist\xe9"

void MASSTOOLZ_PRIVMSG(message_irc *message)
{
	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	if(strcasecmp(message->RAW[2],me))
		return;

	executeCom( use, message , me);
}

void MASSTOOLZ_JOIN(message_irc *message)
{
	Channel_Off_Reg *chan;
	char *chanlist ,*ptr;

	if(!strcasecmp(message->RAW[0],"Proxima1"))
	{
		STRDUP(chanlist,message->RAW[2]);
		ptr = strtok(chanlist,",");
		while( ptr != NULL)
		{
			if(match("#!*!",ptr))
			{
				chan = get_Channel_Off_Reg(ptr);
				if(!chan)
				{
					fsend_service(me,FORMAT_JOIN_NONOFF, message->RAW[0],ptr);
					fsend_service(me,FORMAT_ADD_CHAN, message->RAW[0],ptr);
					add_Channel_Off_Reg(ptr);
				}
				else
				{
					fsend_service(me,FORMAT_JOIN_OFF, message->RAW[0],ptr);
				}
			}
			ptr = strtok(NULL,",");
		}
	}

	if(!close_actif)
		return;

	User *use = get_user("Proxima1");
	if(!use)
		return;

	if(strcasecmp(message->RAW[0],"Proxima1"))
	{
		STRDUP(chanlist,message->RAW[2]);
		ptr = strtok(chanlist,",");
		while( ptr != NULL)
		{
			if(!strcmp(ptr,myconfig->service))
			{
				ptr = strtok(NULL,",");
				continue;
			}

			if(match("#!*!",ptr))
			{
				chan = get_Channel_Off_Reg(ptr);
				if(chan)
				{
					fsend_service(me,FORMAT_JOIN_OFF, message->RAW[0],ptr);
				}
				else
				{
					Channel *channel = get_channel(ptr);
					if(channel)
					{
						fsend_service(me,FORMAT_JOIN_NONOFF, message->RAW[0],channel->chanName);
						masstoolz_close(channel);
					}
				}
			}
			ptr = strtok(NULL,",");
		}
	}
}

void MASSTOOLZ_PART(message_irc *message)
{
	char txt[MAXLEN];
	extern User *Alluser;
	User *use = Alluser;

	if(strcasecmp(message->RAW[0],"Proxima1"))
		return;

	sprintf(txt,"Proxima1 est parti d'un salon , si il sagit d'un UNREG , merci de taper /msg %s SYNCHRO",me);

	/**
		envois a tous les ircops
	**/
	while(use)
	{
		if(is_Capable(use,'o'))
		{
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
			use = use->suivant;
			continue;
		}

		if(strcmp(use->Access_Coleen_pseudo,"?"))
		{
			fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		}
		use = use->suivant;
	}

}

void MASSTOOLZ_EOS(message_irc *message)
{
	extern Channel *Allchan;
	Channel *chan = Allchan;
	User *use = get_user("Proxima1");

	save_bd_masstoolz();

	close_actif = 1;

	while(chan)
	{

		if(!strcmp(chan->chanName,myconfig->service))
		{
			chan = chan->suivant;
			continue;
		}

		if(use && chan->is_Off)
		{
			if(!is_onchan(chan,use))
			{
				masstoolz_close(chan);
			}
		}

		if(get_Channel_Prive_Close(chan->chanName))
		{
			masstoolz_close(chan);
		}

		chan = chan->suivant;
	}

}

void MASSTOOLZ_KILL(message_irc *message)
{
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
		MASSTOOLZ_EOS(NULL);
	}
}

void MASSTOOLZ_KICK(message_irc *message)
{
	if(!strcasecmp(message->RAW[3],me))
	{
		bot_join(me, message->RAW[2] , "+v");
	}
}

/**
	commandes masstoolz
**/	

void masstoolz_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void masstoolz_com_synchro(User *use , message_irc *message)
{
	extern Channel *Allchan;
	extern char *coleen_pseudo;
	char txt[MAXLEN];
	Channel *chan = Allchan;

	User *user = get_user("Proxima1");
	if(!user)
		return;

	if(!(use->Access_Coleen & COLEEN_FLAGS_CSA) && !(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		sprintf(txt,"\0031Vous n'etes pas identifi\xe9 sur\0034 %s",coleen_pseudo);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		return;
	}


	/** vide la liste des channel enregistre **/
	clear_Channel_Off_Reg();


	while(chan)
	{
		/** si le channel est un officiel **/
		if(chan->is_Off)
		{
			/**
				si Proxima1 n'est pas sur le channel
				et que le channel n'est pas le channel de service
			**/
			if(!is_onchan(chan,user) && strcmp(chan->chanName,myconfig->service))
			{
				/* Fermeture du channel */
				masstoolz_close(chan);
			}

			/**
				si Proxima1 est pas sur le channel
				et que le channel n'est pas le channel de service
			**/
			if(is_onchan(chan,user) && strcmp(chan->chanName,myconfig->service))
			{
				/* enregistrement du channel */
				add_Channel_Off_Reg(chan->chanName);
			}
		}
		chan = chan->suivant;
	}
	save_bd_masstoolz();
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,"\0031La liste des Channels officiels a ete mise a jour");
}

void masstoolz_com_close(User *use , message_irc *message)
{
	extern char *coleen_pseudo;
	char txt[MAXLEN];
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_CSA) && !(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		sprintf(txt,"\0031Vous n'etes pas identifi\xe9 sur\0034 %s",coleen_pseudo);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	if(match("#!*!",message->ARG[1]))
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	chan = get_channel(message->ARG[1]);
	if(chan)
	{
		masstoolz_close(chan);
		add_Channel_Prive_Close(chan->chanName);
		save_bd_masstoolz();
	}
	else
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
}

void masstoolz_com_unclose(User *use , message_irc *message)
{
	extern char *coleen_pseudo;
	char txt[MAXLEN];
	Channel *chan;

	if(!(use->Access_Coleen & COLEEN_FLAGS_CSA) && !(use->Access_Coleen & COLEEN_FLAGS_GEO))
	{
		sprintf(txt,"\0031Vous n'etes pas identifi\xe9 sur\0034 %s",coleen_pseudo);
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
		return;
	}

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	
	chan = get_channel(message->ARG[1]);
	if(chan)
	{
		masstoolz_unclose(chan);
		del_Channel_Prive_Close(chan->chanName);
		save_bd_masstoolz();
	}
	else
		fsend_com(LINK_COM_USER_NOTICE,me,use->nick,CHAN_INCONNU);
}

/**
	gestion des channel Off Enregistre
**/

void load_db_masstoolz()
{
	FILE *myFile;
	char ligne[256];
	char *var = NULL;
	char *p;

	clear_Channel_Off_Reg();
	clear_Channel_Prive_Close();

	myFile = fopen("base/chanoff.db", "r");
	if(!myFile)
		goto PRIVE;

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

			var = strtok(ligne , "\n");

			if(var)
				add_Channel_Off_Reg(var);

		}
	}

	fclose(myFile);
	fsend_service(me,CHAR_BD_OK,"Chans Officiels");
	

PRIVE:
	myFile = fopen("base/chanclose.db", "r");
	if(!myFile)
		return;

	while(fgets(ligne, sizeof ligne, myFile))
	{
		if( strlen(ligne) > 1 )
		{
			p = strchr(ligne, '\n');
			if(p)
				*p = '\0';

			p = strchr(ligne, '\r');
			if(p)
				*p = '\0';

			var = strtok(ligne , "\n");

			if(var)
				add_Channel_Prive_Close(var);
		}
	}
	fclose(myFile);
	fsend_service(me,CHAR_BD_OK,"Chans Priv\xe9 Ferm\xe9");
}

void save_bd_masstoolz()
{
	FILE *myFile;
	Channel_Off_Reg *chan = pChannel_Off_Reg;
	Channel_Prive_Close *chan_ = pChannel_Prive_Close;

	myFile = fopen("base/chanoff.db", "w");
	if(!myFile)
		goto CLOSE;

	while(chan)
	{
		fprintf(myFile,"%s\n",chan->name);
		chan = chan->suivant;
	}
	fclose(myFile);
	fsend_service(me,SAVE_BD_OK,"Chans Officiels");


CLOSE:
	myFile = fopen("base/chanclose.db", "w");
	if(!myFile)
		return;

	while(chan_)
	{
		fprintf(myFile,"%s\n",chan_->name);
		chan_ = chan_->suivant;
	}
	fclose(myFile);
	fsend_service(me,SAVE_BD_OK,"Chans Priv\xe9 Ferm\xe9");
}


Channel_Off_Reg *add_Channel_Off_Reg(char *name)
{
	Channel_Off_Reg *chan = (Channel_Off_Reg*)malloc(sizeof(Channel_Off_Reg));
	if(!chan)
		return NULL;

	if(!name || !*name)
	{
		FREE(chan);
		return NULL;
	}
	STRDUP(chan->name,name);

	chan->precedent = NULL;
	chan->suivant = pChannel_Off_Reg;
	if (pChannel_Off_Reg)
    		pChannel_Off_Reg->precedent = chan;
	pChannel_Off_Reg = chan;
	return pChannel_Off_Reg;
}

int del_Channel_Off_Reg(char *name)
{
	Channel_Off_Reg *chan = get_Channel_Off_Reg(name);
	if(!chan)
		return 0;

	if(chan->suivant)
		chan->suivant->precedent = chan->precedent;

	if(chan->precedent)
		chan->precedent->suivant = chan->suivant;

	if(chan == pChannel_Off_Reg)
		pChannel_Off_Reg = chan->suivant;

	FREE(chan->name);
	FREE(chan);

	return 1;
}

Channel_Off_Reg *get_Channel_Off_Reg(char *name)
{
	Channel_Off_Reg *chan = pChannel_Off_Reg;
	while(chan)
	{
		if(!strcasecmp(chan->name,name))
			return chan;

		chan = chan->suivant;
	}
	return NULL;
}

int clear_Channel_Off_Reg()
{
	Channel_Off_Reg *chan;
	while (pChannel_Off_Reg)
	{
		chan = pChannel_Off_Reg;
		pChannel_Off_Reg = pChannel_Off_Reg->suivant;
		FREE(chan->name);
		FREE(chan);
		chan = NULL;
	}
	pChannel_Off_Reg = NULL;
	return 1;
}



Channel_Prive_Close *add_Channel_Prive_Close(char *name)
{
	Channel_Prive_Close *chan;

	chan = (Channel_Prive_Close*)malloc(sizeof(Channel_Prive_Close));
	if(!chan)
		return NULL;

	if(!name || !*name)
	{
		FREE(chan);
		return NULL;
	}

	STRDUP(chan->name,name);

	chan->precedent = NULL;
	chan->suivant = pChannel_Prive_Close;
	if (pChannel_Prive_Close)
    		pChannel_Prive_Close->precedent = chan;
	pChannel_Prive_Close = chan;
	return pChannel_Prive_Close;
}

int del_Channel_Prive_Close(char *name)
{
	Channel_Prive_Close *chan = get_Channel_Prive_Close(name);
	if(!chan)
		return 0;

	if(chan->suivant)
		chan->suivant->precedent = chan->precedent;

	if(chan->precedent)
		chan->precedent->suivant = chan->suivant;

	if(chan == pChannel_Prive_Close)
		pChannel_Prive_Close = chan->suivant;

	FREE(chan->name);
	FREE(chan);

	return 1;
}

Channel_Prive_Close *get_Channel_Prive_Close(char *name)
{
	Channel_Prive_Close *chan = pChannel_Prive_Close;
	while(chan)
	{
		if(!strcasecmp(chan->name,name))
			return chan;

		chan = chan->suivant;
	}
	return NULL;
}

int clear_Channel_Prive_Close()
{
	Channel_Prive_Close *chan;
	while (pChannel_Prive_Close)
	{
		chan = pChannel_Prive_Close;
		pChannel_Prive_Close = pChannel_Prive_Close->suivant;
		FREE(chan->name);
		FREE(chan);
		chan = NULL;
	}
	pChannel_Prive_Close = NULL;
	return 1;
}








