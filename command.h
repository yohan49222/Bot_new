#ifndef COMMAND_H

#define COMMAND_H


typedef void (*myFuncComPtr)(User *use,message_irc *message);

typedef struct Com_IN
{
	char *ComName;			/** commande			**/
	char *ComBot;			/** pseudo du bot proprietaire	**/
	char *ComFlag;			/** Flags demande		**/
	char *exemple;			/** exemple de la commande	**/
	char *desc;			/** description			**/

	myFuncComPtr func;		/** pointeur sur la fonction	**/

	struct Com_IN *precedent;
	struct Com_IN *suivant;

} Com_IN;

Com_IN *Create_Com( char *name , char *bot, myFuncComPtr func ,char *flag,char *exemple,char *desc);
int executeCom( User *use , message_irc *message , char *botnick);
int is_Capable(User *use,char ch);
int is_valide(User *use , Com_IN *command);
void help(User *use,message_irc *message,char *botnick);
void help_on_error(User *use,char *commande,char *botnick);
int clear_command();
long Com_IN_t();
int del_command(char *botname);

#endif

