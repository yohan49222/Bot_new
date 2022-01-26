#ifndef MASSTOOLZ_H

#define MASSTOOLZ_H

/**
	gestion des channel Off Enregistre
**/


typedef struct Channel_Off_Reg
{
	char *name;

	struct Channel_Off_Reg *suivant;
	struct Channel_Off_Reg *precedent;

}Channel_Off_Reg;

Channel_Off_Reg *add_Channel_Off_Reg(char *name);
Channel_Off_Reg *get_Channel_Off_Reg(char *name);
int del_Channel_Off_Reg(char *name);
int clear_Channel_Off_Reg();

/**
	gestion des channel Prive close
**/
typedef struct Channel_Prive_Close
{
	char *name;

	struct Channel_Prive_Close *suivant;
	struct Channel_Prive_Close *precedent;

}Channel_Prive_Close;

Channel_Prive_Close *add_Channel_Prive_Close(char *name);
Channel_Prive_Close *get_Channel_Prive_Close(char *name);
int del_Channel_Prive_Close(char *name);
int clear_Channel_Prive_Close();


/**
	fonction masstoolz
**/
void init_masstoolz();
void unload_masstoolz();
void masstoolz_close(Channel *chan);
void masstoolz_unclose(Channel *chan);
void load_db_masstoolz();
void save_bd_masstoolz();

/**
	Raw masstoolz
**/
void MASSTOOLZ_PRIVMSG(message_irc *message);
void MASSTOOLZ_JOIN(message_irc *message);
void MASSTOOLZ_PART(message_irc *message);
void MASSTOOLZ_EOS(message_irc *message);
void MASSTOOLZ_KILL(message_irc *message);
void MASSTOOLZ_KICK(message_irc *message);

/**
	commandes masstoolz
**/
void masstoolz_help(User *use , message_irc *message);
void masstoolz_com_close(User *use , message_irc *message);
void masstoolz_com_unclose(User *use , message_irc *message);
void masstoolz_com_synchro(User *use , message_irc *message);


#endif

