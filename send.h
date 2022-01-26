#ifndef SEND_H

#define SEND_H

void fsend_service(char *botnick,char *format, ... );
void fsend_com(char *format, ... );
void send_service(char *botnick,char *buf);
char *test_bot_for_send(char *nick);

#define testbot(nick) test_bot_for_send( #nick )

/*
Definition des messages ?affichier sur le channel de service
*/
#define USING_COMMANDE "\0034COMMANDE : \0031%s a utilis\xe9 la commande %s , Require flags : %s , User flags : %s"


#define FORMAT_NICK 		"\0034NICK\0031 : %s change son pseudo en : %s"
#define FORMAT_SETHAND 		"\0034SETHAND\0031 : %s change son handle en : %s"
#define FORMAT_CHGHAND 		"\0034CHGHAND\0031 : %s change le handle de %s en : %s"
#define FORMAT_SETVHOST 	"\0034SETVHOST\0031 : %s change son vhost en : %s"
#define FORMAT_CHGVHOST 	"\0034CHGVHOST\0031 : %s change le vhost de %s en : %s"
#define FORMAT_SETREAL 		"\0034SETREAL\0031 : %s change son realname en : %s"
#define FORMAT_CHGREAL 		"\0034CHGREAL\0031 : %s change le realname de %s en : %s"
#define FORMAT_SVSMODE		"\0034SVSMODE\0031 : %s met le(s) mode(s) %s sur %s"
#define FORMAT_CONNECT 		"\0034CONNEXION\0031 : %s ( %s!%s@%s ) ( Serveur : %s )"
#define FORMAT_CONNECT2 	"\0034CONNEXION\0031 : %s ( %s!%s@%s ) ( Serveur : %s ) ( Clone : %s )"
#define FORMAT_SVSPART 		"\0034SVSPART\0031 : %s utilise svspart sur %s , channel : %s"
#define FORMAT_SVSJOIN 		"\0034SVSJOIN\0031 : %s utilise svsjoin sur %s , channel : %s"
#define FORMAT_SVSKILL 		"\0034SVSKILL\0031 : %s kill %s pour : %s"
#define FORMAT_SVSNICK 		"\0034SVSNICK\0031 : %s change le pseudo de %s en %s"
#define FORMAT_SVSJUPE 		"\0034SVSJUPE\0031 : %s vient de brise le link de %s"
#define FORMAT_QUIT 		"\0034QUIT\0031 : %s a quitt\xe9 irc ( %s )"


#define FORMAT_NEWCHAN 		"\0034NEWCHAN\0031 : %s créé , TOPIC : %s "
#define FORMAT_DELCHAN 		"\0034DELCHAN\0031 : %s détruit sur %s "
#define FORMAT_TOPIC 		"\0034TOPIC\0031 : %s set le topic de %s : %s"
#define FORMAT_JOIN 		"\0034JOIN\0031 : %s rejoin %s"
#define FORMAT_PART 		"\0034PART\0031 : %s part de %s"

#define FORMAT_ISRESA 		"\0034ISRESA\0031 : %s est un pseudo réservé , Attente d'identification ..."
#define FORMAT_OKRESA 		"\0034OKRESA\0031 : %s vient de valider la réservation de son pseudo"
#define FORMAT_NEWRESA 		"\0034NEWRESA\0031 : %s vient de réserver son pseudo"
#define FORMAT_DELRESA 		"\0034DELRESA\0031 : %s vient de suprimer le pseudo %s"
#define FORMAT_REGMAIL		"\0034SETMAIL\0031 : %s vient de modifier le mail associé à son pseudo : %s"
#define FORMAT_REGPASS		"\0034SETPASS\0031 : %s vient de modifier le pass associé à son pseudo : *****"

#define FORMAT_GHOST		"\0034GHOST\0031 : %s vient d'utiliser la commande GHOST sur le pseudo : %s"

#define FORMAT_PROTECTOK	"\0034PROTECTION\0031 : %s est protégé "
#define FORMAT_NEWPROTECT	"\0034PROTECTION\0031 : le mask %s est maintenant protégé "
#define FORMAT_DELPROTECT	"\0034PROTECTION\0031 : le mask %s n'est plus protégé "


#define FORMAT_SETLOGON 	"\0034SETLOGON\0031 : changement du texte sur +%c ' %s ' par %s"

#define FORMAT_KICK 		"\0034KICK\0031 : %s kick %s de %s , motif : %s"
#define FORMAT_KILL 		"\0034KILL\0031 : %s kill %s ( %s )"
#define FORMAT_AWAY1 		"\0034AWAY\0031 : %s revient d'away"
#define FORMAT_AWAY2 		"\0034AWAY\0031 : %s passe en away ( %s )"

#define FORMAT_INVITE 		"\0034INVITE\0031 : %s invite %s sur %s"
#define FORMAT_WALLOPS		"\0034WALLOPS\0031 : %s -> %s"
#define FORMAT_NACHAT		"\0034NACHAT\0031 : %s -> %s"
#define FORMAT_CHATOPS		"\0034CHATOPS\0031 : %s -> %s"
#define FORMAT_ADCHAT		"\0034ADCHAT\0031 : %s -> %s"
#define FORMAT_GLOBOPS		"\0034GLOBOPS\0031 : %s -> %s"
#define FORMAT_SMO		"\0034SMO\0031 : %s -> %s"
#define FORMAT_SENDNO		"\0034SENDNO\0031 : %s -> %s"
//#define FORMAT_AUTHOK		"\0034AUTH\0031 : %s  vient de se auth"
//#define FORMAT_AUTHNOP		"\0034AUTH\0031 : %s  tente de se auth , mais son pass est éroné "
//#define FORMAT_AUTHNOID		"\0034AUTH\0031 :3 %s  tente de se auth , mais son login est éroné"

