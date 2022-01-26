#ifndef CHANNEL_H

#define CHANNEL_H

#define C_MODE_A  0x00000001
#define C_MODE_a  0x00000002
#define C_MODE_b  0x00000004
#define C_MODE_c  0x00000008
#define C_MODE_C  0x00000010
#define C_MODE_e  0x00000020
#define C_MODE_f  0x00000040
#define C_MODE_G  0x00000080
#define C_MODE_i  0x00000100
#define C_MODE_K  0x00000200
#define C_MODE_k  0x00000400
#define C_MODE_L  0x00000800
#define C_MODE_l  0x00001000
#define C_MODE_M  0x00002000
#define C_MODE_m  0x00004000
#define C_MODE_n  0x00008000
#define C_MODE_N  0x00010000
#define C_MODE_O  0x00020000
#define C_MODE_p  0x00040000
#define C_MODE_Q  0x00080000
#define C_MODE_r  0x00100000
#define C_MODE_R  0x00200000
#define C_MODE_S  0x00400000
#define C_MODE_s  0x00800000
#define C_MODE_T  0x01000000
#define C_MODE_t  0x02000000
#define C_MODE_u  0x04000000
#define C_MODE_V  0x08000000
#define C_MODE_z  0x10000000


#define S_MODE_o 0x00000001
#define S_MODE_h 0x00000002
#define S_MODE_v 0x00000004
#define S_MODE_a 0x00000008
#define S_MODE_q 0x00000010


/**
	****************************
	** Struture des userslist **
	****************************
**/
typedef struct UserList
{
	struct User *use;
	int modeUser;
	int access;
	struct UserList *precedent;
	struct UserList *suivant;

}UserList;

/**
	****************************
	** Struture des banlist **
	****************************
**/
typedef struct BanList
{
	char *mask;
	long timestamp;

	struct BanList *precedent;
	struct BanList *suivant;

}BanList;

/**
	****************************
	** structure des channels **
	****************************
**/
typedef struct Channel
{
	char *chanName;
	char *chanTopic;
	char *chanTopic_Auteur;
	long chanTopic_Date;
	int is_Off;
	int Mode;
	struct BanList *bancourant;
	struct UserList *usercourant;
	struct Channel *precedent;
	struct Channel *suivant;

}Channel;


/**
	** Gestions des channels **
**/

Channel *new_channel(char *name,long datetopic,char *topicAuteur,char *topic);
int del_channel(char *name);
int clear_channel(char *motif);
Channel *get_channel(char *name);
int set_topic(char *name,char *topic,char *auteur,long date);
int user_join(char *name,User *use);
UserList *user_part(char *name,User *use);
void clear_uliste(Channel *channel);
int user_part_allchan(User *use,char *mess);
void set_Mode_Chan(Channel *channel , char mode , int on_off);
void set_Mode_Status(Channel *channel , char *nick, char mode , int on_off);
long Channel_t();
char *list_Mode_Chan(Channel *channel);
void del_ban(Channel *channel,char *mask,long time_t);
void new_ban(Channel *channel,char *mask,long time_t);
void clear_ban(Channel *channel);
int is_onchan(Channel *chan , User *use);
char *chanList(User *use);
#endif




