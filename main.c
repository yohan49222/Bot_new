#include "main.h"

Config *myconfig = NULL;

char *my_version = "3.0.0";

int main()
{
	int result = 0;
	int xfork = 1;
	struct sigaction action;

	action.sa_handler = ERREUR_SIGNAL;
	sigemptyset (&(action.sa_mask));
	action.sa_flags = 0;

	if(sigaction (SIGSEGV, &action, NULL) != 0)
	{
		fprintf (stderr, "Erreur de gestion %d\n", errno);
		exit(1);
	}

	init_Raw_Gestion();
	init_log();

	result = load_config("bot.conf");
	if(result == 1)
	{

		xfork = fork();
		switch(xfork)
		{
	    	case -1:		// error
			printf( "erreur fork!! Fin!\n");
			return 0;

		default:		// parent
			exit(0);
			break;

		case 0:
			printf( "Demarrage en arriere plan\n");
			if(connect_serveur())
				pool_one();
			break;
		}
	}
	else
	{
		put_log("Erreur de configuration , fonction main");
		return 0;
	}
	return 1;
}

int load_config( char *Fichier)
{
	FILE *myFile;
	char ligne[256];
	char *var = NULL;
	char *val = NULL;
	char *p;
	myconfig = (Config*)malloc(sizeof(Config));
	if(!myconfig)
	{
		put_log("Erreur Creation de myconfig , fonction load_config");
		return 0;
	}

	myconfig->botnick = NULL;
	myconfig->real = NULL;
	myconfig->server = NULL;
	myconfig->port = 0;
	myconfig->service = NULL;
	myconfig->serverpass = NULL;
	myconfig->host = NULL;
	myconfig->hostc = NULL;
	myconfig->flags = NULL;

	myconfig->use_protect = 0;
	myconfig->use_nickserv = 0;
	myconfig->use_operserv = 0;
	myconfig->use_radio = 0;
	myconfig->use_antispam = 0;
	myconfig->use_coleen = 0;
	myconfig->use_global = 0;
	myconfig->use_masstoolz = 0;
	myconfig->use_antiproxy = 0;
	myconfig->use_jeux = 0;

	myFile = fopen(Fichier, "r");
	if(!myFile)
	{
		put_log("Erreur lecture du fichier de configuration , fonction load_config");
		return 0;
	}

	while(fgets(ligne, sizeof ligne, myFile))
	{
		if( (ligne[0] != '#') && (ligne[0] != '/') && (strlen(ligne) > 1 ))
		{
			p = strchr(ligne, '\n');
			if(p)
				*p = '\0';

			if(*ligne)
			{
				p = strchr(ligne, '\r');
				if (p)
					*p = '\0';
			}


			if(*ligne)
			{
				var = strtok(ligne , "\"");
				sscanf(var,"%s",var);
				val = strtok(NULL , "\"");
				
				if(!val)
					continue;

				if(var && val)
				{

					/* Pseudo */
					if(!strcmp("BOTNICK",var))
					{
						STRDUP(myconfig->botnick,val)
					}
					/* Realname du Bot */
					if(!strcmp("REAL",var))
					{
						STRDUP(myconfig->real,val)
					}
						
					/* Ip du server ou son domaine */
					if(!strcmp("SERVER",var))
					{
						STRDUP(myconfig->server,val);
					}

					/* Port de connexion au server */
					if(!strcmp("PORT",var))
						myconfig->port = atoi(val);

					/* Channel de service */
					if(!strcmp("SERVICE",var))
					{
						STRDUP(myconfig->service,val);
					}
					/* Link */
					if(!strcmp("HOST",var))
					{
						STRDUP(myconfig->host,val);
					}
					/* Complement d'host */
					if(!strcmp("HOSTC",var))
					{
						STRDUP(myconfig->hostc,val);
					}
					/* Flags du bots */
					if(!strcmp("FLAGS",var))
					{
						STRDUP(myconfig->flags,val);
					}
					/* Pass du link */
					if(!strcmp("SERVERPASS",var))
					{
						STRDUP(myconfig->serverpass,val);
					}
					/* Use protection */
					if(!strcmp("USEPROTECT",var))
						myconfig->use_protect = atoi(val);

					/* Use nickserv */
					if(!strcmp("USENICKSERV",var))
						myconfig->use_nickserv = atoi(val);
					
					/* Use operserv */
					if(!strcmp("USEOPERSERV",var))
						myconfig->use_operserv = atoi(val);

					/* Use radio */
					if(!strcmp("USERADIO",var))
						myconfig->use_radio = atoi(val);

					/* Use antispam */
					if(!strcmp("USEANTISPAM",var))
						myconfig->use_antispam = atoi(val);

					/* Use Coleen */
					if(!strcmp("USECOLEEN",var))
						myconfig->use_coleen = atoi(val);

					/* Use MasstoolZ */
					if(!strcmp("USEMASSTOOLZ",var))
						myconfig->use_masstoolz = atoi(val);

					/* Use globalserv */
					if(!strcmp("USEGLOBALSERV",var))
						myconfig->use_global = atoi(val);

					/* Use globalserv */
					if(!strcmp("USEANTIPROXY",var))
						myconfig->use_antiproxy = atoi(val);

					/* Use jeux */
					if(!strcmp("USEJEUX",var))
						myconfig->use_jeux = atoi(val);
				}
			}
		}
	}
	fclose(myFile);

	/** Verification de la configuration des parametre obligatoire **/

	/* Verif Pseudo */
	if(!myconfig->botnick)
	{
		put_log("Erreur Botnick abs , fonction load_config");
		return 0;
	}

	/* Verif  Realname du Bot */
	if(!myconfig->real)
	{
		put_log("Erreur real abs , fonction load_config");
		return 0;
	}

	/* Verif  Ip du server ou son domaine */
	if(!myconfig->server)
	{
		put_log("Erreur server abs , fonction load_config");
		return 0;
	}

	/* Verif  Port de connexion au server */
	if(myconfig->port == 0)
	{
		put_log("Erreur port = 0 , fonction load_config");
		return 0;
	}

	/* Verif  Channel de service */
	if(!myconfig->service)
	{
		put_log("Erreur service abs , fonction load_config");
		return 0;
	}

	/* Verif  Pass de connexion Link */
	if(!myconfig->serverpass)
	{
		put_log("Erreur serverpass abs , fonction load_config");
		return 0;
	}

	/* Verif  Link */
	if(!myconfig->host)
	{
		put_log("Erreur host abs , fonction load_config");
		return 0;
	}

	/*  Verif Complement d'host */
	if(!myconfig->hostc)
	{
		put_log("Erreur hostc abs , fonction load_config");
		return 0;
	}

	/* Verif  Flags du bots */
	if(!myconfig->flags)
	{
		put_log("Erreur flags abs , fonction load_config");
		return 0;
	}
	return 1;
}