#define FORMAT_MODE 		"\0034MODE\0031 : %s met le mode %s sur %s"
#define FORMAT_MODECHAN		"\0034MODE\0031 : %s met le mode %c%c sur %s"
//#define FORMAT_MODE2 		"\0034MODE\0031 : changement de mode sur %s %s %s par %s"

#define FORMAT_MODEUSECHAN	"\0034MODE\0031 : %s met le mode %c%c %s sur %s"



#define FORMAT_SPAM		"\0034SPAM\0031 : de %s ( %s )"
#define FORMAT_SPAMUSERPROTECT	"\0034SPAM\0031 : de %s ( %s ) Usé protégé "
#define FORMAT_ADDMASKSPAM	"\0034SPAM\0031 : Nouveau Mask de Spam : %s"

//#define FORMAT_BANADD		"\0034BAN\0031 : ban sur %s par %s ( %s ) posé le : %s "
//#define FORMAT_BANDEL		"\0034UNBAN\0031 : unban sur %s par %s ( %s ) posé le : %s "
//#define FORMAT_BANLIS		"\0034BANLIST\0031 : %s par %s ( %s ) posé le : %s "

#define FORMAT_GLINE		"\0034GLINE\0031 : %s vient de gline le host : %s , motif : %s"
#define FORMAT_UNGLINE		"\0034UNGLINE\0031 : %s vient de ungline le host : %s"
#define FORMAT_GLINECLEAR	"\0034CLEARGLINE\0031 : %s vient de vider la liste des Glines"
#define FORMAT_GLINELIST	"\0034GLINE\0031 : les host %s est gline"

#define FORMAT_SHUN		"\0034SHUN\0031 : %s vient de shun le host : %s , motif : %s"
#define FORMAT_UNSHUN		"\0034UNSHUN\0031 : %s vient de retirer le shun sur le host : %s"


//#define FORMAT_NEWSCHANGE	"\0034NEWSCHANGE\0031 : %s vient de modifier la news"

//#define FORMAT_REGBOT		"\0034REGBOT\0031 : Nouveau bot enregistré sur %s , pseudo %s , Owner : %s"
//#define FORMAT_DELBOT		"\0034DELBOT\0031 : Bot supprimé sur %s , pseudo %s"
//#define FORMAT_LISTREGBOT	"\0034LISTREGBOT\0031 : Channel : %s , Bot : %s , Owner : %s"


//#define IRC_AIDE "NOTICE %s :Commande %s : %s"
//#define IRC_LINK_AIDE ":%s NOTICE %s :Commande pour %s -> %s : %s"



/*
Definition du protocole IRC ( IRCOP LINK )
*/

