
#include "main.h"
extern Config *myconfig;

Quizz *quizz = NULL;
Quizz_Base *pQuizz_Base = NULL;


void init_jeux_quizz()
{
	quizz = (Quizz*)malloc(sizeof(Quizz));
	if(!quizz)
		return;

	Create_Raw("PRIVMSG"  	,&p_RAW_QUIZZ);
	Create_Raw("JOIN"		,&p_RAW_JOIN_QUIZZ);
	Create_Com("help"		,QUIZZ,	&help,			2,NULL,0);
	Create_Com("quizz"	,QUIZZ,  &lance_quizz,	1,NULL,0);
	Create_Com("stop"		,QUIZZ,	&stop_quizz,		1,NULL,0);	
	init_quizz();

	quizz->tirage = NULL;
}

void init_quizz()
{
	FILE *myFile;
	char ligne[10000];
	char *ptr,*ptr2;
	char *p;
	if((myFile= fopen("base/Liste_Quizz.db", "r")) != NULL)
	{
		while(fgets(ligne, sizeof ligne, myFile))
		{
			if( strlen(ligne) > 1 )
			{
				p = strchr(ligne, '\n');
				if (p)
				{
					*p = '\0';
				}
				ptr = strtok(ligne,"|");
				ptr2 = strtok(NULL,"\n");
				add_quizz_base(ptr,ptr2);
			}
		}
		fclose(myFile);
	}
	else
	{
		fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,"Impossible de lancer le Quizz");
		
	}
}

void add_quizz_base(char *question, char *reponse)
{
	Quizz_Base *nQuizz;
	nQuizz = (Quizz_Base*)malloc(sizeof(Quizz_Base));
	if(!nQuizz)
		return;

	quizz->tirage_max++;

	Remplacer(question,"_"," ");
	Remplacer(reponse,"_"," ");
	retire_accent(reponse);

	strcpy(nQuizz->question,question);
	strcpy(nQuizz->reponse,reponse);
	
	nQuizz->precedent = NULL;
	nQuizz->suivant = pQuizz_Base;
	if (pQuizz_Base)
    	pQuizz_Base->precedent = nQuizz;
	pQuizz_Base = nQuizz;
}

void lance_quizz(message_irc *message)
{
	char txt[MAXLEN];

	if(message) 
		if(strcmp(message->RAW[2],CHANNELQUIZZ))
			return;

	quizz->tirage_vide++;
	while(quizz->tirage == NULL)
		quizz->tirage = new_tirage_quizz();

	sprintf(txt,ANNONCEQUESTION,quizz->tirage->question);
	fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,txt);

	new_timer(1,30,&quizz_mi_temp,"QUIZZ");
}

void lance_quizz2()
{
	char txt[MAXLEN];
	quizz->tirage_vide++;

	quizz->tirage = NULL;

	while(quizz->tirage == NULL)
		quizz->tirage = new_tirage_quizz();

	sprintf(txt,ANNONCEQUESTION,quizz->tirage->question);
	fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,txt);
	new_timer(1,30,&quizz_mi_temp,"QUIZZ");
}

Quizz_Base *new_tirage_quizz()
{
	int x;
	Quizz_Base *qui;
	qui = pQuizz_Base;
	x = my_rand(quizz->tirage_max);
	while(qui)
	{
		if(!x--)
			return qui;

		qui = qui->suivant;
	}
	return NULL;
}

void quizz_mi_temp()
{
	char txt[MAXLEN];
	sprintf(txt,MI_TEMPS_QUIZZ);
	fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,txt);
	new_timer(1,30,&quizz_expire,"QUIZZ");
}

void quizz_expire()
{
	char txt[MAXLEN];
	quizz->tirage_vide++;

	sprintf(txt,EXPIRE_TEMPS_QUIZZ,quizz->tirage->reponse);
	fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,txt);

	quizz->tirage = NULL;

	if(quizz->tirage_vide < 10)
	{
		new_timer(1,30,&lance_quizz2,"QUIZZ");
		fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ :BOTNICK,CHANNELQUIZZ,NEW_TIRAGE_IN_QUIZZ);
	}
	else
		stop_quizz(NULL);
}

