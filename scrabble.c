#include "main.h"

extern Config *myconfig;

static char *me = "ScRaBiDoO";

Mot_Base *pMot_Base = NULL;
Reponse *pReponse = NULL;
Possible *pPossible = NULL;
Base_Quizz *pBase_Quizz = NULL;
Pseudo_Jeux *pPseudo_Jeux = NULL;

#define CHANNELSCRABBLE "#!JeuX!"

static int count_lettre = 10;
static int jeux_actif = 0;

static int nMot = 0;
static int maxlen = 0;
static int xMot_Maxlen = 0;
static Pseudo_Jeux *gagnant;
static int point_courant;
static int tirage_vide = 0;
static int nQuestion = 0;
static Base_Quizz *Question_tire = NULL;
static int Scrabble_type = 1;

/**
	initialisation du robot
**/
void init_jeux()
{
	/**
		verifie que ce clone n'est pas dejas chargé
	**/
	if(get_clone(me))
	{
		put_log("tentative de duplication du bot de jeux");
		return;
	}

	/**
		creation du clone
	**/
	User *use = new_clone(me,"ixw",myconfig->real,NULL);
	if(!use)
	{
		put_log("creation bot de jeux echoué");
		return;
	}

	/**
		creation des commandes
	**/
	Create_Com("!help" , me, &scrabble_help ,"?","!HELP" ,"Permet de voir la liste des commandes , et si [<command>] est spécifié , affiche le detail de cette commande");


	Create_Com("!stop" , me, &jeux_stop ,"?","!STOP" ,"Permet stoper le jeux");
	Create_Com("!score" , me, &jeux_score ,"?","!SCORE " ,"Permet stoper le jeux");
	Create_Com("!top10" , me, &jeux_top10 ,"?","!TOP10" ,"Permet de voir le top10");
 
	Create_Com("!mynick" , me, &jeux_mynick ,"?","!MYNICK <pseudo>" ,"Permet de mofifier modifier votre pseudo de jeux");

	/**
		creation des raws
	**/
	Create_Raw_Bot("JOIN"  		,&JEUX_JOIN		,me);
	Create_Raw_Bot("PRIVMSG"  	,&JEUX_PRIVMSG		,me);
	Create_Raw_Bot("KILL"  		,&JEUX_KILL 		,me);
	Create_Raw_Bot("KICK"  		,&JEUX_KICK 		,me);


	/**
		chargement de la liste de mot
	**/
	if(load_db_scabble())
	{
		Create_Com("!scrabble",me, &scrabble_lance ,"?","!SCRABBLE" ,"Permet demarrer le scrabble");
		Create_Com("!type" , me, &scrabble_type ,"?","!type <1|2> " ,"Permet changer le type de scrabble , 1 pour longueur des mots et 2 pour valeur des lettres");
		Create_Com("!setlettre" , me, &scrabble_set_count ,"?","!SETLETTRE < 10 <-> 15 >","Permet de mofifier le nombre de lettre tiree au scrabble");
	}

	/**
		chargement de la bd pour le quizz
	**/
	if(load_db_quizz())
	{
		Create_Com("!quizz" , me, &quizz_lance ,"?","!QUIZZ" ,"Permet demarrer le quizz");

	}
	/**
		chargement de le bd des scores
	**/
	load_db_score();

	/** 
		rejoin #!JeuX!
	**/
	bot_join(me, CHANNELSCRABBLE , "+v");
}

/**
	dechargement du robot
**/
void unload_jeux()
{
	jeux_actif = 0;				/** mise a zero du jeux actif **/
	save_db_score();			/** savegarde des scores **/
	clear_Pseudo_Jeux();			/** vide la liste des scores **/
	clear_question_quizz();			/** lide la liste des question quizz **/
	clear_mot_base();			/** vide la liste des mots scrabble **/
	clear_possible();			/** lide la liste des poss scrabble **/
	clear_reponse();			/** lide la liste des repo scrabble **/
	del_command(me);			/** destruction des commandes du bot **/
	del_Raw_Bot(me);			/** destruction des raws du bot **/
	del_clone(me,"Aurevoir tout le monde");	/** destruction et quit du bot **/
	del_Timer("SCRABBLE","SCRABBLE");	/** destruction du timer **/
}