/* Syntax: :<pseudo> ADCHAT <text> */
#define LINK_COM_OPER_ADCHAT			":%s ADCHAT %s"
/* Syntax: :<pseudo> CHATOPS <message> */
#define LINK_COM_OPER_CHATOPS			":%s CHATOPS %s"
/* Syntax: :<pseudo> CHGHOST <nick> <host> */
#define LINK_COM_OPER_CHGHOST			":%s CHGHOST %s %s"
/* Syntax: :<pseudo> CHGIDENT <nick> <ident> */
#define LINK_COM_OPER_CHGIDENT			":%s CHGIDENT %s %s"
/* Syntax: :<pseudo> CHGNAME <nick> <name> */
#define LINK_COM_OPER_CHGNAME			":%s CHGNAME %s %s"
/* Syntax: :<pseudo> CLOSE */
#define LINK_COM_OPER_CLOSE			":%s CLOSE"
/* Syntax: :<pseudo> CONNECT <server> */
#define LINK_COM_OPER_CONNECT			":%s CONNECT %s"
/* Syntax: :<pseudo> CONNECT <server> [port] */
#define LINK_COM_OPER_CONNECT_PORT		":%s CONNECT %s %s"
/* Syntax: :<pseudo> DCCDENY <filename mask> <reason> */
#define LINK_COM_OPER_DCCDENY			":%s DCCDENY %s %s"
/* Syntax: :<pseudo> DIE <password>*/
#define LINK_COM_OPER_DIE			":%s DIE %s"
/* Syntax: :<pseudo> DNS <server> */
#define LINK_COM_OPER_DNS			":%s DNS %s"
/* Syntax: :<pseudo> GLINE *@*.idiot.net 900 Spammers */
#define LINK_COM_OPER_GLINE_TIME		":%s GLINE %s %s %s"
/* Syntax: :<pseudo> GLINE *@*.idiot.net Spammers */
#define LINK_COM_OPER_GLINE			":%s GLINE %s %s"
/* Syntax: :<pseudo> GLINE -*@*.idiot.net */
#define LINK_COM_OPER_GLINE_REM			":%s GLINE -%s"
/* Syntax: :<pseudo> GLOBOPS <message> */
#define LINK_COM_OPER_GLOBOPS			":%s GLOBOPS %s"
/* Syntax: :<pseudo> GZLINE *@4.16.200.* 900 Spammers */
#define LINK_COM_OPER_GZLINE			":%s GZLINE %s %s %s"
/* Syntax: :<pseudo> GZLINE -*@4.16.200.* */
#define LINK_COM_OPER_GZLINE_REM		":%s GZLINE -%s"
/* Syntax: :<pseudo> KILL yoyo49 idio */
#define LINK_COM_OPER_KILL			":%s KILL %s %s"
/* Syntax: :<pseudo> KLINE yoyo49 5000 idiot */
#define LINK_COM_OPER_KLINE_TIME		":%s KLINE %s %s %s"
/* Syntax: :<pseudo> KLINE yoyo49 idiot */
#define LINK_COM_OPER_KLINE			":%s KLINE %s %s"
/* Syntax: :<pseudo> KLINE -*!*@tele2.fr */
#define LINK_COM_OPER_KLINE_REM			":%s KLINE -%s"
/* Syntax: :<pseudo> LAG <server> */
#define LINK_COM_OPER_LAG			":%s LAG %s"
/* Syntax: :<pseudo> LOCOPS <message> */
#define LINK_COM_OPER_LOCOPS			":%s LOCOPS %s"
/* Syntax: :<pseudo> MKPASSWD <method> <password> */
#define LINK_COM_OPER_MKPASSWD			":%s MKPASSWD %s %s"
/* Syntax: :<pseudo> NACHAT <text> */
#define LINK_COM_OPER_NACHAT			":%s NACHAT %s"
/* Syntax: :<pseudo> OPER <uid> <password> */
#define LINK_COM_OPER_OPER			":%s OPER %s %s"
/* Syntax: :<pseudo> OPERMOTD */
#define LINK_COM_OPER_OPERMOTD			":%s OPERMOTD"
/* Syntax: :<pseudo> REHASH -motd */
#define LINK_COM_OPER_REHASH_MOT		":%s REHASH -motd"
/* Syntax: :<pseudo> REHASH -opermotd */
#define LINK_COM_OPER_REHASH_OPE		":%s REHASH -opermotd"
/* Syntax: :<pseudo> REHASH -botmotd */
#define LINK_COM_OPER_REHASH_BOT		":%s REHASH -botmotd"
/* Syntax: :<pseudo> REHASH -garbage */
#define LINK_COM_OPER_REHASH_GAR		":%s REHASH -garbage"
/* Syntax: :<pseudo> REHASH <server> -motd */
#define LINK_COM_OPER_REHASH_SMOT		":%s REHASH %s -motd"
/* Syntax: :<pseudo> REHASH <server> -opermotd */
#define LINK_COM_OPER_REHASH_SOPE		":%s REHASH %s -opermotd"
/* Syntax: :<pseudo> REHASH <server> -botmotd */
#define LINK_COM_OPER_REHASH_SBOT		":%s REHASH %s -botmotd"
/* Syntax: :<pseudo> REHASH <server> -garbage */
#define LINK_COM_OPER_REHASH_SGAR		":%s REHASH %s -garbage"
/* Syntax: :<pseudo> RESTART <password> */
#define LINK_COM_OPER_RESTART			":%s RESTART %s"
/* Syntax: :<pseudo> RESTART <password> <reason> */
#define LINK_COM_OPER_RESTART_RAIS		":%s RESTART %s %s"
/* Syntax: :<pseudo> RPING <servermask> */
#define LINK_COM_OPER_RPING			":%s RPING %s"
/* Syntax: :<pseudo> SAMODE <channel> <mode> */
#define LINK_COM_OPER_SAMODE			":%s SAMODE %s %s"
/* Syntax: :<pseudo> SAJOIN <nick> <channel>,[<channel2>..] */
#define LINK_COM_OPER_SAJOIN			":%s SAJOIN %s %s"
/* Syntax: :<pseudo> SAPART <nick> <channel>,[<channel2>..] */
#define LINK_COM_OPER_SAPART			":%s SAPART %s %s"
/* Syntax: :<pseudo> SAPART <nick> <channel>,[<channel2>..] [<comment>] */
#define LINK_COM_OPER_SAPART_MESS		":%s SAPART %s %s %s"
/* Syntax: :<pseudo> SDESC <New description> */
#define LINK_COM_OPER_SDESC			":%s SDESC %s"
/* Syntax: :<pseudo> SETHOST <new hostname> */
#define LINK_COM_OPER_SETHOST			":%s SETHOST %s"
/* Syntax: :<pseudo> SETIDENT <new ident> */
#define LINK_COM_OPER_SETIDENT			":%s SETIDENT %s"
/* Syntax: :<pseudo> SHUN */
#define LINK_COM_OPER_SHUN_LIST			":%s SHUN"
/* Syntax: :<pseudo> SHUN <nickname> <time> :<Reason> */
#define LINK_COM_OPER_SHUN_NICK			":%s SHUN %s %s :%s"
/* Syntax: :<pseudo> SHUN +<user@host> <time> :<Reason> */
#define LINK_COM_OPER_SHUN_HOST			":%s SHUN +%s %s :%s"
/* Syntax: :<pseudo> SHUN -<user@host> */
#define LINK_COM_OPER_SHUN_REM			":%s SHUN -%s"
/* Syntax: :<pseudo> SQUIT <server> */
#define LINK_COM_OPER_SQUIT			":%s SQUIT %s"
/* Syntax: :<pseudo> TEMPSHUN [+|-]<nickname> */
#define LINK_COM_OPER_TEMPSHUN			":%s TEMPSHUN %c%s"
/* Syntax: :<pseudo> TEMPSHUN [+|-]<nickname> [reason] */
#define LINK_COM_OPER_TEMPSHUN_RAI		":%s TEMPSHUN %c%s %s"
/* Syntax: :<pseudo> TRACE <servername|nickname> */
#define LINK_COM_OPER_TRACE			":%s TRACE %s"
/* Syntax: :<pseudo> TSCTL OFFSET +|- <time> */
#define LINK_COM_OPER_TSCTL_OFFSET		":%s TSCTL OFFSET %c %s"
/* Syntax: :<pseudo> TSCTL TIME */
#define LINK_COM_OPER_TSCTL_TIME		":%s TSCTL TIME"
/* Syntax: :<pseudo> TSCTL ALLTIME */
#define LINK_COM_OPER_TSCTL_ALLTIME		":%s TSCTL ALLTIME"
/* Syntax: :<pseudo> TSCTL SVSTIME <timestamp> */
#define LINK_COM_OPER_TSCTL_SVSTIME		":%s TSCTL SVSTIME %ld"
/* Syntax: :<pseudo> UNDCCDENY <filename mask>  */
#define LINK_COM_OPER_UNDCCDENY			":%s UNDCCDENY %s"
/* Syntax: :<pseudo> WALLOPS <message> */
#define LINK_COM_OPER_WALLOPS			":%s WALLOPS %s"
/* Syntax: :<pseudo> ZLINE *@127.0.0.1 2d Abuse */
#define LINK_COM_OPER_ZLINE_TIME		":%s ZLINE %s %s %s"
/* Syntax: :<pseudo> ZLINE *@127.0.0.1 Abuse */
#define LINK_COM_OPER_ZLINE			":%s ZLINE %s %s"
/* Syntax: :<pseudo> ZLINE -*@127.0.0.1 */
#define LINK_COM_OPER_ZLINE_REM			":%s ZLINE -%s"
#define LINK_TKL 				":%s TKL + G * %s %s %ld %ld : %s (Expire le %s)"
#define LINK_UNTKL 				":%s TKL - G %s %s %s"
#define COM_SERV_UNGLINE			":%s TKL - G %s %s %s"
#define COM_SERV_UNKLINE			":%s TKL - K %s %s %s"



