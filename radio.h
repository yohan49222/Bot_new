#ifndef RADIO_H

#define RADIO_H


typedef struct Radio
{
	
	char *serverradio;
	int serverradioport;
	char *channelradio;
	char *urlradiostream;
	char *urlradiomedia;
	char *urlradiowinamp;

	char *songtitle;

}Radio;

void RADIO_PRIVMSG(message_irc *message);
void RADIO_KILL(message_irc *message);
void RADIO_KICK(message_irc *message);
void init_radio();
void unload_radio();

void load_config_radio(char *Fichier );

void *get_url();


SOCKET check_connect_radio(char *iphost,int port);

void parse_xml(char *c);
void Remplacer(char *ligne,char *dep, char *arr);
void encode(char *phrase);


char *creat_hostsock_radiostream(char *serveur);
char *creat_url_radiostream(char *url);

void pub_radio();
void radio_live(User *use ,message_irc *message);
void radio_help(User *use , message_irc *message);

void creat_threads();
void clear_url_radio();

char *str_sub (const char *s, unsigned int start, unsigned int end);

#endif