/**
	Chargement de la liste des scrores
**/
void load_db_score()
{
	FILE *myFile;
	char ligne[200];
	char *nick,*score,*p;

	myFile = fopen("base/score.db", "r");
	if(!myFile)
		return;

	while(fgets(ligne, sizeof ligne, myFile))
	{
		if( strlen(ligne) > 1 )
		{
			p = strchr(ligne, '\n');
			if(p)
				*p = '\0';
	
			nick = strtok(ligne, ":");
			score = strtok(NULL, ":");
			
			if(nick && score)
				add_Pseudo_Jeux(nick,atoi(score));
		}
	}

	fclose(myFile);
	fsend_service(me,CHAR_BD_OK,"Score Jeux");
	
}

void save_db_score()
{
	Pseudo_Jeux *pseudo = pPseudo_Jeux;
	FILE *myFile = fopen("base/score.db", "w");
	if(!myFile)
		return;

	while(pseudo)
	{
		fprintf(myFile,"%s:%d:\n",pseudo->nick,pseudo->point_jeux);
		pseudo = pseudo->suivant;
	}

	fclose(myFile);
	fsend_service(me,SAVE_BD_OK,"Score Jeux");
}

Pseudo_Jeux *add_Pseudo_Jeux(char *nick,int score)
{
	Pseudo_Jeux *n = (Pseudo_Jeux*)malloc(sizeof(Pseudo_Jeux));
	if(!n)
		return NULL;

	STRDUP(n->nick,nick);
	n->point_jeux = score;

	n->precedent = NULL;
	n->suivant = pPseudo_Jeux;
	if (pPseudo_Jeux)
    	pPseudo_Jeux->precedent = n;
	pPseudo_Jeux = n;

	return pPseudo_Jeux;
}

void clear_Pseudo_Jeux()
{
	Pseudo_Jeux *n;
	while (pPseudo_Jeux)
	{
		n = pPseudo_Jeux;
		pPseudo_Jeux = pPseudo_Jeux->suivant;
		FREE(n->nick);
		FREE(n);
		n = NULL;
	}
	pPseudo_Jeux = NULL;
}

Pseudo_Jeux *get_Pseudo_Jeux(char *nick)
{
	Pseudo_Jeux *n = pPseudo_Jeux;
	while(n)
	{
		if(!strcasecmp(n->nick,nick))
			return n;

		n = n->suivant;
	}
	return NULL;
}

void set_score(char *nick,int add)
{
	Pseudo_Jeux *n = get_Pseudo_Jeux(nick);
	if(n)
		n->point_jeux += add;
	else
		add_Pseudo_Jeux(nick,add);
}

/**
	raw scrabble
**/
void JEUX_PRIVMSG(message_irc *message)
{

	if(strcmp(message->RAW[2],CHANNELSCRABBLE))
		return;

	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	executeCom( use, message , me);

	if(!message->ARG[0])
		return;

	switch(jeux_actif)
	{
		case 1:
			find_scrabble(message);
			break;

		case 2:
			find_quizz(message);
			break;

	}
}

void JEUX_JOIN(message_irc *message)
{
	if(strcmp(message->RAW[2],CHANNELSCRABBLE))
		return;

	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBSCRABBLE_SCRABBLE);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBQUIZZ_QUIZZ);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,YOUR_NICK_JEUX);
}

void JEUX_KILL(message_irc *message)
{
	if(!strcasecmp(message->RAW[2],me))
	{
		del_clone(me,"Aurevoir tout le monde");
		new_clone(me,myconfig->flags,myconfig->real,NULL);
		bot_join(me, CHANNELSCRABBLE , "+v");
	}
}

void JEUX_KICK(message_irc *message)
{
	if(!strcasecmp(message->RAW[3],me))
		bot_join(me, message->RAW[2] , "+v");
}

