#ifndef GLOBALSERV_H

#define GLOBALSERV_H

void init_global();
void unload_global();

/**
	Raw antispam
**/
void GLOBAL_PRIVMSG(message_irc *message);
void GLOBAL_KILL(message_irc *message);
void GLOBAL_KICK(message_irc *message);

/**
	commandes antispam
**/
void global_help(User *use , message_irc *message);
void global_global(User *use , message_irc *message);
void global_globop(User *use , message_irc *message);
#endif

