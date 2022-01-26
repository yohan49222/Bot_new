#include "main.h"

extern Config *myconfig;

Com_IN *pCom_IN = NULL;

/**
	creation d'une commande 
**/
Com_IN *Create_Com( char *name , char *bot, myFuncComPtr func ,char *flag,char *exemple,char *desc)
{
	Com_IN *nCom = (Com_IN*)malloc(sizeof(Com_IN));
	if(!nCom)
		return NULL;

	if(!name || !bot || !func)
	{
		FREE(nCom);
		return NULL;
	}

	STRDUP(nCom->ComName,name)
	STRDUP(nCom->ComBot,bot)

	nCom->func = func;

	if(flag)
	{
		STRDUP(nCom->ComFlag,flag)
	}
	else
	{
		STRDUP(nCom->ComFlag,"?")
	}

	if(exemple)
	{
		STRDUP(nCom->exemple,exemple)
	}
	else
	{
		STRDUP(nCom->exemple,"?")
	}

	if(desc)
	{
		STRDUP(nCom->desc,desc)
	}
	else
	{
		STRDUP(nCom->desc,"?")
	}


	nCom->precedent = NULL;
	nCom->suivant = pCom_IN;
	if (pCom_IN)
    	pCom_IN->precedent = nCom;
	pCom_IN = nCom;

	return pCom_IN;
}

/**
	Destruction de toutes les commandes , tout bot confondus
**/
int clear_command()
{
	Com_IN *nCom;
	while (pCom_IN)
	{
		nCom = pCom_IN;
		pCom_IN = pCom_IN->suivant;
		FREE(nCom->ComName);
		FREE(nCom->ComBot);
		FREE(nCom->ComFlag);
		FREE(nCom->exemple);
		FREE(nCom->desc);
		FREE(nCom);
		nCom = NULL;
	}
	pCom_IN = NULL;
	return 1;
}

/**
	Destruction de toutes les commandes appartenant au bot specifie
**/
int del_command(char *botname)
{
	Com_IN *com = pCom_IN;
	while(com)
	{
		if(!strcmp(com->ComBot,botname))
		{
			if(com->suivant)
				com->suivant->precedent = com->precedent;

			if(com->precedent)
				com->precedent->suivant = com->suivant;

			if(com == pCom_IN)
				pCom_IN = com->suivant;

			FREE(com->ComName);
			FREE(com->ComBot);
			FREE(com->ComFlag);
			FREE(com->exemple);
			FREE(com->desc);
			FREE(com);
			com = pCom_IN;
			continue;
		}
		com = com->suivant;
	}
	return 1;
}


long Com_IN_t()
{
	int count = 0;

	Com_IN *u;
	u = pCom_IN;
	while (u)
	{
		count++;
		u = u->suivant;
	}
	return sizeof(Com_IN) * (count+1);
}

/**
	fonction qui verifie si l'user a droit a la commande
**/
int is_valide(User *use , Com_IN *command)
{
	char c;
	char *flag = command->ComFlag;

	/* verification de l'access suivant les flags serveur */
	if(flag[0] != '?')
	{
		while((c = *flag++))
		{
			if(is_Capable(use,c))
			{
				return 1;
			}
		}
	}
	else
		return 1;

	/* envois du message de refus de commande a l'use */
	fsend_com(LINK_COM_USER_NOTICE,command->ComBot,use->nick,"D�sole , mais tu n'a pas le droit a cette commande");
 	return 0;
}

/**
	fonction qui verifie si l'use dispose du flag 'ch'
**/
int is_Capable(User *user,char ch)
{
	switch(ch)
	{
		case'A':if(user->ModeGlobMaj & U_MODE_A) return 1;break;
		case'B':if(user->ModeGlobMaj & U_MODE_B) return 1;break;
		case'C':if(user->ModeGlobMaj & U_MODE_C) return 1;break;
		case'D':if(user->ModeGlobMaj & U_MODE_D) return 1;break;
		case'G':if(user->ModeGlobMaj & U_MODE_G) return 1;break;
		case'H':if(user->ModeGlobMaj & U_MODE_H) return 1;break;
		case'K':if(user->ModeGlobMaj & U_MODE_K) return 1;break;
		case'L':if(user->ModeGlobMaj & U_MODE_L) return 1;break;
		case'N':if(user->ModeGlobMaj & U_MODE_N) return 1;break;
		case'O':if(user->ModeGlobMaj & U_MODE_O) return 1;break;
		case'R':if(user->ModeGlobMaj & U_MODE_R) return 1;break;
		case'S':if(user->ModeGlobMaj & U_MODE_S) return 1;break;
		case'T':if(user->ModeGlobMaj & U_MODE_T) return 1;break;
		case'V':if(user->ModeGlobMaj & U_MODE_V) return 1;break;
		case'W':if(user->ModeGlobMaj & U_MODE_W) return 1;break;
		case'X':if(user->ModeGlobMaj & U_MODE_X) return 1;break;
		case'Z':if(user->ModeGlobMaj & U_MODE_Z) return 1;break;

		case'a':if(user->ModeGlobMin & U_MODE_a) return 1;break;
		case'b':if(user->ModeGlobMin & U_MODE_b) return 1;break;
		case'c':if(user->ModeGlobMin & U_MODE_c) return 1;break;
		case'd':if(user->ModeGlobMin & U_MODE_d) return 1;break;
		case'g':if(user->ModeGlobMin & U_MODE_g) return 1;break;
		case'h':if(user->ModeGlobMin & U_MODE_h) return 1;break;
		case'i':if(user->ModeGlobMin & U_MODE_i) return 1;break;
		case'k':if(user->ModeGlobMin & U_MODE_k) return 1;break;
		case'n':if(user->ModeGlobMin & U_MODE_n) return 1;break;
		case'o':if(user->ModeGlobMin & U_MODE_o) return 1;break;
		case'p':if(user->ModeGlobMin & U_MODE_p) return 1;break;
		case'q':if(user->ModeGlobMin & U_MODE_q) return 1;break;
		case'r':if(user->ModeGlobMin & U_MODE_r) return 1;break;
		case's':if(user->ModeGlobMin & U_MODE_s) return 1;break;
		case't':if(user->ModeGlobMin & U_MODE_t) return 1;break;
		case'v':if(user->ModeGlobMin & U_MODE_v) return 1;break;
		case'w':if(user->ModeGlobMin & U_MODE_w) return 1;break;
		case'x':if(user->ModeGlobMin & U_MODE_x) return 1;break;
		case'z':if(user->ModeGlobMin & U_MODE_z) return 1;break;
	}
	return 0;
}


