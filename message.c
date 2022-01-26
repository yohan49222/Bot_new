
#include "main.h"

void traitement( char *src )
{

	int i = 0;
	message_irc *message = (message_irc*)malloc(sizeof(message_irc));
	if(!message)
	{
		put_log("Allocation impossible");
		return;
	}
	prep_message(src,message);

	executeRaw_Gestion(message);
	executeRaw_Protect(message);
	executeRaw_Bot(message);
	
	while(message->RAW[i])
	{
		FREE(message->RAW[i]);
		i++;
	}
	i = 0;
	while(message->ARG[i])
	{
		FREE(message->ARG[i]);
		i++;
	}
	if(message->message)
	{
		FREE(message->message);
	}
	FREE(message);
}
/**
void prep_message( char *src , message_irc *message)
{

	char *ptr;
	int i = 0;
	int posRaw = 0;
	int posArg = 0;
	char c;
	int n_raw = 100;

	message->RAW = (char**)malloc(sizeof(message->RAW));
	if(!message->RAW)
	{
		//print_debug(2,"erreur malloc RAW");
		return;
	}


	message->ARG = (char**)malloc(sizeof(message->ARG));
	if(!message->ARG)
	{
		//print_debug(2,"erreur malloc ARG\n");
		return;
	}
	message->ARG[0] = NULL;
	strcpy(message->message,"NULL");
	ptr = strtok(src, " ");
	while(ptr != NULL)
	{
		if (i < n_raw)
		{
			if(strspn(ptr,":") == 1)
			{
				c = *ptr++;
				if(i == 0)
				{
					message->RAW = (char**)realloc(message->RAW, ( sizeof(message->RAW) * (posRaw+1)) + 1 );
					if(!message->RAW)
					{
						//print_debug(2,"erreur realloc RAW");
						return;
					}
					message->RAW[posRaw++] = ptr;
				}
				else
				{
					if(strlen(ptr) > 0)
					{
						
						message->ARG = (char**)realloc(message->ARG, ( sizeof(message->ARG) * (posArg+1)) + 1 );
						if(!message->ARG)
						{
							//print_debug(2,"erreur realloc ARG");
							return;
						}
						message->ARG[posArg] = ptr;
						retirecouleur(message->ARG[posArg],message->ARG[posArg]);
						if(strlen(message->ARG[posArg]) > 0)
							posArg++;

						
						strncpy(message->message,ptr,sizeof(message->message) - 1);
					}
					i = 100;
				}
			}
			else
			{
				message->RAW = (char**)realloc(message->RAW, ( sizeof(message->RAW) * (posRaw+1)) + 1 );
				if(!message->RAW)
				{
					//print_debug(2,"erreur realloc RAW");
					return;
				}
				message->RAW[posRaw++] = ptr;
			}
		}
		else
		{
			message->ARG = (char**)realloc(message->ARG, ( sizeof(message->ARG) * (posArg+1)) + 1 );
			if(!message->ARG)
			{
				//print_debug(2,"erreur realloc ARG");
				return;
			}
			message->ARG[posArg] = ptr;
			retirecouleur(message->ARG[posArg],message->ARG[posArg]);
			if(strlen(message->ARG[posArg]) > 0)
				posArg++;

			if((strlen(message->message) + strlen(ptr) +1) <= sizeof(message->message))
				sprintf(message->message,"%s %s",message->message,ptr);
		}
		ptr = strtok(NULL," ");
		if(ptr)
			i++;
	}
	message->RAW[posRaw] = NULL;
	message->ARG[posArg] = NULL;
}
**/

