#ifndef NICKSERV_H

#define NICKSERV_H

/**
	**********************************
	** structure des nicks reserve **
	**********************************
**/
typedef struct Nick_Resa
{
	char *nick;
	char *pass;
	char *email;
	char *vhost;
	long point_jeux;
	long expire;
	struct Nick_Resa *precedent;
	struct Nick_Resa *suivant;

}Nick_Resa;



void init_nickserv();
void unload_nickserv();

void load_db_nickserv();
void savebd_nick_resa();
void verif_ident(char *nick);
void conn_protect(char *nick);
void deco_protect(char *nick);

/**
	** Gestions des nick resa **
**/

Nick_Resa *new_nickresa(char *nick,char *pass,char *email,char *vhost,long expire,long score);
int del_nickresa(char *nick);
int clear_nickresa();
Nick_Resa *get_nickresa(char *nick);
long Nick_Resa_t();



/**
	Raw nickserv
**/
void NICKSERV_CONNECT(message_irc *message);
void NICKSERV_NICK(message_irc *message);
void NICKSERV_PRIVMSG(message_irc *message);
void NICKSERV_KILL(message_irc *message);
void NICKSERV_KICK(message_irc *message);


/**
	commandes nickserv
**/
void nickserv_help(User *use , message_irc *message);
void nickserv_identify(User *use , message_irc *message);
void nickserv_register(User *use , message_irc *message);
void nickserv_drop(User *use , message_irc *message);
void nickserv_ghost(User *use , message_irc *message);
void nickserv_sendpass(User *use , message_irc *message);
void nickserv_setpass(User *use , message_irc *message);
void nickserv_setmail(User *use , message_irc *message);
#endif