/**
	fonction qui execute la commande demande
**/
int executeCom(  User *use , message_irc *message , char *botnick)
{
	Com_IN *myCom = pCom_IN;
	char *t;

	if(!message->ARG[0])
		return 0;

	while(myCom)
	{
		if(!strcasecmp(myCom->ComName, message->ARG[0]) && !strcasecmp(myCom->ComBot, botnick))
		{
			if(!use)
				return 1;

			set_Ltime(use->nick);

			if(myCom->ComFlag[0] != '?')
				if(!is_valide(use , myCom))
					return 1;

			t = list_Mode_User(use);
			fsend_service(myCom->ComBot,USING_COMMANDE,use->nick,myCom->ComName,myCom->ComFlag,t);
			FREE(t);
			myCom->func(use,message);
		}
		myCom = myCom->suivant;
	}
	return 1;
}

/**
	fonction qui affiche l'aide de la commande sur demande de use
**/
void help(User *use,message_irc *message,char *botnick)
{
	Com_IN *com;
	char txt[MAXLEN];
	memset(txt,0,MAXLEN);
	int compteur = 0;

	if(message->ARG[1])
	{
		com = pCom_IN;
		while(com)
		{
			if(!strcasecmp(com->ComName,message->ARG[1]) && !strcasecmp(com->ComBot,botnick) )
			{
				if(com->ComFlag && com->ComFlag[0] != '?')
				{
					sprintf(txt,"\0031La Commande \0034%s \0031 require les Flags :\0034 %s",com->ComName,com->ComFlag);
					fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
				}
				if(com->exemple && *com->exemple)
				{
					sprintf(txt,com->exemple,botnick);
					fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
				}
				else
				{
					sprintf(txt,"\0031La Commande \0034%s \0031 n'a pas d'exemple",com->ComName);
					fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
				}
				if(com->desc && *com->desc)
				{
					sprintf(txt,com->desc);
					fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
				}
				else
				{
					sprintf(txt,"\0031La Commande \0034%s \0031 n'a pas de description",com->ComName);
					fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
				}
			}
			com = com->suivant;
		}
	}
	else
	{
		sprintf(txt,"\0031Liste des Commandes \0034 %s \0031:",botnick);
		fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);

		com = pCom_IN;
		while(com)
		{
			if(!strcasecmp(com->ComBot,botnick) )
			{
				if(!compteur)
				{
					sprintf(txt,"\0033[ \0034%s \0033]",com->ComName);
					compteur++;
				}
				else
				{
					sprintf(txt,"%s \0031- \0033[ \0034%s \0033]", txt,com->ComName);
					compteur++;

					if(compteur == 4)
					{
						fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
						compteur = 0;
					}
				}
			}
			com = com->suivant;
		}
		if(compteur)
		{
			fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
		}

		sprintf(txt,"\0031Taper \0034 /msg %s HELP <commande> \0031pour voir l'aide d\xe9taill\xe9",botnick);
		fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
	}
}

/**
	fonction qui affiche l'aide de la commande sur une erreur de parametre
**/
void help_on_error(User *use,char *commande,char *botnick)
{
	Com_IN *com;
	char txt[MAXLEN];
	memset(txt,0,MAXLEN);

	com = pCom_IN;
	while(com)
	{
		if(!strcasecmp(com->ComName,commande) && !strcasecmp(com->ComBot,botnick) )
		{
			if(com->ComFlag && com->ComFlag[0] != '?')
			{
				sprintf(txt,"\0031La Commande \0034%s \0031 require les Flags :\0034 %s",com->ComName,com->ComFlag);
				fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
			}
			if(com->exemple && *com->exemple)
			{
				sprintf(txt,com->exemple,botnick);
				fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
			}
			else
			{
				sprintf(txt,"\0031La Commande \0034%s \0031 n'a pas d'exemple",com->ComName);
				fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
			}
			if(com->desc && *com->desc)
			{
				sprintf(txt,com->desc);
				fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
			}
			else
			{
				sprintf(txt,"\0031La Commande \0034%s \0031 n'a pas de description",com->ComName);
				fsend_com(LINK_COM_USER_NOTICE,botnick,use->nick,txt);
			}
		}
		com = com->suivant;
	}
}