void stop_quizz(message_irc *message)
{
	char txt[MAXLEN];

	if(message)
	{

		if(strcmp(message->RAW[2],CHANNELQUIZZ))
			return;

		del_Timer("QUIZZ");

		sprintf(txt,QUIZZ_TERMINE,get_source(message->RAW[0],1));
		fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,txt);
	
	}
	else
	{
		fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,PUBQUIZZ);
	}

	quizz->tirage = NULL;
}

void p_RAW_QUIZZ(message_irc *message)
{
	/*
		:<source> PRIVMSG <target> :<message string>
	*/
	char *messtemp;
	char *messtemp_;

	if(message->message == NULL || !quizz->tirage) 
		return;

	if(strcmp(message->RAW[2],CHANNELQUIZZ))
		return;

	quizz->tirage_vide = 0;

	messtemp = strdup(message->message);
	retirecouleur(messtemp,messtemp);

	messtemp_ = messtemp;

	while(*messtemp == ' ')
		messtemp_++;

	if(!strcasecmp(quizz->tirage->reponse,messtemp_))
	{
		find_reponse_quizz(message);
	}
	free(messtemp);
}

void p_RAW_JOIN_QUIZZ(message_irc *message)
{
	if(strcmp(message->RAW[2],CHANNELQUIZZ))
		return;

	if(quizz->tirage)
		return;

	fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,PUBQUIZZ);
}

void find_reponse_quizz(message_irc *message)
{
	Nick_Resa *resa;
	char txt[MAXLEN];
	resa = get_nickresa(get_source(message->RAW[0],1));
	if(!resa)
	{
		fsend_com(LINK_COM_USER_NOTICE,QUIZZ ? QUIZZ : BOTNICK,get_source(message->RAW[0],1),"Vous ne pouvez pas jouer sans un pseudo reserv\xe9");
		return;
	}

	del_Timer("QUIZZ");
	resa->point_jeux += 10;

	sprintf(txt,GAGNANT,resa->nick,10);
	fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,txt);
	fsend_com(LINK_COM_USER_PRIVMSG,QUIZZ ? QUIZZ : BOTNICK,CHANNELQUIZZ,NEW_TIRAGE_IN_QUIZZ);

	quizz->tirage = NULL;
	new_timer(1,30,&lance_quizz2,"QUIZZ");
}