/**
	commande scrabble
**/
void scrabble_help(User *use , message_irc *message)
{
	help(use,message,me);
}

void scrabble_lance(User *use , message_irc *message)
{
	if(jeux_actif)
		return;

	jeux_actif = 1;
	lance_scrabble();
}

void scrabble_type(User *use , message_irc *message)
{
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	if(*message->ARG[1] != '1' && *message->ARG[1] != '2')
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	del_Timer("SCRABBLE","SCRABBLE");
	stop_jeux(message);
	jeux_actif = 0;
	close_scrabble();

	if(*message->ARG[1] == '1')
	{
		Scrabble_type = 1;
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,SCRABBLE_ANNONCE_TYPE1);
		return;
	}
	if(*message->ARG[1] == '2')
	{
		Scrabble_type = 2;
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,SCRABBLE_ANNONCE_TYPE2);
		return;
	}

	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBSCRABBLE_SCRABBLE);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBQUIZZ_QUIZZ);
}

void scrabble_set_count(User *use , message_irc *message)
{
	int x = 0;
	char txt[MAXLEN];
	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	x = atoi(message->ARG[1]);
	if( x <= 0)
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}

	if(x >= 10 && x <= 15)
	{
		sprintf(txt,"\0038,1\002[\0034 SCRABBLE \0038]\0030 Le nombre de lettre tiree au scrabble passe maintenant a\0034 %d \0030.",x);
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
		count_lettre = x;
	}
	else
	{
		help_on_error(use,message->ARG[0],me);
	}
		
}

void quizz_lance(User *use , message_irc *message)
{
	if(jeux_actif)
		return;

	jeux_actif = 2;
	lance_quizz();
}

void jeux_stop(User *use , message_irc *message)
{
	del_Timer("SCRABBLE","SCRABBLE");

	switch(jeux_actif)
	{
		case 1:
			stop_jeux(message);
			jeux_actif = 0;
			close_scrabble();
			break;

		case 2:
			stop_jeux(message);
			jeux_actif = 0;
			close_quizz();
			break;
	}
}

void jeux_score(User *use , message_irc *message)
{
	score_jeux(message);
}

void jeux_top10(User *use , message_irc *message)
{
	class_top10(message);
}

void jeux_mynick(User *use , message_irc *message)
{
	char txt[MAXLEN];

	if(!message->ARG[1])
	{
		help_on_error(use,message->ARG[0],me);
		return;
	}
	set_nick_jeux(use,message->ARG[1]);
	sprintf(txt,"Votre pseudo de jeux est maintenant\0034 %s \0030.",message->ARG[1]);
	fsend_com(LINK_COM_USER_NOTICE,me,use->nick,txt);
}
/**
	Gestion Liste Chainee du scrabble 
**/
void add_mot_base(char *mot)
{
	Mot_Base *nMot = (Mot_Base*)malloc(sizeof(Mot_Base));
	if(!nMot)
		return;

	STRDUP(nMot->mot,mot);
	nMot->point = count_point(mot);

	nMot->precedent = NULL;
	nMot->suivant = pMot_Base;
	if (pMot_Base)
    	pMot_Base->precedent = nMot;
	pMot_Base = nMot;
}

void clear_mot_base()
{
	Mot_Base *nMot;
	while (pPossible)
	{
		nMot = pMot_Base;
		pMot_Base = pMot_Base->suivant;
		FREE(nMot->mot);
		FREE(nMot);
		nMot = NULL;
	}
	pMot_Base = NULL;
}


void add_reponse(char *mot)
{
	Reponse *nMot = (Reponse*)malloc(sizeof(Reponse));
	if(!nMot)
		return;

	STRDUP(nMot->mot,mot);

	nMot->precedent = NULL;
	nMot->suivant = pReponse;
	if (pReponse)
    	pReponse->precedent = nMot;
	pReponse = nMot;
}

void clear_reponse()
{
	Reponse *reponse;
	while (pReponse)
	{
		reponse = pReponse;
		pReponse = pReponse->suivant;
		FREE(reponse->mot);
		FREE(reponse);
		reponse = NULL;
	}
	pReponse = NULL;
}


