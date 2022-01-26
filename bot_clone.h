#ifndef BOTCLONE_H

#define BOTCLONE_H


/**
	****************************
	** structure des services **
	****************************
**/
typedef struct bot_clone
{
	char *nick;
	char *handle;
	char *host;
	char *real;
	char *flag;
	struct bot_clone *precedent;
	struct bot_clone *suivant;

} bot_clone;


/**
	** Gestions des bots **
**/
User  *new_clone(char *nick,char *flag,char *real,char *vhost);
int clear_clone();
long bot_clone_t();
int del_clone(char *nick,char *messquit);
int get_clone(char *nick);

void bot_join(char *botnick , char *chanName , char *mode);

void bot_clone_version(User *use , message_irc *message);




#endif

