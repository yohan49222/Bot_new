#include "main.h"

extern Config *myconfig;

void ERREUR(char *message,...)
{
	char t[MAXLEN];
	va_list arg;
	va_start(arg, message);
	vsprintf(t,message, arg);
	fsend_service(myconfig->botnick,"ERREUR : %s\n",t);
	printf("%s\n",t);
	put_log(t);
	close_log();
	va_end(arg);
}

void OK(char *message,...)
{
	char t[MAXLEN];
	va_list arg;
	va_start(arg, message);
	vsprintf(t,message, arg);
	fsend_service(myconfig->botnick,"ERREUR : %s\n",t);
	printf("%s\n",t);
	put_log(t);
	va_end(arg);
}


void ERREUR_SIGNAL(int sig)
{
	char t[MAXLEN];
	sprintf(t,"SIGNAL : pid %u -> SIGSEGV(%d)", getpid(),sig);
	fsend_service(myconfig->botnick,t);
	put_log(t);
	close_log();
	exit (1);
}