void add_possible(char *mot)
{
	Possible *nMot = (Possible*)malloc(sizeof(Possible));
	if(!nMot)
		return;

	STRDUP(nMot->mot,mot);
	nMot->point = count_point(mot);

	nMot->precedent = NULL;
	nMot->suivant = pPossible;
	if (pPossible)
    	pPossible->precedent = nMot;
	pPossible = nMot;
}

void clear_possible()
{
	Possible *poss;
	while (pPossible)
	{
		poss = pPossible;
		pPossible = pPossible->suivant;
		FREE(poss->mot);
		FREE(poss);
		poss = NULL;
	}
	pPossible = NULL;
}

void add_question_quizz(char *question,char *reponse)
{
	Base_Quizz *q = (Base_Quizz*)malloc(sizeof(Base_Quizz));
	if(!q)
		return;

	STRDUP(q->question,question);
	STRDUP(q->reponse,reponse);

	nQuestion++;

	q->precedent = NULL;
	q->suivant = pBase_Quizz;
	if (pBase_Quizz)
    	pBase_Quizz->precedent = q;
	pBase_Quizz = q;
}

void clear_question_quizz()
{
	Base_Quizz *q;
	while (pBase_Quizz)
	{
		q = pBase_Quizz;
		pBase_Quizz = pBase_Quizz->suivant;
		FREE(q->question);
		FREE(q->reponse);
		FREE(q);
		q = NULL;

		nQuestion--;
	}
	pBase_Quizz = NULL;
}

/**
	les fonctions scrabble
**/
int count_point(char *mot)
{
	int val = 0;
	char ch;
	int i = 0;

	while((ch = mot[i++]))
	{
		switch(ch)
		{
			case 'D':
			case 'G':
			case 'M':
				val += 2;
				break;

			case 'B':
			case 'C':
			case 'P': 
				val += 3;
				break;

			case 'V':
			case 'F':
			case 'H':
				val += 4;
				break;

			case 'Q':
			case 'J':
				val += 8;
				break;

			case 'K':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
				val += 10;
				break;

			default:
				val += 1;
				break;
		}
	}
	return val;
}

int count(char c , char *mot)
{
	int i = 0;
	char ch = 0;
	int count = 0;

	while((ch = mot[i]))
	{
		if(ch == c)
			count++;

		i++;
	}

	return count;
}

void valide(char *lettre , char *mot)
{
	int i = 0;
	char c = 0;
	while((c = mot[i]))
	{
		if(count(c,lettre) < count(c,mot))
			return;

		i++;
	}
	nMot++;

	add_possible(mot);

	if(Scrabble_type == 1)
	{
		if(strlen(mot) > maxlen)
		{
			maxlen = strlen(mot);
			xMot_Maxlen = 1;
			clear_reponse();
			add_reponse(mot);
			return;
		}
		if(strlen(mot) == maxlen)
		{
			xMot_Maxlen++;
			add_reponse(mot);
		}
	}
	if(Scrabble_type == 2)
	{
		i = count_point(mot);

		if(i > maxlen)
		{
			maxlen = i;
			xMot_Maxlen = 1;
			clear_reponse();
			add_reponse(mot);
			return;
		}
		if(i == maxlen)
		{
			xMot_Maxlen++;
			add_reponse(mot);
		}
	}
}

int load_db_scabble()
{
	char ligne[50];
	char *p;
	FILE *myFile= fopen("base/liste_base.db", "r");
	if(!myFile)
		return 0;

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

			add_mot_base(ligne);
		}
	}

	fclose(myFile);

	return 1;
}

