#ifndef OPERSERV_H

#define OPERSERV_H


void init_operserv();
void unload_operserv();

int maxclone(User *tmp);
char *listclone(User *tmp);
/**
	Raw operserv 
**/
void OPERSERV_PRIVMSG(message_irc *message);
void OPERSERV_CONNECT(message_irc *message);
void OPERSERV_QUIT(message_irc *message);
void OPERSERV_MODE(message_irc *message);
void OPERSERV_JOIN(message_irc *message);
void OPERSERV_PART(message_irc *message);
void OPERSERV_NICK(message_irc *message);
void OPERSERV_KICK(message_irc *message);
void OPERSERV_KILL(message_irc *message);
void OPERSERV_SETHOST(message_irc *message);
void OPERSERV_CHGHOST(message_irc *message);
void OPERSERV_CHGIDENT(message_irc *message);
void OPERSERV_SETIDENT(message_irc *message);
void OPERSERV_SETNAME(message_irc *message);
void OPERSERV_CHGNAME(message_irc *message);
void OPERSERV_AWAY(message_irc *message);
void OPERSERV_TOPIC(message_irc *message);
void OPERSERV_TKL(message_irc *message);
/**
	commandes operserv
**/
void operserv_help(User *use , message_irc *message);
void operserv_kill(User *use , message_irc *message);
void operserv_gline(User *use , message_irc *message);
void operserv_ungline(User *use , message_irc *message);
void operserv_svspart(User *use , message_irc *message);
void operserv_svsjoin(User *use , message_irc *message);
void operserv_svsmode(User *use , message_irc *message);
void operserv_svsnick(User *use , message_irc *message);
void operserv_jupe(User *use , message_irc *message);


#endif

