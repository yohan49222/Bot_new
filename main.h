#ifndef MAIN_H

#define MAIN_H

#ifdef WIN32

	#include <windows.h>
	#define strcasecmp stricmp
	#define strncasecmp strnicmp
	#define snprintf _snprintf
	#define sleep Sleep

#else

	#include <sys/time.h>
	#include <pthread.h>

#endif

/** include standard **/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <assert.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <regex.h>
#include <setjmp.h>
#include <sys/utsname.h>



/** include perso **/
#include "error.h"
#include "infosystem.h"
#include "log.h"
#include "ircSocket.h"
#include "message.h"
#include "send.h"
#include "user.h"
#include "channel.h"
#include "raw.h"
#include "raw_numeric.h"
#include "raw_string.h"
#include "bot_clone.h"
#include "command.h"
#include "timeout.h"
#include "protection.h"
#include "nickserv.h"
#include "operserv.h"
#include "radio.h"
#include "antispam.h"
#include "coleen.h"
#include "globalserv.h"
#include "principale.h"
#include "masstoolz.h"
#include "global_message.h"
#include "my_regex.h"
#include "antiproxy.h"
#include "TKL.h"
#include "scrabble.h"

#define USETHREAD 1
#define MAXLEN 2048
#define TRUE 1
#define FALSE 0

#define DEBUG_IRC

typedef struct Config
{
	/** Parametre du bot principale et du link **/
	char *botnick;		/* pseudo du bot principale */ 
	char *real;		/* realname du bot principale */
	char *flags;		/* flag du bot principale */
	char *server;		/* ip/host du bot */
	char *host;		/* host du link */
	char *hostc;		/* complement vhost */
	char *serverpass;	/* pass du link */
	char *service;		/* channel de service */
	int port;		/* port de connexion du link */

	int use_protect;	/* utilisation des protections */
	int use_nickserv;	/* utilisation de nickserv */
	int use_operserv;	/* utilisation de operserv */
	int use_radio;		/* utilisation de radio */
	int use_antispam;	/* utilisation des Antispam */
	int use_coleen;		/* utilisation de Coleen */
	int use_global;		/* utilisation de GlobalServ */
	int use_masstoolz;	/* utilisation de MassToolZ */
	int use_antiproxy;	/* utilisation de l'anti_proxy */

	int use_jeux;	/* utilisation du scrabble */

}Config;

int load_config( char *Fichier);
void rehash();
char *heure_fr(long t);
char *time_fr(long t);
unsigned my_rand(unsigned N);
int match(char *ma, char *na);

#endif