char *tire_lettre()
{
	char *lettre = { "AAAAAAAAABBCCDDDEEEEEEEEEEEEEEEFFGGHHIIIIIIIIJKLLLLLMMMNNNNNNOOOOOOPPQRRRRRRSSSSSSTTTTTTUUUUUUVVWXYZ" };

	int i = 0;
	char tir[50];
	do
	{
		switch(i)
		{
		case 0:
		case 2:
		case 4:
		case 6:
		case 8:
		case 10:
		case 12:
		case 14:
		case 16:
		case 18:
		case 20:
		case 22:
		case 24:
		case 26:
		case 28:
		case 30:
			tir[i++] = lettre[my_rand(strlen(lettre))];
			break;

		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
		case 13:
		case 15:
		case 17:
		case 19:
		case 21:
		case 23:
		case 25:
		case 27:
		case 29:
		case 31:
			tir[i++] = ' ';
			break;
		}
		
		if(i >= (count_lettre * 2))
		{
			tir[i++] = 0;
			return strdup(tir);
		}

		
	}while(i);

	return strdup(tir);
}

/**
	JEUX SCRABBLE
**/
void init_scrabble()
{
	Mot_Base *mot = NULL;

	clock_t
  		temps_initial, /* Temps initial en micro-secondes */
  		temps_final;   /* Temps final en micro-secondes */
	float
  		temps_cpu;     /* Temps total en secondes */
	
	temps_initial = clock ();
	char *tirage = tire_lettre();
	char txt[MAXLEN];
	mot = pMot_Base;
	while(mot)
	{
			valide(tirage,mot->mot);
			mot = mot->suivant;
	}
	temps_final = clock ();
	temps_cpu = (temps_final - temps_initial) * 1e-6;



	if(Scrabble_type == 1)
	{
		sprintf(txt,ANNONCELETTRE_SCRABBLE,tirage,nMot);
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);

		sprintf(txt,ANNONCEPOSSIBLE_SCRABBLE,xMot_Maxlen,maxlen,maxlen);
		fsend_com(LINK_COM_USER_PRIVMSG,me, CHANNELSCRABBLE,txt);
	}
	if(Scrabble_type == 2)
	{
		sprintf(txt,ANNONCELETTRE_SCRABBLE2,tirage,nMot);
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);

		sprintf(txt,ANNONCEPOSSIBLE_SCRABBLE2,xMot_Maxlen,maxlen,maxlen);
		fsend_com(LINK_COM_USER_PRIVMSG,me, CHANNELSCRABBLE,txt);
	}
	sprintf(txt,ANNONCETEMPS_SCRABBLE,temps_cpu);
	fsend_com(LINK_COM_USER_PRIVMSG,me, CHANNELSCRABBLE,txt);


	FREE(tirage);
}

void close_scrabble()
{
	nMot = 0;
	maxlen = 0;
	xMot_Maxlen = 0;
	clear_reponse();
	clear_possible();

	gagnant = NULL;
	point_courant = 0;
}

char *Affiche_reponse()
{
	char txt[MAXLEN];
	int i = 0;
	Reponse *reponse = pReponse;
	while(reponse)
	{
		if(!i)
			sprintf(txt,"\0038%s",reponse->mot);

		else
			sprintf(txt,"%s \0030- \0038%s", txt,reponse->mot);

		reponse = reponse->suivant;
		i++;
	}
	return strdup(txt);
}

