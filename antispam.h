#ifndef ANTISPAM_H

#define ANTISPAM_H

/**
	Gestion Des As Actif
**/
typedef struct As_Actif
{
	char *nick;
	struct As_Actif *precedent;
	struct As_Actif *suivant;

}As_Actif;

As_Actif *new_As_Actif(char *nick);
int del_As_Actif(char *nick);
As_Actif *get_As_Actif(char *nick);

/**
	Gestion des Mask 
**/
typedef struct As_Mask
{
	char *mask;
	struct As_Mask *precedent;
	struct As_Mask *suivant;

}As_Mask;

As_Mask *new_mask(char *mask);
int clear_mask_spam();

void init_spam();
void unload_spam();

/**
	Raw antispam
**/
void ANTISPAM_PRIVMSG(message_irc *message);
void ANTISPAM_KILL(message_irc *message);
void ANTISPAM_KICK(message_irc *message);

/**
	commandes antispam
**/
void antispam_help(User *use , message_irc *message);
void antispam_active(User *use , message_irc *message);
void add_mask_spam(User *use ,message_irc *message);

/**
	fonction antispam
**/
void load_config_Antispam(char *Fichier );
void save_db_antispam();
void load_db_antispam();
char *codage_host();


int find_spam(message_irc *message);
int is_spam(const char *str_request);
int is_spam_ok(const char *str_request);

void connect_As();
void deconnect_As(char *Array);
void deconnect_allAs();






#endif

