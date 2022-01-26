#ifndef SCRABBLE_H

#define SCRABBLE_H

/**
	scrabble
**/
#define YOUR_NICK_JEUX "\0038,1\002[\0034 INFO \0038]\0030 N'oubliez pas de definir votre pseudo de jeux\0038 !MYNICK <pseudo>"

#define PUBSCRABBLE_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Tapez \0038!scrabble\0030 pour demmarrer le jeux"

#define SCRABBLE_ANNONCE_TYPE1 "\0038,1\002[\0034 SCRABBLE \0038]\0030 Le But du jeux est maintenant de trouver le mot le plus\0038 long \0030."

#define SCRABBLE_ANNONCE_TYPE2 "\0038,1\002[\0034 SCRABBLE \0038]\0030 Le But du jeux est maintenant de trouver le mot le plus\0038 cher \0030."

#define ANNONCELETTRE_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Trouvez le mots le plus long avec les lettres :\0038 %s \0030, Il y a\0038 %d \0030mots possibles ."

#define ANNONCELETTRE_SCRABBLE2 "\0038,1\002[\0034 SCRABBLE \0038]\0030 Trouvez le mots le plus cher avec les lettres :\0038 %s \0030, Il y a\0038 %d \0030mots possibles ."


#define ANNONCEPOSSIBLE_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Il y a\0038 %d \0030mots de\0038 %d \0030lettres ,\0038 %d \0030points à gagner ."



#define ANNONCEPOSSIBLE_SCRABBLE2 "\0038,1\002[\0034 SCRABBLE \0038]\0030 Il y a\0038 %d \0030mots valant\0038 %d \0030points ,\0038 %d\0030 points a gagner ."

#define ANNONCETEMPS_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Tirage effectu\xe9 en\0038 %f \0030secondes ."


#define MI_TEMPS_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Attention , il ne vous reste plus que\0038 30\0030 secondes ."

#define EXPIRE_TEMPS_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Terminé, Personne ne remporte de point ."

#define EXPIRE_TEMPS_AVEC_GAGNANT_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Terminé, \0038 %s\0030 remporte\0038 %d \0030points ."

#define RETIENT_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 le mot\0038 %s\0030 est une des possibilitées , je retiens\0038 %d \0030 points pour\0038 %s\0030 ."

#define SCRABBLE_TERMINE_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0038 %s \0030vient de mettre fin à la partie ."

#define NEW_TIRAGE_IN_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Prochain tirage dans \0038 30 \0030secondes, Bonne chance !!"

#define REPONSE_SCRABBLE "\0038,1\002[\0034 SCRABBLE \0038]\0030 Les mots les plus long \xe9taient : %s \0030!!"




/**
	quizz
**/

#define PUBQUIZZ_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Tapez \0038!quizz\0030 pour demmarrer le jeux"
#define ANNONCEQUESTION_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Nouvelles question :\0038 %s ???"
#define MI_TEMPS_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Attention , il ne vous reste plus que\0038 30\0030 secondes ."
#define EXPIRE_TEMPS_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Termin\xe9 Personne ne remporte de point , Reponse :\0038 %s"
#define GAGNANT_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Termin\xe9 \0038 %s\0030 remporte \0038 %d \0030points , Reponse :\0038 %s"
#define QUIZZ_TERMINE_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0038 %s \0030vient de mettre fin à la partie"
#define ANNONCETEMPS_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Tirage effectu\xe9 en\0038 %f \0030secondes ."
#define NEW_TIRAGE_IN_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Prochain tirage dans \0038 30 \0030secondes, Bonne chance !!"
#define INDICE_IN_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Voici de quoi vous aider : \0038 %s \0030, Bonne chance !!"


typedef struct Mot_Base
{
	char *mot;
	int point;

	struct Mot_Base *suivant;
	struct Mot_Base *precedent;
}Mot_Base;

typedef struct Reponse
{
	char *mot;

	struct Reponse *suivant;
	struct Reponse *precedent;
}Reponse;

typedef struct Possible
{
	char *mot;
	int point;

	struct Possible *suivant;
	struct Possible *precedent;

}Possible;

typedef struct Base_Quizz
{
	char *question;
	char *reponse;

	struct Base_Quizz *suivant;
	struct Base_Quizz *precedent;

}Base_Quizz;

typedef struct Pseudo_Jeux
{
	char *nick;
	int point_jeux;

	struct Pseudo_Jeux *suivant;
	struct Pseudo_Jeux *precedent;

}Pseudo_Jeux;

/* void scrabble */
void init_jeux();
void unload_jeux();

/**
	gestion des scores
**/
void load_db_score();
void save_db_score();
Pseudo_Jeux *add_Pseudo_Jeux(char *nick,int score);
void clear_Pseudo_Jeux();
Pseudo_Jeux *get_Pseudo_Jeux(char *nick);
void set_score(char *nick,int add);
void jeux_mynick(User *use , message_irc *message);

/**
	raws scrabble
**/
void JEUX_PRIVMSG(message_irc *message);
void JEUX_JOIN(message_irc *message);
void JEUX_KICK(message_irc *message);
void JEUX_KILL(message_irc *message);

/**
	commande scrabble
**/
void scrabble_help(User *use , message_irc *message);
void scrabble_lance(User *use , message_irc *message);
void scrabble_type(User *use , message_irc *message);
void scrabble_set_count(User *use , message_irc *message);
void quizz_lance(User *use , message_irc *message);
void jeux_stop(User *use , message_irc *message);
void jeux_score(User *use , message_irc *message);
void jeux_top10(User *use , message_irc *message);

/**
	Gestion Liste Chainee du scrabble 
**/
void add_mot_base(char *mot);
void clear_mot_base();
void add_reponse(char *mot);
void clear_reponse();
void add_possible(char *mot);
void clear_possible();
void add_question_quizz(char *question,char *reponse);
void clear_question_quizz();


/**
	le jeux scrabble
**/
int count_point(char *mot);
int count(char c , char *mot);
void valide(char *lettre , char *mot);
int load_db_scabble();
char *tire_lettre();
void init_scrabble();
void close_scrabble();
void find_scrabble(message_irc *message);
void lance_scrabble();
void scrabble_mi_temp();
void scrabble_expire();

/**
	le jeux quizz
**/
char *remplace_tiret(char *scr);
char *indice(char *scr);
int load_db_quizz();
void init_quizz();
void close_quizz();
void lance_quizz();
void quizz_mi_temp();
void quizz_expire();
void find_quizz(message_irc *message);

/**
	all jeux
**/
void stop_jeux(message_irc *message);
void score_jeux(message_irc *message);
void class_top10(message_irc *message);

#endif

