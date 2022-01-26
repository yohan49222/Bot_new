#ifndef RAW_H

#define RAW_H

/**
	Gestion de Raw de gestion

	les raws de gestion sont les raws sevant a la gestion des users et des channels
**/


typedef void (*myFuncRawPtr)(message_irc *message);

typedef struct Raw_IN_Gestion
{
	char *rawName;
	myFuncRawPtr func;

	struct Raw_IN_Gestion *precedent;
	struct Raw_IN_Gestion *suivant;

} Raw_IN_Gestion;


void init_Raw_Gestion( void );
Raw_IN_Gestion *Create_Raw_Gestion( char *name , myFuncRawPtr func);
void executeRaw_Gestion( message_irc *message );
int clear_Raw_Gestion();
long Raw_IN_t_Gestion();

/**
	Gestion des raws de bot

	Les raws de bots sont les raws neccessaire a chaque robot
**/

typedef struct Raw_IN_Bot
{
	char *rawName;
	char *rawBot;
	myFuncRawPtr func;

	struct Raw_IN_Bot *precedent;
	struct Raw_IN_Bot *suivant;

}Raw_IN_Bot;

Raw_IN_Bot *Create_Raw_Bot( char *name , myFuncRawPtr func,char *botnick);
void executeRaw_Bot( message_irc *message );
int clear_Raw_Bot();
long Raw_IN_t_Bot();
int del_Raw_Bot(char *botname);
/**
	Gestion des raws de Protect 

	Les raws de bots sont les raws neccessaire aux Protect 
**/

typedef struct Raw_IN_Protect
{
	char *rawName;
	myFuncRawPtr func;

	struct Raw_IN_Protect *precedent;
	struct Raw_IN_Protect *suivant;

}Raw_IN_Protect;

Raw_IN_Protect *Create_Raw_Protect( char *name , myFuncRawPtr func);
int clear_Raw_Protect();
long Raw_IN_t_Protect();
void executeRaw_Protect( message_irc *message );

typedef struct ComAction
{
	char action[10];
}ComAction;


#endif