/*
Definition du protocole IRC ( IRCOP SANS LINK )
*/

/* Syntax: ADCHAT <text> */
#define COM_OPER_ADCHAT				"ADCHAT %s"
/* Syntax: CHATOPS <message> */
#define COM_OPER_CHATOPS			"CHATOPS %s"
/* Syntax: CHGHOST <nick> <host> */
#define COM_OPER_CHGHOST			"CHGHOST %s %s"
/* Syntax: CHGIDENT <nick> <ident> */
#define COM_OPER_CHGIDENT			"CHGIDENT %s %s"
/* Syntax: CHGNAME <nick> <name> */
#define COM_OPER_CHGNAME			"CHGNAME %s %s"
/* Syntax: CLOSE */
#define COM_OPER_CLOSE				"CLOSE"
/* Syntax: CONNECT <server> */
#define COM_OPER_CONNECT			"CONNECT %s"
/* Syntax: CONNECT <server> [port] */
#define COM_OPER_CONNECT_PORT			"CONNECT %s %s"
/* Syntax: DCCDENY <filename mask> <reason> */
#define COM_OPER_DCCDENY			"DCCDENY %s %s"
/* Syntax: DIE <password>*/
#define COM_OPER_DIE				"DIE %s"
/* Syntax: DNS <server> */
#define COM_OPER_DNS				"DNS %s"
/* Syntax: GLINE *@*.idiot.net 900 Spammers */
#define COM_OPER_GLINE_TIME			"GLINE %s %s %s"
/* Syntax: GLINE *@*.idiot.net Spammers */
#define COM_OPER_GLINE				"GLINE %s %s"
/* Syntax: GLINE -*@*.idiot.net */
#define COM_OPER_GLINE_REM			"GLINE -%s"
/* Syntax: GLOBOPS <message> */
#define COM_OPER_GLOBOPS			"GLOBOPS %s"
/* Syntax: GZLINE *@4.16.200.* 900 Spammers */
#define COM_OPER_GZLINE				"GZLINE %s %s %s"
/* Syntax: GZLINE -*@4.16.200.* */
#define COM_OPER_GZLINE_REM			"GZLINE -%s"
/* Syntax: KILL yoyo49 idio */
#define COM_OPER_KILL				"KILL %s %s"
/* Syntax: KLINE yoyo49 5000 idiot */
#define COM_OPER_KLINE_TIME			"KLINE %s %s %s"
/* Syntax: KLINE yoyo49 idiot */
#define COM_OPER_KLINE				"KLINE %s %s"
/* Syntax: KLINE -*!*@tele2.fr */
#define COM_OPER_KLINE_REM			"KLINE -%s"
/* Syntax: LAG <server> */
#define COM_OPER_LAG				"LAG %s"
/* Syntax: LOCOPS <message> */
#define COM_OPER_LOCOPS				"LOCOPS %s"
/* Syntax: MKPASSWD <method> <password> */
#define COM_OPER_MKPASSWD			"MKPASSWD %s %s"
/* Syntax: NACHAT <text> */
#define COM_OPER_NACHAT				"NACHAT %s"
/* Syntax: OPER <uid> <password> */
#define COM_OPER_OPER				"OPER %s %s"
/* Syntax: OPERMOTD */
#define COM_OPER_OPERMOTD			"OPERMOTD"
/* Syntax: REHASH -motd */
#define COM_OPER_REHASH_MOT			"REHASH -motd"
/* Syntax: REHASH -opermotd */
#define COM_OPER_REHASH_OPE			"REHASH -opermotd"
/* Syntax: REHASH -botmotd */
#define COM_OPER_REHASH_BOT			"REHASH -botmotd"
/* Syntax: REHASH -garbage */
#define COM_OPER_REHASH_GAR			"REHASH -garbage"
/* Syntax: REHASH <server> -motd */
#define COM_OPER_REHASH_SMOT			"REHASH %s -motd"
/* Syntax: REHASH <server> -opermotd */
#define COM_OPER_REHASH_SOPE			"REHASH %s -opermotd"
/* Syntax: REHASH <server> -botmotd */
#define COM_OPER_REHASH_SBOT			"REHASH %s -botmotd"
/* Syntax: REHASH <server> -garbage */
#define COM_OPER_REHASH_SGAR			"REHASH %s -garbage"
/* Syntax: RESTART <password> */
#define COM_OPER_RESTART			"RESTART %s"
/* Syntax: RESTART <password> <reason> */
#define COM_OPER_RESTART_RAIS			"RESTART %s %s"
/* Syntax: RPING <servermask> */
#define COM_OPER_RPING				"RPING %s"
/* Syntax: SAMODE <channel> <mode> */
#define COM_OPER_SAMODE				"SAMODE %s %s"
/* Syntax: SAJOIN <nick> <channel>,[<channel2>..] */
#define COM_OPER_SAJOIN				"SAJOIN %s %s"
/* Syntax: SAPART <nick> <channel>,[<channel2>..] */
#define COM_OPER_SAPART				"SAPART %s %s"
/* Syntax: SAPART <nick> <channel>,[<channel2>..] [<comment>] */
#define COM_OPER_SAPART_MESS			"SAPART %s %s %s"
/* Syntax: SDESC <New description> */
#define COM_OPER_SDESC				"SDESC %s"
/* Syntax: SETHOST <new hostname> */
#define COM_OPER_SETHOST			"SETHOST %s"
/* Syntax: SETIDENT <new ident> */
#define COM_OPER_SETIDENT			"SETIDENT %s"
/* Syntax: SHUN */
#define COM_OPER_SHUN_LIST			"SHUN"
/* Syntax: SHUN <nickname> <time> :<Reason> */
#define COM_OPER_SHUN_NICK			"SHUN %s %s :%s"
/* Syntax: SHUN +<user@host> <time> :<Reason> */
#define COM_OPER_SHUN_HOST			"SHUN +%s %s :%s"
/* Syntax: SHUN -<user@host> */
#define COM_OPER_SHUN_REM			"SHUN -%s"
/* Syntax: SQUIT <server> */
#define COM_OPER_SQUIT				"SQUIT %s"
/* Syntax: TEMPSHUN [+|-]<nickname> */
#define COM_OPER_TEMPSHUN			"TEMPSHUN %c%s"
/* Syntax: TEMPSHUN [+|-]<nickname> [reason] */
#define COM_OPER_TEMPSHUN_RAI			"TEMPSHUN %c%s %s"
/* Syntax: TRACE <servername|nickname> */
#define COM_OPER_TRACE				"TRACE %s"
/* Syntax: TSCTL OFFSET +|- <time> */
#define COM_OPER_TSCTL_OFFSET			"TSCTL OFFSET %c %s"
/* Syntax: TSCTL TIME */
#define COM_OPER_TSCTL_TIME			"TSCTL TIME"
/* Syntax: TSCTL ALLTIME */
#define COM_OPER_TSCTL_ALLTIME			"TSCTL ALLTIME"
/* Syntax: TSCTL SVSTIME <timestamp> */
#define COM_OPER_TSCTL_SVSTIME			"TSCTL SVSTIME %ld"
/* Syntax: UNDCCDENY <filename mask>  */
#define COM_OPER_UNDCCDENY			"UNDCCDENY %s"
/* Syntax: WALLOPS <message> */
#define COM_OPER_WALLOPS			"WALLOPS %s"
/* Syntax: ZLINE *@127.0.0.1 2d Abuse */
#define COM_OPER_ZLINE_TIME			"ZLINE %s %s %s"
/* Syntax: ZLINE *@127.0.0.1 Abuse */
#define COM_OPER_ZLINE				"ZLINE %s %s"
/* Syntax: ZLINE -*@127.0.0.1 */
#define COM_OPER_ZLINE_REM			"ZLINE -%s"


