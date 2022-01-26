#ifndef ERROR_H

#define ERROR_H


#define STRDUP(src,val)									\
	src = strdup(val); 								\
	if(!src)									\
	{										\
		ERREUR("Erreur Alloccation de %s -> %s:%ld", #src , __FILE__,__LINE__);	\
		exit(1);								\
	}										\



#define FREE(src)										\
	if(src)											\
	{											\
		free(src);									\
	}											\
	src = NULL;


void ERREUR(char *message, ...);
void ERREUR_SIGNAL(int sig);
void OK(char *message,...);

#endif

