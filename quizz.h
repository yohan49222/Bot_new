#ifndef QUIZZ_H

#define QUIZZ_H

#define PUBQUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Tapez \0038!quizz\0030 pour demmarrer le jeux"
#define ANNONCEQUESTION "\0038,1\002[\0034 QUIZZ \0038]\0030 Nouvelles question :\0038 %s ???"
#define MI_TEMPS_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Attention , il ne vous reste plus que\0038 30\0030 secondes ."
#define EXPIRE_TEMPS_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Termin� Personne ne remporte de point , Reponse :\0038 %s"
#define GAGNANT "\0038,1\002[\0034 QUIZZ \0038]\0030 Termin� \0038 %s\0030 remporte \0038 %d \0030points ."
#define QUIZZ_TERMINE "\0038,1\002[\0034 QUIZZ \0038]\0038 %s \0030vient de mettre fin �la partie"
#define NEW_TIRAGE_IN_QUIZZ "\0038,1\002[\0034 QUIZZ \0038]\0030 Prochain tirage dans \0038 30 \0030secondes, Bonne chance !!"



typedef struct Quizz_Base
{
	char question[256];
	char reponse[256];
	struct Quizz_Base *precedent;
	struct Quizz_Base *suivant;
}Quizz_Base;

typedef struct Quizz
{
	Quizz_Base *tirage;
	int tirage_max;
	int tirage_vide;
}Quizz;

void init_jeux_quizz();
void init_quizz();
void add_quizz_base(char *question, char *reponse);
Quizz_Base *new_tirage_quizz();
void lance_quizz(message_irc *message);
void lance_quizz2();
void quizz_mi_temp();
void quizz_expire();
void stop_quizz(message_irc *message);
void p_RAW_QUIZZ(message_irc *message);
void p_RAW_JOIN_QUIZZ(message_irc *message);
void find_reponse_quizz(message_irc *message);
void retire_accent(char *mot);
#endif