void find_scrabble(message_irc *message)
{
	Pseudo_Jeux *r;
	char txt[MAXLEN];
	int ok = 0;
	User *use = NULL;

	Possible *possible = pPossible;
	while(possible)
	{
		if(!strcasecmp(message->ARG[0],possible->mot))
		{
			ok = 1;
			break;
		}
		possible = possible->suivant;
	}

	tirage_vide = 0;

	if(!ok)
		return;

	use = get_user(message->RAW[0]);
	if(!use)
		return;

	if(!strcmp(use->nick_jeux,"?"))
	{
		sprintf(txt,"Vous devez choisir un pseudo de jeux avant de jouer");
		fsend_com(LINK_COM_USER_NOTICE,me,message->RAW[0],txt);
		help_on_error(use,"!mynick",me);
		return;
	}

	r = get_Pseudo_Jeux(use->nick_jeux);
	if(!r)
		r = add_Pseudo_Jeux(use->nick_jeux,0);

	if(!r)
		return;

	if(Scrabble_type == 1)
	{
		if(strlen(possible->mot) == (unsigned int)maxlen)
		{
			gagnant = r;

			del_Timer("SCRABBLE","SCRABBLE");
			gagnant->point_jeux += maxlen;
			sprintf(txt,EXPIRE_TEMPS_AVEC_GAGNANT_SCRABBLE,gagnant->nick,maxlen);
			fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
			fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,NEW_TIRAGE_IN_SCRABBLE);
			close_scrabble();
			new_timer(1,30,&lance_scrabble,"SCRABBLE","SCRABBLE");
			return;
		}
		if(strlen(possible->mot) > (unsigned int)point_courant)
		{
			point_courant = (int)strlen(possible->mot);
			gagnant = r;
			sprintf(txt,RETIENT_SCRABBLE,message->ARG[0],point_courant,gagnant->nick);
			fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
		}
	}

	if(Scrabble_type == 2)
	{
		if(possible->point == (unsigned int)maxlen)
		{
			gagnant = r;

			del_Timer("SCRABBLE","SCRABBLE");
			gagnant->point_jeux += maxlen;
			sprintf(txt,EXPIRE_TEMPS_AVEC_GAGNANT_SCRABBLE,gagnant->nick,maxlen);
			fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
			fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,NEW_TIRAGE_IN_SCRABBLE);
			close_scrabble();
			new_timer(1,30,&lance_scrabble,"SCRABBLE","SCRABBLE");
			return;
		}
		if(possible->point > (unsigned int)point_courant)
		{
			point_courant = possible->point;
			gagnant = r;
			sprintf(txt,RETIENT_SCRABBLE,message->ARG[0],point_courant,gagnant->nick);
			fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
		}
	}
}

void lance_scrabble()
{
	init_scrabble();
	new_timer(1,30,&scrabble_mi_temp,"SCRABBLE","SCRABBLE");
}


void scrabble_mi_temp()
{
	char txt[MAXLEN];
	sprintf(txt,MI_TEMPS_SCRABBLE);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
	new_timer(1,30,&scrabble_expire,"SCRABBLE","SCRABBLE");
}

void scrabble_expire()
{
	char txt[MAXLEN];
	char *reponse;
	if(gagnant)
	{
		tirage_vide = 0;

		gagnant->point_jeux += point_courant;

		sprintf(txt,EXPIRE_TEMPS_AVEC_GAGNANT_SCRABBLE,gagnant->nick,point_courant);
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);

	}
	else
	{
		tirage_vide++;
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,EXPIRE_TEMPS_SCRABBLE);
	}

	reponse = Affiche_reponse();
	sprintf(txt,REPONSE_SCRABBLE,reponse);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
	FREE(reponse);

	close_scrabble();
	if(tirage_vide < 10)
	{
		new_timer(1,30,&lance_scrabble,"SCRABBLE","SCRABBLE");
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,NEW_TIRAGE_IN_SCRABBLE);
	}
	else
		stop_jeux(NULL);
}

void stop_jeux(message_irc *message)
{
	char txt[MAXLEN];

	switch(jeux_actif)
	{
		case 1:
			if(message)
			{

				sprintf(txt,SCRABBLE_TERMINE_SCRABBLE,message->RAW[0]);
				fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
			}
			else
			{
				fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBSCRABBLE_SCRABBLE);
				fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBQUIZZ_QUIZZ);
			}
			break;

		case 2:
			if(message)
			{

				sprintf(txt,QUIZZ_TERMINE_QUIZZ,message->RAW[0]);
				fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
			}
			else
			{
				fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBSCRABBLE_SCRABBLE);
				fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,PUBQUIZZ_QUIZZ);
			}
			break;
	}
	jeux_actif = 0;

	save_db_score();
}