/*
Definition du protocole IRC ( USER LINK )
*/
/* Syntax: :<pseudo> ADMIN */
#define LINK_COM_USER_ADMIN			":%s ADMIN"
/* Syntax: :<pseudo> ADMIN <server> */
#define LINK_COM_USER_ADMIN_OPT			":%s ADMIN %s"
/* Syntax: :<pseudo> AWAY */
#define LINK_COM_USER_AWAY			":%s AWAY"
/* Syntax: :<pseudo> AWAY <reason> */
#define LINK_COM_USER_AWAY_RAI			":%s AWAY %s"
/* Syntax: :<pseudo> CREDITS */
#define LINK_COM_USER_CREDITS			":%s CREDITS"
/* Syntax: :<pseudo> CREDITS <server> */
#define LINK_COM_USER_CREDITS_OPT		":%s CREDITS %s"
/* Syntax: :<pseudo> CYCLE <chan1>,<chan2>,<chan3> */
#define LINK_COM_USER_CYCLE			":%s CYCLE %s"
/* Syntax: :<pseudo> DALINFO */
#define LINK_COM_USER_DALINFO			":%s DALINFO"
/* Syntax: :<pseudo> DALINFO <server> */
#define LINK_COM_USER_DALINFO_OPT		":%s DALINFO %s"
/* Syntax: :<pseudo> INVITE */
#define LINK_COM_USER_INVITE			":%s INVITE"
/* Syntax: :<pseudo> INVITE [<user> <channel>] */
#define LINK_COM_USER_INVITE_OPT		":%s INVITE %s %s"
/* Syntax: :<pseudo> ISON <user> */
#define LINK_COM_USER_ISON			":%s ISON %s"
/* Syntax: :<pseudo> JOIN <chan> */
#define LINK_COM_USER_JOIN			":%s JOIN %s"
/* Syntax: :<pseudo> JOIN <chan> <key1> */
#define LINK_COM_USER_JOIN_KEY			":%s JOIN %s %s"
/* Syntax: :<pseudo> KICK <channel> <user> [reason] */
#define LINK_COM_USER_KICK			":%s KICK %s %s"
/* Syntax: :<pseudo> KICK <channel> <user> [reason] */
#define LINK_COM_USER_KICK_RAI			":%s KICK %s %s %s"
/* Syntax: :<pseudo> KNOCK <channel> <message> */
#define LINK_COM_USER_KNOCK			":%s KNOCK %s %s"
/* Syntax: :<pseudo> LICENSE */
#define LINK_COM_USER_LICENSE			":%s LICENSE"
/* Syntax: :<pseudo> LICENSE <server> */
#define LINK_COM_USER_LICENSE_OPT		":%s LICENSE %s"
/* Syntax: :<pseudo> LINKS */
#define LINK_COM_USER_LINKS			":%s LINKS"
/* Syntax: :<pseudo> LIST */
#define LINK_COM_USER_LIST			":%s LIST"
/* Syntax: :<pseudo> LUSERS */
#define LINK_COM_USER_LUSERS			":%s LUSERS"
/* Syntax: :<pseudo> LUSERS [server] */
#define LINK_COM_USER_LUSERS_OPT		":%s LUSERS %s"
/* Syntax: :<pseudo> MAP */
#define LINK_COM_USER_MAP			":%s MAP"
/* Syntax: :<pseudo> MODE <user> <mode> */
#define LINK_COM_USER_MODE			":%s MODE %s %s"
/* Syntax: :<pseudo> MODE <channel> <mode> <user>*/
#define LINK_COM_USER_MODE_USE			":%s MODE %s %s %s"
/* Syntax: :<pseudo> MOTD */
#define LINK_COM_USER_MOTD			":%s MOTD"
/* Syntax: :<pseudo> MOTD <server> */
#define LINK_COM_USER_MOTD_OPT			":%s MOTD %s"
/* Syntax: :<pseudo> NAMES <channel> */
#define LINK_COM_USER_NAMES			":%s NAMES %s"
/* Syntax: :<pseudo> NICK <new nickname> */
#define LINK_COM_USER_NICK			":%s NICK %s"
/* Syntax: :<pseudo> NOTICE <nick> <text> */
#define LINK_COM_USER_NOTICE			":%s NOTICE %s %s"
/* Syntax: :<pseudo> PART <chan>,<chan2>,<chan3>,<chan4> */
#define LINK_COM_USER_PART			":%s PART %s"
/* Syntax: :<pseudo> PART <chan>,<chan2>,<chan3>,<chan4> <reason> */
#define LINK_COM_USER_PART_RAI			":%s PART %s %s"
/* Syntax: :<pseudo> PING <server> */
#define LINK_COM_USER_PING			":%s PING %s"
/* Syntax: :<pseudo> PONG <server> */
#define LINK_COM_USER_PONG			":%s PONG %s"
/* Syntax: :<pseudo> PRIVMSG <nick> <text> */
#define LINK_COM_USER_PRIVMSG			":%s PRIVMSG %s %s"
/* Syntax: :<pseudo> QUIT <reason> */
#define LINK_COM_USER_QUIT			":%s QUIT :quit: %s"
/* Syntax: :<pseudo> RULES */
#define LINK_COM_USER_RULES			":%s RULES"
/* Syntax: :<pseudo> RULES <server> */
#define LINK_COM_USER_RULES_OPT			":%s RULES %s"
/* Syntax: :<pseudo> SETNAME <New Real Name> */
#define LINK_COM_USER_SETNAME			":%s SETNAME %s"
/* Syntax: :<pseudo> SILENCE +nickname */
#define LINK_COM_USER_SILENCE_ADD		":%s SILENCE +%s"
/* Syntax: :<pseudo> SILENCE -nickname */
#define LINK_COM_USER_SILENCE_REM		":%s SILENCE -%s"
/* Syntax: :<pseudo> SILENCE */
#define LINK_COM_USER_SILENCE			":%s SILENCE"
/* Syntax: :<pseudo> STATS */
#define LINK_COM_USER_STATS			":%s STATS"
/* Syntax: :<pseudo> STATS <flags> */
#define LINK_COM_USER_STATS_OPT			":%s STATS %c"
/* Syntax: :<pseudo> TIME */
#define LINK_COM_USER_TIME			":%s TIME"
/* Syntax: :<pseudo> TIME <server> */
#define LINK_COM_USER_TIME_OPT			":%s TIME %s"
/* Syntax: :<pseudo> TOPIC <channel> */
#define LINK_COM_USER_TOPIC			":%s TOPIC %s"
/* Syntax: :<pseudo> TOPIC <channel> <new topic>*/
#define LINK_COM_USER_TOPIC_SET			":%s TOPIC %s :%s"
/* Syntax: :<pseudo> USERHOST <nickname> */
#define LINK_COM_USER_USERHOST			":%s USERHOST %s"
/* Syntax: :<pseudo> USERIP <nickname> */
#define LINK_COM_USER_USERIP			":%s USERIP %s"
/* Syntax: :<pseudo> VERSION */
#define LINK_COM_USER_VERSION			":%s VERSION"
/* Syntax: :<pseudo> VERSION <server> */
#define LINK_COM_USER_VERSION_OPT		":%s VERSION %s"
/* Syntax: :<pseudo> VHOST <login> <password> */
#define LINK_COM_USER_VHOST			":%s VHOST %s %s"
/* Syntax: :<pseudo> WATCH +nick1 */
#define LINK_COM_USER_WATCH_ADD			":%s WATCH +%s"
/* Syntax: :<pseudo> WATCH -nick */
#define LINK_COM_USER_WATCH_REM			":%s WATCH -%s"
/* Syntax: :<pseudo> WATCH */
#define LINK_COM_USER_WATCH			":%s WATCH"
/* Syntax: :<pseudo> WHO <char> <char> */
#define LINK_COM_USER_WHO			":%s WHO %s "
/* Syntax: :<pseudo> WHOIS <user> */
#define LINK_COM_USER_WHOIS			":%s WHOIS %s"
/* Syntax: :<pseudo> WHOWAS <nickname> */
#define LINK_COM_USER_WHOWAS			":%s WHOWAS %s"

