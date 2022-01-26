#ifndef COLEEN_H

#define COLEEN_H

#define COLEEN_FLAGS_GEO	0x00000001
#define COLEEN_FLAGS_CSA	0x00000002
#define COLEEN_FLAGS_IRCOP	0x00000004

typedef struct Coleen_Access
{
	char *nick;
	char *pass;
	int niveau;
	int actif;

	struct Coleen_Access *suivant;
	struct Coleen_Access *precedent;

}Coleen_Access;

void init_coleen();
void unload_coleen();
void coleen_join_channel();



Coleen_Access *new_Coleen_Access(char *nick,char *pass,int niveau,int actif);
Coleen_Access *get_Coleen_Access(char *nick);
int del_Coleen_Access(char *nick);
int clear_access();

void load_db_access();
void save_Coleen_access();

void set_geo(User *use,int onoff);
void set_csa(User *use,int onoff);
void set_ircop(User *use,int onoff);
void deauth_user(char *host);


/**
	Raw antispam
**/
void COLEEN_PRIVMSG(message_irc *message);
void COLEEN_KILL(message_irc *message);
void COLEEN_KICK(message_irc *message);
/**
	commandes antispam
**/
void coleen_help(User *use , message_irc *message);
void coleen_auth(User *use , message_irc *message);
void coleen_deauth(User *use , message_irc *message);
void coleen_kill(User *use , message_irc *message);
void coleen_gline(User *use , message_irc *message);
void coleen_add_access(User *use , message_irc *message);
void coleen_suspend(User *use , message_irc *message);
void coleen_reactive(User *use , message_irc *message);
void coleen_setpass(User *use , message_irc *message);
void coleen_deluser(User *use , message_irc *message);
void coleen_say(User *use , message_irc *message);
void coleen_setaccess(User *use , message_irc *message);
void coleen_accesslist(User *use , message_irc *message);


void coleen_op(User *use , message_irc *message);
void coleen_deop(User *use , message_irc *message);
void coleen_voice(User *use , message_irc *message);
void coleen_devoice(User *use , message_irc *message);
void coleen_half(User *use , message_irc *message);
void coleen_dehalf(User *use , message_irc *message);

void coleen_glinelist(User *use , message_irc *message);
void coleen_ungline(User *use , message_irc *message);
void coleen_cleargline(User *use , message_irc *message);

void coleen_kick(User *use , message_irc *message);

void coleen_sajoin(User *use , message_irc *message);
void coleen_sapart(User *use , message_irc *message);

void coleen_swhois(User *use , message_irc *message);


void coleen_mop(User *use , message_irc *message);
void coleen_mdeop(User *use , message_irc *message);
void coleen_mvoice(User *use , message_irc *message);
void coleen_mdevoice(User *use , message_irc *message);
void coleen_mhalf(User *use , message_irc *message);
void coleen_mdehalf(User *use , message_irc *message);
void coleen_mkick(User *use , message_irc *message);
#endif






