#ifndef PRINCIPALE_H

#define PRINCIPALE_H

void init_principale();
void unload_principale();

/**
	Raw principale
**/
void PRINCIPALE_PRIVMSG(message_irc *message);
void PRINCIPALE_KILL(message_irc *message);
void PRINCIPALE_KICK(message_irc *message);

/**
	commandes principale
**/
void principale_help(User *use , message_irc *message);
void principale_rehash(User *use , message_irc *message);
void principale_die(User *use , message_irc *message);

#endif

