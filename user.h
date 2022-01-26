#ifndef USER_H

#define USER_H

#define IS_CLONE 	0x00000001
#define IS_PROTECT 	0x00000002

#define U_MODE_A  0x00000001
#define U_MODE_B  0x00000002
#define U_MODE_C  0x00000004
#define U_MODE_D  0x00000008
#define U_MODE_G  0x00000010
#define U_MODE_H  0x00000020
#define U_MODE_K  0x00000040
#define U_MODE_L  0x00000080
#define U_MODE_N  0x00000100
#define U_MODE_O  0x00000200
#define U_MODE_R  0x00000400
#define U_MODE_S  0x00000800
#define U_MODE_T  0x00001000
#define U_MODE_V  0x00002000
#define U_MODE_W  0x00004000
#define U_MODE_X  0x00008000
#define U_MODE_Z  0x00010000

#define U_MODE_a  0x00000001
#define U_MODE_b  0x00000002
#define U_MODE_c  0x00000004
#define U_MODE_d  0x00000008
#define U_MODE_g  0x00000010
#define U_MODE_h  0x00000020
#define U_MODE_i  0x00000040
#define U_MODE_k  0x00000080
#define U_MODE_n  0x00000100
#define U_MODE_o  0x00000200
#define U_MODE_p  0x00000400
#define U_MODE_q  0x00000800
#define U_MODE_r  0x00001000
#define U_MODE_s  0x00002000
#define U_MODE_t  0x00004000
#define U_MODE_v  0x00008000
#define U_MODE_w  0x00010000
#define U_MODE_x  0x00020000
#define U_MODE_z  0x00080000

/**
	************************
	** Struture des users **
	************************
**/
typedef struct User
{
	char *nick;
	char *handle;
	char *host;
	char *vhost;
	char *real;
	char *server;
	char *ip;
	long Ctime;
	long Ltime;

	int option;		

	int ModeGlobMaj;
	int ModeGlobMin;

	char *Access_Coleen_pseudo;
	int Access_Coleen;
	char *nick_jeux;

	int Threads_pid;

	struct User *precedent;
	struct User *suivant;

}User;



/**
	** Gestions des users **
**/

User *new_user(char *nick,char *handle,char *host,char *real,long Ctime,char *server);
User *get_user(char *nick);
int del_user(char *nick,char *mess);
int clear_user(char *motif);

int set_nick(char *nick,char *newnick);
int set_handle(char *nick,char *handle,char *from);
int set_vhost(char *nick,char *vhost,char *from);
int set_real(char *nick,char *real,char *from);
int set_Ltime(char *nick);
void set_flag(User *use,char *from, char flag,int onoff);
long User_t();
char *list_Mode_User(User *user);
int set_ip(User *use,char *ip);
int set_nick_jeux(User *use,char *newnick);



#endif