/**
	JEUX QUIZZ
**/
char *remplace_tiret(char *scr)
{
	char *txt;
	int i = 0;
	STRDUP(txt,scr);
	while(txt[i] != 0)
	{
		switch(txt[i])
		{
		case '_':
			txt[i] = ' ';
			break;

		case 'é':
		case 'è':
		case 'ê':
		case 'ë':
		case 'È':
		case 'É':
		case 'Ê':
		case 'Ë':
			txt[i] = 'e';
			break;

		case 'à':
		case 'â':
		case 'ä':
		case 'À':
		case 'Â':
			txt[i] = 'a';
			break;

		case 'î':
		case 'ï':
		case 'Ï':
		case 'Î':
		case 'ì':
		case 'Ì':
			txt[i] = 'i';
			break;

		case 'Ô':
		case 'ö':
		case 'ô':
			txt[i] = 'o';
			break;


		case 'ù':
		case 'Ù':
		case 'û':
		case 'Û':
		case 'ü':
		case 'Ü':
			txt[i] = 'u';
			break;

		case 'ç':
			txt[i] = 'c';
			break;

		}
			

		i++;
	}
	return txt;
}

char *indice(char *scr)
{
	char *txt;
	int i = 0;
	int x = 0;
	int len = 0;

	STRDUP(txt,scr);
	len = strlen(txt);
	if(len == 1)
		return txt;

	while(txt[i] != 0)
	{
		x = my_rand(len);

		if(i != x && txt[i] != ' ' && txt[i] != '\'')
			txt[i] = '*';

		i++;
	}
	return txt;
}


int load_db_quizz()
{
	char ligne[MAXLEN];
	char *question , *reponse;
	char *question_ , *reponse_;
	char *p;
	FILE *myFile = fopen("base/liste_quizz.db", "r");
	if(!myFile)
		return 0;

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

			question_ = strtok(ligne,"|");
			reponse_ = strtok(NULL,"|");
			question = remplace_tiret(question_);
			reponse = remplace_tiret(reponse_);
			add_question_quizz(question,reponse);
			FREE(reponse);
			FREE(question);	
		}
	}
	fclose(myFile);
	return 1;
}


void init_quizz()
{
	Base_Quizz *quizz = NULL;

	clock_t
  		temps_initial, /* Temps initial en micro-secondes */
  		temps_final;   /* Temps final en micro-secondes */
	float
  		temps_cpu;     /* Temps total en secondes */
	
	temps_initial = clock ();
	int x = my_rand(nQuestion);
	int y = 0;

	char txt[MAXLEN];
	quizz = pBase_Quizz;
	while(quizz)
	{
		if(x == y++)
		{
			Question_tire = quizz;
			break;
		}
		quizz = quizz->suivant;
	}
	temps_final = clock ();
	temps_cpu = (temps_final - temps_initial) * 1e-6;

	sprintf(txt,ANNONCEQUESTION_QUIZZ,Question_tire->question);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);

	sprintf(txt,ANNONCETEMPS_QUIZZ,temps_cpu);
	fsend_com(LINK_COM_USER_PRIVMSG,me, CHANNELSCRABBLE,txt);

	tirage_vide++;
}

void close_quizz()
{
	Question_tire = NULL;
}

void lance_quizz()
{
	init_quizz();
	new_timer(1,30,&quizz_mi_temp,"SCRABBLE","SCRABBLE");
}


void quizz_mi_temp()
{
	char txt[MAXLEN];
	char *t;
	sprintf(txt,MI_TEMPS_QUIZZ);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);

	t = indice(Question_tire->reponse);
	sprintf(txt,INDICE_IN_QUIZZ,t);
	FREE(t);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
	new_timer(1,30,&quizz_expire,"SCRABBLE","SCRABBLE");
}

void quizz_expire()
{
	char txt[MAXLEN];
	tirage_vide++;

	sprintf(txt,EXPIRE_TEMPS_QUIZZ,Question_tire->reponse);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);

	close_quizz();
	if(tirage_vide < 10)
	{
		new_timer(1,30,&lance_quizz,"SCRABBLE","SCRABBLE");
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,NEW_TIRAGE_IN_QUIZZ);
	}
	else
		stop_jeux(NULL);
}

