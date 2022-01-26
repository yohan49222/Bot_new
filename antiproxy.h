#ifndef ANTIPROXY_H

#define ANTIPROXY_H

#define SOCK_CLEAN 		0
#define ANTI_SOCK_45 		1
#define ANTI_SOCK_HTTP 		2
#define ANTI_SOCK_WINGATE 	3
#define SECURE_PROXY 		4

#define FORMAT_NOBLACK		"\0034PROXY\0031 : %s n'est pas blacklist\xe9, Lancement du scanner"
#define FORMAT_INSCAN 		"\0034PROXY\0031 : %s n'est pas blacklist\xe9, ip dejas en cours de scan"
#define FORMAT_PROXYOK		"\0034PROXY\0031 : %s est connecte via proxy, type %s"
#define FORMAT_PROXYNO		"\0034PROXY\0031 : Pas de proxy detecte pour %s"
#define FORMAT_PROXYLI		"\0034PROXY\0031 : %s est banni"
#define FORMAT_CONNECTPROXY 	"\0034CONNEXION\0031 : %s ( %s!%s@%s ) ( ip : %s )"



/**
	Gestion des ip dejas scanne
**/

typedef struct Proxi_List
{
	char *ip;
	struct Proxi_List *precedent;
	struct Proxi_List *suivant;

}Proxi_List;


void load_db_proxy();
void save_db_proxy();
Proxi_List *new_proxy_ban(char *iphost);
int del_proxy_ban(char *host);
int clear_proxy_ban();
void liste_proxy_ban(char *nick);
int get_proxy_ban(char *host);

/**
	fornction proxy
**/
void init_proxy();
void unload_proxy();
char *resol_host(char *host);
unsigned int aton(char *ipaddr);
SOCKET new_socket(char *iphost,int port);
int proxy_read(SOCKET s, char *buf, size_t buflen);
int Sock_SetBlockMode (int sock, int blocking);

void kill_pthread(User *use);
void creat_thread_proxy(User *use);
void mainproxy(User *use);
int proxy_scan(char *ip);
int scan_proxy_socks(char *ip);
int scan_proxy_http(char *ip);
int scan_proxy_wingate(char *ip);


/**
	Raw proxy
**/
void ANTIPROXY_CONNECT(message_irc *message);
void ANTIPROXY_PRIVMSG(message_irc *message);
void ANTIPROXY_KILL(message_irc *message);
void ANTIPROXY_KICK(message_irc *message);
/**
	commande proxy
**/
void antiproxy_help(User *use , message_irc *message);
void antiproxy_add(User *use , message_irc *message);


#endif