/*
Definition du protocole IRC ( USER SANS LINL)
*/
/* Syntax: USER <pseudo> 0 * :<realname> */
#define COM_USER_USER 				"USER %s 0 * :%s"
/* Syntax: ADMIN */
#define COM_USER_ADMIN				"ADMIN"
/* Syntax: ADMIN <server> */
#define COM_USER_ADMIN_OPT			"ADMIN %s"
/* Syntax: AWAY */
#define COM_USER_AWAY				"AWAY"
/* Syntax: AWAY <reason> */
#define COM_USER_AWAY_RAI			"AWAY %s"
/* Syntax: CREDITS */
#define COM_USER_CREDITS			"CREDITS"
/* Syntax: CREDITS <server> */
#define COM_USER_CREDITS_OPT			"CREDITS %s"
/* Syntax: CYCLE <chan1>,<chan2>,<chan3> */
#define COM_USER_CYCLE				"CYCLE %s"
/* Syntax: DALINFO */
#define COM_USER_DALINFO			"DALINFO"
/* Syntax: DALINFO <server> */
#define COM_USER_DALINFO_OPT			"DALINFO %s"
/* Syntax: INVITE */
#define COM_USER_INVITE				"INVITE"
/* Syntax: INVITE [<user> <channel>] */
#define COM_USER_INVITE_OPT			"INVITE %s %s"
/* Syntax: ISON <user> */
#define COM_USER_ISON				"ISON %s"
/* Syntax: JOIN <chan> */
#define COM_USER_JOIN				"JOIN %s"
/* Syntax: JOIN <chan> <key1> */
#define COM_USER_JOIN_KEY			"JOIN %s %s"
/* Syntax: KICK <channel> <user> [reason] */
#define COM_USER_KICK				"KICK %s %s"
/* Syntax: KICK <channel> <user> [reason] */
#define COM_USER_KICK_RAI			"KICK %s %s %s"
/* Syntax: KNOCK <channel> <message> */
#define COM_USER_KNOCK				"KNOCK %s %s"
/* Syntax: LICENSE */
#define COM_USER_LICENSE			"LICENSE"
/* Syntax: LICENSE <server> */
#define COM_USER_LICENSE_OPT			"LICENSE %s"
/* Syntax: LINKS */
#define COM_USER_LINKS				"LINKS"
/* Syntax: LIST */
#define COM_USER_LIST				"LIST"
/* Syntax: LUSERS */
#define COM_USER_LUSERS				"LUSERS"
/* Syntax: LUSERS [server] */
#define COM_USER_LUSERS_OPT			"LUSERS %s"
/* Syntax: MAP */
#define COM_USER_MAP				"MAP"
/* Syntax: MODE <channel/user> <mode> */
#define COM_USER_MODE				"MODE %s %s"
/* Syntax: MOTD */
#define COM_USER_MOTD				"MOTD"
/* Syntax: MOTD <server> */
#define COM_USER_MOTD_OPT			"MOTD %s"
/* Syntax: NAMES <channel> */
#define COM_USER_NAMES				"NAMES %s"
/* Syntax: NICK <new nickname> */
#define COM_USER_NICK				"NICK %s"
/* Syntax: NOTICE <nick> <text> */
#define COM_USER_NOTICE				"NOTICE %s %s"
/* Syntax: PART <chan>,<chan2>,<chan3>,<chan4> */
#define COM_USER_PART				"PART %s"
/* Syntax: PART <chan>,<chan2>,<chan3>,<chan4> <reason> */
#define COM_USER_PART_RAI			"PART %s %s"
/* Syntax: PING <server> */
#define COM_USER_PING				"PING %s"
/* Syntax: PONG <server> */
#define COM_USER_PONG				"PONG %s"
/* Syntax: PRIVMSG <nick> <text> */
#define COM_USER_PRIVMSG			"PRIVMSG %s %s"
/* Syntax: QUIT <reason> */
#define COM_USER_QUIT				"QUIT :quit: %s"
/* Syntax: RULES */
#define COM_USER_RULES				"RULES"
/* Syntax: RULES <server> */
#define COM_USER_RULES_OPT			"RULES %s"
/* Syntax: SETNAME <New Real Name> */
#define COM_USER_SETNAME			"SETNAME %s"
/* Syntax: SILENCE +nickname */
#define COM_USER_SILENCE_ADD			"SILENCE +%s"
/* Syntax: SILENCE -nickname */
#define COM_USER_SILENCE_REM			"SILENCE -%s"
/* Syntax: SILENCE */
#define COM_USER_SILENCE			"SILENCE"
/* Syntax: STATS */
#define COM_USER_STATS				"STATS"
/* Syntax: STATS <flags> */
#define COM_USER_STATS_OPT			"STATS %s"
/* Syntax: TIME */
#define COM_USER_TIME				"TIME"
/* Syntax: TIME <server> */
#define COM_USER_TIME_OPT			"TIME %s"
/* Syntax: TOPIC <channel> */
#define COM_USER_TOPIC				"TOPIC %s"
/* Syntax: TOPIC <channel> <new topic>*/
#define COM_USER_TOPIC_SET			"TOPIC %s :%s"
/* Syntax: USERHOST <nickname> */
#define COM_USER_USERHOST			"USERHOST %s"
/* Syntax: USERIP <nickname> */
#define COM_USER_USERIP				"USERIP %s"
/* Syntax: VERSION */
#define COM_USER_VERSION			"VERSION"
/* Syntax: VERSION <server> */
#define COM_USER_VERSION_OPT			"VERSION %s"
/* Syntax: VHOST <login> <password> */
#define COM_USER_VHOST				"VHOST %s %s"
/* Syntax: WATCH +nick1 */
#define COM_USER_WATCH_ADD			"WATCH +%s"
/* Syntax: WATCH -nick */
#define COM_USER_WATCH_REM			"WATCH -%s"
/* Syntax: WATCH */
#define COM_USER_WATCH				"WATCH"
/* Syntax: WHO <char> <char> */
#define COM_USER_WHO				"WHO %s"
/* Syntax: WHOIS <user> */
#define COM_USER_WHOIS				"WHOIS %s"
/* Syntax: WHOWAS <nickname> */
#define COM_USER_WHOWAS				"WHOWAS %s"