void prep_message( char *src , message_irc *message)
{

	char *ptr;
	int i = 0;
	int posRaw = 0;
	int posArg = 0;

	char *raw = NULL;
	char *mess = NULL;

	message->RAW = (char**)malloc(sizeof(message->RAW));
	message->ARG = (char**)malloc(sizeof(message->ARG));
	message->RAW[0] = NULL;
	message->ARG[0] = NULL;
	message->n_raw = 0;
	message->n_arg = 0;

	if(src[0] == ':')
	{
		while(src[i] != 0)
		{
			src[i] = src[i+1];
			i++;
		}
		src[i] = 0;
	}

	/** recup le raw jusqu'au : **/
	ptr = strtok(src, ":\n");
	if(ptr != NULL)
	{
		STRDUP(raw,ptr);
	}

	ptr = strtok(NULL, "\n");
	if(ptr != NULL)
	{
		STRDUP(mess,ptr);
		STRDUP(message->message,ptr);
	}
	else
	{
		mess = NULL;
		message->message = NULL;
	}
	
	ptr = strtok(raw, " ");
	while(ptr != NULL)
	{
		message->RAW = (char**)realloc(message->RAW,(sizeof(message->RAW)*(posRaw+1))+1);
		//STRDUP(message->RAW[posRaw],ptr);
		message->RAW[posRaw] = strdup(ptr);
		posRaw++;
		message->RAW[posRaw] = NULL;
		ptr = strtok(NULL, " ");
	}
	FREE(raw);

	if(mess)
	{
		i = 0;
		if(mess[i] == ' ')
		{
			do
			{
				while(mess[i] != 0)
				{
					mess[i] = mess[i+1];
					i++;
				}
				mess[i] = 0;
				i = 0;
			}while(mess[i] == ' ');
		}
		ptr = strtok(mess, " ");
		while(ptr != NULL)
		{
			message->ARG = (char**)realloc(message->ARG,(sizeof(message->ARG)*(posArg+1))+1);
			message->ARG[posArg] = strdup(ptr);
			retirecouleur(message->ARG[posArg],message->ARG[posArg]);
			if(strlen(message->ARG[posArg]))
			{
				posArg++;
				message->ARG[posArg] = NULL;
			}
			else
			{
				FREE(message->ARG[posArg]);
				message->ARG[posArg] = NULL;
			}
			ptr = strtok(NULL, " ");
		}
		FREE(mess);
	}
	message->n_raw = posRaw;
	message->n_arg = posArg;
}

void retirecouleur(char *src,char *retour)
{
	char
		c,
		preced = '\0';

	int
		clapet = 0,
		virgule = 0;

	while( ( c = *src++) )
	{
		switch(c)
		{
			/*
				passe les caracteres soulign�et gars
			*/
			case '\001':
			case '\002':
			case '\004':
				break;

			/*
				caractere \003 , on ouvre le clapet top , mise a zero du repere dixaine
			*/
			case '\003':
				virgule = 0;
				clapet = 1;
				preced = '\0';
				break;

			case ',':
				/*
					si le clapet est ouvert (1)
					on incremente virgule et on test si defois on aurait ca " \0031,1,mot "
					si on n'a deux virugule , on ferme le clapet
				*/
				if(clapet == 1)
				{
					virgule++;
					if(virgule == 2)
					{
						clapet = virgule = 0;
						*retour++ = c;
					}
					preced = '\0';
					break;
				}
				else
				{
					*retour++ = c;
				}
				preced = '\0';
				break;



			case '0':case '1':case '2':case '3':case '4':
			case '5':case '6':case '7':case '8':case '9':
				/*
					pour les numeriques , on va tester si le clapet est ouvert
				*/
				if (clapet == 1)
				{
					switch(preced)
					{
						case '1':
							if ( ( c == '6') || ( c == '7') || ( c == '8') || ( c == '9') )
							{
								*retour++ = c;
								clapet = 0;
							}
							break;

						case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
							/*
								on verifie que c ne soit pas 6,7,8,9 , limite de couleur a 15
							*/
							*retour++ = c;
							clapet = 0;
							break;
					}

				}
				else
				{
					*retour++ = c;
				}
				preced = c;
				break;

			/*
				pour tous les autre caracteres , on ferme le clapet et on les ajoutes a "retour"
			*/
			default:
				clapet = 0;
				*retour++ = c;
				preced = '\0';
				break;
		}
	}
	/*
		ajout du fin de chaine a "retour"
	*/
	*retour++ = '\0';
}


