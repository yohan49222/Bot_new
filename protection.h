#ifndef PROTECTION_H


#define PROTECTION_H


/**
	****************************
	** structure des Protect **
	****************************
**/

typedef struct Protect
{
	char *mask;
	struct Protect *precedent;
	struct Protect *suivant;

}Protect;


/**
	** Gestions des Protections **
**/

Protect *new_Protect(char *mask);
int del_Protect(char *mask);
int clear_Protect();
void get_Protect(User *use);
long Protect_t();
void load_bd_protect();


void init_protectserv();
void unload_protectserv();

/**
	Raw protectserv 
**/
void PROTECTSERV_CONNECT(message_irc *message);
void PROTECTSERV_PRIVMSG(message_irc *message);
void PROTECTSERV_KILL(message_irc *message);
void PROTECTSERV_KICK(message_irc *message);


/**
	commandes protectserv
**/
void protectserv_help(User *use , message_irc *message);
void protectserv_add( User *use , message_irc *message);
void protectserv_del( User *use , message_irc *message);
void protectserv_list( User *use , message_irc *message);














#endif