/*
Definition du protocole IRC ( SERVICE ULINE UNIQUEMENT )
*/
/* Syntax: PASS <pass> */
#define COM_SERV_PASS				"PASS %s"
/* Syntax: SERVER <serber name> :<server description> */
#define COM_SERV_SERVER				"SERVER %s 1 :%s"
/* Syntax: NICK <pseudo> 1 <timestamp> <handle> <host> <server> 0 <flags> * :<realname> */
#define COM_SERV_NICK				"NICK %s 1 %ld %s %s %s 0 %s * :%s"
/* Syntax: :<uline> SQLINE <nickmask> :<Reason> */
#define COM_SERV_SQLINE				":%s SQLINE %s :%s"
/* Syntax: :<uline> SVS2MODE <nickname> <usermodes> */
#define COM_SERV_SVS2MODE			":%s SVS2MODE %s %s"
/* Syntax: :<uline> SVS2SNO <nickname> <snomasks> */
#define COM_SERV_SVS2SNO			":%s SVS2SNO %s %s"
/* Syntax: :<uline> SVSFLINE + file :reason */
#define COM_SERV_SVSFLINE_ADD			":%s SVSFLINE + %s :%s"
/* Syntax: :<uline> SVSFLINE - file */
#define COM_SERV_SVSFLINE_REM			":%s SVSFLINE - %s"
/* Syntax: :<uline> SVSJOIN <nick> <channel>[,<channel2>..] */
#define COM_SERV_SVSJOIN			":%s SVSJOIN %s %s"
/* Syntax: :<uline> SVSJOIN <nick> <channel>[,<channel2>..] [key1[,key2[..]]] */
#define COM_SERV_SVSJOIN_KEY			":%s SVSJOIN %s %s %s"
/* Syntax: :<uline> SVSKILL <user> :<reason> */
#define COM_SERV_SVSKILL			":%s SVSKILL %s :%s"
/* Syntax: :<uline> SVSLUSERS <server> <globalmax|-1> <localmax|-1> */
#define COM_SERV_SVSLUSERS			":%s SVSLUSERS %s %s %s"
/* Syntax: :<uline> SVSMODE <nickname> <usermode> */
#define COM_SERV_SVSMODE			":%s SVSMODE %s %s"
/* Syntax: :<uline> SVSNICK <nickname> <new nickname> <timestamp> */
#define COM_SERV_SVSNICK			":%s SVSNICK %s %s %ld"
/* Syntax: :<uline> SVSNLINE +/- <reason_for_ban> :<realname> */
#define COM_SERV_SVSNLINE			":%s SVSNLINE %c %s :%s"
/* Syntax: :<uline> SVSNOOP <server> <+/-> */
#define COM_SERV_SVSNOOP			":%s SVSNOOP %s %c"
/* Syntax: :<uline> SVSO <nick> <+operflags> */
#define COM_SERV_SVSO				":%s SVSO %s %s"
/* Syntax: :<uline> SVSPART <nick> <channel>[,<channel2>..]  [<comment>] */
#define COM_SERV_SVSPART			":%s SVSPART %s %s"
/* Syntax: :<uline> SVSSILENCE <nick> :<silence parameters> */
#define COM_SERV_SVSSILENCE			":%s SVSSILENCE %s :%s"
/* Syntax: :<uline> SVSSNO <nickname> <snomasks> */
#define COM_SERV_SVSSNO				":%s SVSSNO %s %s"
/* Syntax: :<uline> SVSWATCH <nick> :<watch parameters> */
#define COM_SERV_SWATCHS			":%s SVSWATCH %s :%s"
/* Syntax: :<uline> SWHOIS <nick> :<message> */
#define COM_SERV_SWHOIS				":%s SWHOIS %s :%s"
/* Syntax: :<uline> UNSQLINE <nickmask> */
#define COM_SERV_UNSQLINE			":%s UNSQLINE %s"

#define COM_SERV_UNGLINE			":%s TKL - G %s %s %s"
#define COM_SERV_UNKLINE			":%s TKL - K %s %s %s"


#define COM_SERV_EOS				":%s EOS"


#endif