void find_quizz(message_irc *message)
{
	Pseudo_Jeux *r;
	User *use = NULL;
	char txt[MAXLEN];
	int i = 0;

	if(!Question_tire)
		return;

	tirage_vide = 0;
	while(message->ARG[i])
	{
		if(i == 0)
			sprintf(txt,"%s",message->ARG[i]);
		else
			sprintf(txt,"%s %s",txt,message->ARG[i]);
		i++;
	}

	if(strcasecmp(txt,Question_tire->reponse))
		return;

	use = get_user(message->RAW[0]);
	if(!use)
		return;

	if(!strcmp(use->nick_jeux,"?"))
	{
		sprintf(txt,"Vous devez choisir un pseudo de jeux avant de jouer");
		fsend_com(LINK_COM_USER_NOTICE,me,message->RAW[0],txt);
		help_on_error(use,"!mynick",me);
		return;
	}

	r = get_Pseudo_Jeux(use->nick_jeux);
	if(!r)
		r = add_Pseudo_Jeux(use->nick_jeux,0);

	if(!r)
		return;

	gagnant = r;

	del_Timer("SCRABBLE","SCRABBLE");
	gagnant->point_jeux += 10;
	sprintf(txt,GAGNANT_QUIZZ,gagnant->nick,10,Question_tire->reponse);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,NEW_TIRAGE_IN_QUIZZ);
	close_quizz();
	new_timer(1,30,&lance_quizz,"SCRABBLE","SCRABBLE");
}

/**
	all jeux
**/
void score_jeux(message_irc *message)
{
	char txt[MAXLEN];
	Pseudo_Jeux *r;
	User *use = get_user(message->RAW[0]);
	if(!use)
		return;

	if(!strcmp(use->nick_jeux,"?"))
	{
		sprintf(txt,"Vous n'avez pas defini votre pseudo de jeux");
		fsend_com(LINK_COM_USER_NOTICE,me,message->RAW[0],txt);
		help_on_error(use,"!mynick",me);
		return;
	}

	r = get_Pseudo_Jeux(use->nick_jeux);
	if(!r)
	{
		fsend_com(LINK_COM_USER_NOTICE,me,message->RAW[0],"Votre pseudo n'a pas de score");
		return;
	}

	sprintf(txt,"Le score de %s est de %d",r->nick,r->point_jeux);
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
}

void class_top10(message_irc *message)
{
	char txt[MAXLEN];
	char **nicklist;
	char *temp; 
	int modif = 0;
	int nb = 0;
	int i = 0;

	Pseudo_Jeux *resa = pPseudo_Jeux;
	Pseudo_Jeux *resa2 = NULL;

	nicklist = (char**)malloc(sizeof(nicklist));
	
	nb = 0;
	modif = 0;
	i = 0;
	while(resa)
	{
		nicklist = (char**)realloc(nicklist, ( sizeof(nicklist) * (nb+1)) + 1 );
		nicklist[nb++] = resa->nick;
		resa = resa->suivant;
	}

	nicklist[nb] = NULL;
	nb--;
	do 
	{ 
		modif = 0; 
		for (i=0; i<=nb-1; i++)
		{

			if(!nicklist[i] || !nicklist[i+1])
				break;

			resa = get_Pseudo_Jeux(nicklist[i]);
			resa2 = get_Pseudo_Jeux(nicklist[i+1]);
			if (resa->point_jeux < resa2->point_jeux) 
			{ 
				temp = nicklist[i]; 
				nicklist[i] = nicklist[i+1]; 
				nicklist[i+1] = temp; 
				modif = 1; 
			} 
		} 
	} while (modif == 1);

	i = 0;
	sprintf(txt,"\0038,1\002[\0034 TOP 10 \0038]\0030 Voici le top 10 :");
	fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
	while( i < 10 && i <= nb)
	{
		resa = get_Pseudo_Jeux(nicklist[i]);
		sprintf(txt,"\0038,1\002[\0034 %d \0038]\00315 %s \0030 avec\0034 %d \0030 points .",i+1,resa->nick,resa->point_jeux);
		fsend_com(LINK_COM_USER_PRIVMSG,me,CHANNELSCRABBLE,txt);
		i++;
	}
	FREE(nicklist);
	
	return;
}

