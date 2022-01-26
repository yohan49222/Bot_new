#ifndef MESSAGE_H

#define MESSAGE_H

/* structure des messages entrant */
typedef struct message_irc
{
	char **RAW;
	char **ARG;
	char *message;

	int n_raw;
	int n_arg;
}message_irc;



/* prototype */
void prep_message( char *src ,message_irc *message );
void retirecouleur(char *src,char *retour);
void traitement( char *src );



#endif