void retire_accent(char *phrase)
{
	Remplacer(phrase,"&#xA0;","\xA0");
	Remplacer(phrase,"&#xA1;","\xA1");
	Remplacer(phrase,"&#xA2;","\xA2");
	Remplacer(phrase,"&#xA3;","\xA3");
	Remplacer(phrase,"&#xA4;","\xA4");
	Remplacer(phrase,"&#xA5;","\xA5");
	Remplacer(phrase,"&#xA6;","\xA6");
	Remplacer(phrase,"&#xA7;","\xA7");
	Remplacer(phrase,"&#xA8;","\xA8");
	Remplacer(phrase,"&#xA9;","\xA9");
	Remplacer(phrase,"&#xAA;","\xAA");
	Remplacer(phrase,"&#xAB;","\xAB");
	Remplacer(phrase,"&#xAC;","\xAC");
	Remplacer(phrase,"&#xAD;","\xAD");
	Remplacer(phrase,"&#xAE;","\xAE");
	Remplacer(phrase,"&#xAF;","\xAF");
	Remplacer(phrase,"&#xB0;","\xB0");
	Remplacer(phrase,"&#xB1;","\xB1");
	Remplacer(phrase,"&#xB2;","\xB2");
	Remplacer(phrase,"&#xB3;","\xB3");
	Remplacer(phrase,"&#xB4;","\xB4");
	Remplacer(phrase,"&#xB5;","\xB5");
	Remplacer(phrase,"&#xB6;","\xB6");
	Remplacer(phrase,"&#xB7;","\xB7");
	Remplacer(phrase,"&#xB8;","\xB8");
	Remplacer(phrase,"&#xB9;","\xB9");
	Remplacer(phrase,"&#xBA;","\xBA");
	Remplacer(phrase,"&#xBB;","\xBB");
	Remplacer(phrase,"&#xBC;","\xBC");
	Remplacer(phrase,"&#xBD;","\xBD");
	Remplacer(phrase,"&#xBE;","\xBE");
	Remplacer(phrase,"&#xBF;","\xBF");
	Remplacer(phrase,"&#xC0;","\xC0");
	Remplacer(phrase,"&#xC1;","\xC1");
	Remplacer(phrase,"&#xC2;","\xC2");
	Remplacer(phrase,"&#xC3;","\xC3");
	Remplacer(phrase,"&#xC4;","\xC4");
	Remplacer(phrase,"&#xC5;","\xC5");
	Remplacer(phrase,"&#xC6;","\xC6");
	Remplacer(phrase,"&#xC7;","\xC7");
	Remplacer(phrase,"&#xC8;","\xC8");
	Remplacer(phrase,"&#xC9;","\xC9");
	Remplacer(phrase,"&#xCA;","\xCA");
	Remplacer(phrase,"&#xCB;","\xCB");
	Remplacer(phrase,"&#xCC;","\xCC");
	Remplacer(phrase,"&#xCD;","\xCD");
	Remplacer(phrase,"&#xCE;","\xCE");
	Remplacer(phrase,"&#xCF;","\xCF");
	Remplacer(phrase,"&#xD0;","\xD0");
	Remplacer(phrase,"&#xD1;","\xD1");
	Remplacer(phrase,"&#xD2;","\xD2");
	Remplacer(phrase,"&#xD3;","\xD3");
	Remplacer(phrase,"&#xD4;","\xD4");
	Remplacer(phrase,"&#xD5;","\xD5");
	Remplacer(phrase,"&#xD6;","\xD6");
	Remplacer(phrase,"&#xD7;","\xD7");
	Remplacer(phrase,"&#xD8;","\xD8");
	Remplacer(phrase,"&#xD9;","\xD9");
	Remplacer(phrase,"&#xDA;","\xDA");
	Remplacer(phrase,"&#xDB;","\xDB");
	Remplacer(phrase,"&#xDC;","\xDC");
	Remplacer(phrase,"&#xDD;","\xDD");
	Remplacer(phrase,"&#xDE;","\xDE");
	Remplacer(phrase,"&#xDF;","\xDF");
	Remplacer(phrase,"&#xE0;","\xE0");
	Remplacer(phrase,"&#xE1;","\xE1");
	Remplacer(phrase,"&#xE2;","\xE2");
	Remplacer(phrase,"&#xE3;","\xE3");
	Remplacer(phrase,"&#xE4;","\xE4");
	Remplacer(phrase,"&#xE5;","\xE5");
	Remplacer(phrase,"&#xE6;","\xE6");
	Remplacer(phrase,"&#xE7;","\xE7");
	Remplacer(phrase,"&#xE8;","\xE8");
	Remplacer(phrase,"&#xE9;","\xE9");
	Remplacer(phrase,"&#xEA;","\xEA");
	Remplacer(phrase,"&#xEB;","\xEB");
	Remplacer(phrase,"&#xEC;","\xEC");
	Remplacer(phrase,"&#xED;","\xED");
	Remplacer(phrase,"&#xEE;","\xEE");
	Remplacer(phrase,"&#xEF;","\xEF");
	Remplacer(phrase,"&#xF0;","\xF0");
	Remplacer(phrase,"&#xF1;","\xF1");
	Remplacer(phrase,"&#xF2;","\xF2");
	Remplacer(phrase,"&#xF3;","\xF3");
	Remplacer(phrase,"&#xF4;","\xF4");
	Remplacer(phrase,"&#xF5;","\xF5");
	Remplacer(phrase,"&#xF6;","\xF6");
	Remplacer(phrase,"&#xF7;","\xF7");
	Remplacer(phrase,"&#xF8;","\xF8");
	Remplacer(phrase,"&#xF9;","\xF9");
	Remplacer(phrase,"&#xFA;","\xFA");
	Remplacer(phrase,"&#xFB;","\xFB");
	Remplacer(phrase,"&#xFC;","\xFC");
	Remplacer(phrase,"&#xFD;","\xFD");
	Remplacer(phrase,"&#xFE;","\xFE");
	Remplacer(phrase,"&#xFF;","\xFF");
	Remplacer(phrase,"&#x26;","\x26");
	Remplacer(phrase,"&#x27;","\x27");
	Remplacer(phrase,"&#x3C;","\x3C");
	Remplacer(phrase,"&#x3E;","\x3E");
	Remplacer(phrase,"&#x92;","\x92");
	Remplacer(phrase,"&equiv;","=");
	return ;
}