void rehash()
{
	int result = 0;

	/** Liberation **/
	if(myconfig->botnick) FREE(myconfig->botnick);
	if(myconfig->real) FREE(myconfig->real);
	if(myconfig->server) FREE(myconfig->server);
	if(myconfig->service) FREE(myconfig->service);
	if(myconfig->serverpass) FREE(myconfig->serverpass);
	if(myconfig->host) FREE(myconfig->host);
	if(myconfig->hostc) FREE(myconfig->hostc);
	if(myconfig->flags) FREE(myconfig->flags);
	FREE(myconfig);

	/** rechargement du fichier de configuration **/
	result = load_config("bot.conf");
	if(result == 0)
	{
		put_log("Erreur de configuration , fonction rehash");
		exit(1);
	}

	/** liberation et quit des bots plus desiré **/
	if(!myconfig->use_nickserv) unload_nickserv();
	if(!myconfig->use_operserv) unload_operserv();	
	if(!myconfig->use_protect) unload_protectserv();
	if(!myconfig->use_radio) unload_radio();
	if(!myconfig->use_antispam) unload_spam();
	if(!myconfig->use_coleen) unload_coleen();
	if(!myconfig->use_global) unload_global();
	if(!myconfig->use_masstoolz) unload_masstoolz();
	if(!myconfig->use_antiproxy) unload_proxy();
	if(!myconfig->use_jeux) unload_jeux();

	if(myconfig->use_nickserv) init_nickserv();
	if(myconfig->use_operserv) init_operserv();	
	if(myconfig->use_protect) init_protectserv();
	if(myconfig->use_radio) init_radio();
	if(myconfig->use_antispam) init_spam();
	if(myconfig->use_coleen) init_coleen();
	if(myconfig->use_global) init_global();
	if(myconfig->use_masstoolz) init_masstoolz();
	if(myconfig->use_antiproxy) init_proxy();
	if(myconfig->use_jeux) init_jeux();
}

char *time_fr(long t)
{
	struct tm *pdh; time_t intps;
	char buffer[100];
	static char *jour[]={"Dim","Lun","Mar","Mer","Jeu","Ven","Sam"};
	static char *mois[]={"Janvier","Fevrier","Mars","Avril","Mai ","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};
	intps=t;
	pdh = localtime(&intps);
	sprintf(buffer,"%s %d %s %d a %02d:%02d:%02d",jour[pdh->tm_wday],pdh->tm_mday,mois[pdh->tm_mon],1900+pdh->tm_year,pdh->tm_hour,pdh->tm_min,pdh->tm_sec);
	return strdup(buffer);
}

char *heure_fr(long t)
{
	struct tm *pdh; time_t intps;
	char buffer[50];
	intps=t;
	pdh = localtime(&intps);
	sprintf(buffer,"%02d:%02d:%02d",pdh->tm_hour,pdh->tm_min,pdh->tm_sec);
	return strdup(buffer);
}

unsigned my_rand(unsigned N)
{
#ifndef WIN32
	struct timeval tv_1;
	gettimeofday(&tv_1, NULL);
	srand(tv_1.tv_usec);
	return rand()%N;
#else
	LARGE_INTEGER i;
	QueryPerformanceCounter(&i);
	srand((unsigned int)i.QuadPart);
	return rand()%N;
#endif
}

int	match(char *ma, char *na)
{
	int	wild = 0, q = 0;
	char *m = (char *)ma;
	char *n = (char *)na;
	char *mask = (char *)ma;
	
	if (!m || !n)
		return 0;

	while (1)
	{
		if (!*m)
		{
			if (!*n)
				return 1;

			for (m--; (*m == '?') && (m>mask); m--);

			if ((*m == '*') && (m>mask) && (m[-1]!='\\'))
				return 1;

			if (wild) 
			{
				m = (char *)ma;
				n = (char *)++na;
			}
			else
				return 0;
		}
		else
		{
			if (!*n)
			{
				while(*m == '*')
					m++;

				return 0;
		    }
		}
		if (*m == '*')
		{
			while (*m == '*')
				m++;
			wild = 1;
			ma = (char *)m;
			na = (char *)n;
		}
		
		if ((*m == '\\') && ((m[1] == '*') || (m[1] == '?')))
		{
			m++;
			q = 1;
		}
		else
			q = 0;

		if ((tolower(*m) != tolower(*n)) && ((*m != '?') || q))
		{
			if (wild)
			{
				m = (char *)ma;
				n = (char *)++na;
			}
			else
				return 0;
		}
		else
		{
			if (*m)
					m++;
			if (*n)
					n++;
		}
	}
	return 1;
}






