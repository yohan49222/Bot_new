#include "main.h"

extern Config *myconfig;

/**
	***************************
	** Gestions des channels **
	***************************
**/

Channel *Allchan = NULL;

Channel *new_channel(char *name,long datetopic,char *topicAuteur,char *topic)
{
	Channel *channel;

	if(!name || !*name)
		return NULL;

	channel = get_channel(name);
	if(channel)
		return channel;

	channel = (Channel*)malloc(sizeof(Channel));
	if(!channel)
		return NULL;


	STRDUP(channel->chanName,name);
	channel->usercourant = NULL;
	channel->bancourant = NULL;
	channel->Mode = 0;

	if(match("#!*!",name))
		channel->is_Off = 1;
	else
		channel->is_Off = 0;

	if(datetopic)
		channel->chanTopic_Date = datetopic;
	else
		channel->chanTopic_Date = time(NULL);



	if(topicAuteur)
	{
		STRDUP(channel->chanTopic_Auteur,topicAuteur)
	}
	else
	{
		STRDUP(channel->chanTopic_Auteur, "?") ;
	}

	if(topic)
	{
		STRDUP(channel->chanTopic,topic)
	}
	else
	{
		STRDUP(channel->chanTopic,"?") ;
	}

	channel->precedent = NULL;
	channel->suivant = Allchan;
	if (Allchan)
    		Allchan->precedent = channel;
	Allchan = channel;
	return Allchan;

}

int del_channel(char *name)
{
	Channel *channel = Allchan;
	while (channel)
	{
		if(strcasecmp(channel->chanName,name) == 0)
		{
			clear_ban(channel);
			clear_uliste(channel);

			if(channel->suivant)
				channel->suivant->precedent = channel->precedent;

			if(channel->precedent)
				channel->precedent->suivant = channel->suivant;

			if(channel == Allchan)
				Allchan = channel->suivant;

			FREE(channel);

			return 1;
		}
		channel = channel->suivant;
	}
	return 0;
}

int clear_channel(char *motif)
{
	Channel *channel;
	while (Allchan)
	{
		clear_ban(Allchan);
		clear_uliste(Allchan);
		
		channel = Allchan;
		Allchan = Allchan->suivant;
		FREE(channel);
		channel = NULL;
	}
	Allchan = NULL;
	return 1;
}

long Channel_t()
{
	int count = 0;

	Channel *u;
	u = Allchan;
	while (u)
	{
		count++;
		u = u->suivant;
	}
	return sizeof(Channel) * (count+1);
}

/*
	recherche le channel par son nom
*/
Channel *get_channel(char *name)
{
	Channel *channel = Allchan;
	while(channel)
	{
		if(strcasecmp(channel->chanName,name) == 0)
			return channel;

		channel = channel->suivant;
	}
	return NULL;
}

int set_topic(char *name,char *topic,char *auteur,long date)
{
	Channel *channel = get_channel(name);
	if(!channel)
		return 0;

	/* changement du topic */
	if(topic)
	{
		FREE(channel->chanTopic);
		STRDUP(channel->chanTopic,topic);
	}
	/* changement d'auteur */
	if(auteur)
	{
		FREE(channel->chanTopic_Auteur);
		STRDUP(channel->chanTopic_Auteur,auteur);
	}
	/* changement de date */
	if(date)
		channel->chanTopic_Date = date; 

	return 1;
}

int is_onchan(Channel *chan , User *use)
{
	UserList *Utmp = chan->usercourant;
	while(Utmp)
	{
		if(Utmp->use == use)
			return 1;

		Utmp = Utmp->suivant;
	}
	return 0;
}

char *chanList(User *use)
{
	Channel *channel = Allchan;
	char txt[MAXLEN];
	int i = 0;
	while(channel)
	{
		if(is_onchan(channel ,use))
		{
			if(!i)
			{
				sprintf(txt,"%s",channel->chanName);
			}
			else
			{
				sprintf(txt,"%s - %s", txt,channel->chanName);
			}
			i++;
		}

		channel = channel->suivant;
	}
	return strdup(txt);
}

int user_join(char *name,User *use)
{
	Channel *channel;
	UserList *Utmp;
	UserList *UserListSuivant;

	channel = get_channel(name);
	if(!channel)
		goto NEWCHAN;


	Utmp = channel->usercourant;
	while(Utmp)
	{
		if(Utmp->use == use)
			return 0;

		Utmp = Utmp->suivant;
	}


	UserListSuivant = (UserList*)malloc(sizeof(UserList));
	if(!UserListSuivant)
		return 0;

	UserListSuivant->modeUser = 0;

	UserListSuivant->use = use;
	UserListSuivant->precedent = NULL;
	UserListSuivant->suivant = channel->usercourant;
	if(channel->usercourant)
    		channel->usercourant->precedent = UserListSuivant;
	channel->usercourant = UserListSuivant;
			
	return 1;

NEWCHAN:
	new_channel(name,0,NULL,NULL);
	user_join(name,use);
	return 0;
}

UserList *user_part(char *name,User *use)
{
	UserList *Utmp;
	Channel *channel = get_channel(name);
	if(!channel)
		return NULL;

	Utmp = channel->usercourant;
	while(Utmp)
	{
		if(strcasecmp(Utmp->use->nick,use->nick) == 0)
		{
			if(Utmp->suivant)
				Utmp->suivant->precedent = Utmp->precedent;

			if(Utmp->precedent)
				Utmp->precedent->suivant = Utmp->suivant;

			if(Utmp == channel->usercourant)
				channel->usercourant = Utmp->suivant;

;
					
			FREE(Utmp);

			if(!channel->usercourant)
			{
				del_channel(channel->chanName);
				return NULL;
			}

			return channel->usercourant;

		}
		Utmp = Utmp->suivant;
	}
	return channel->usercourant;
}

int user_part_allchan(User *use,char *mess)
{
	Channel *channel;
	UserList *Utmp;

retour:

	channel = Allchan;
	while(channel)
	{
		Utmp = channel->usercourant;
		while(Utmp)
		{
			if(!strcasecmp(Utmp->use->nick,use->nick))
			{
				if(Utmp->suivant)
					Utmp->suivant->precedent = Utmp->precedent;

				if(Utmp->precedent)
					Utmp->precedent->suivant = Utmp->suivant;

				if(Utmp == channel->usercourant)
					channel->usercourant = Utmp->suivant;

				
				FREE(Utmp);

				if(!channel->usercourant)
					del_channel(channel->chanName);

				goto retour;
			}
			Utmp = Utmp->suivant;
		}
		channel = channel->suivant;
	}
	return 1;
}

void clear_uliste(Channel *channel)
{
	UserList *use;
	while (channel->usercourant)
	{
		use = channel->usercourant;
		channel->usercourant = channel->usercourant->suivant;
		FREE(use);
		use = NULL;
	}
	channel->usercourant = NULL;
	return;
}

void set_Mode_Status(Channel *channel , char *nick, char mode , int on_off)
{
	UserList *tmp = channel->usercourant;
	while(tmp)
	{
		if(!strcmp(tmp->use->nick,nick))
		{

			if(on_off)
			{
				switch(mode)
				{
					case 'a':
						tmp->modeUser |= S_MODE_a;
						break;
					case 'o':
						tmp->modeUser |= S_MODE_o;
						break;
					case 'h':
						tmp->modeUser |= S_MODE_h;
						break;
					case 'v':
						tmp->modeUser |= S_MODE_v;
						break;
					case 'q':
						tmp->modeUser |= S_MODE_q;
						break;
				}
			}
			else
			{
				switch(mode)
				{
					case 'a':
						tmp->modeUser &= (0xFFFFFFFF ^ S_MODE_a);
						break;
					case 'o':
						tmp->modeUser &= (0xFFFFFFFF ^ S_MODE_o);
						break;
					case 'h':
						tmp->modeUser &= (0xFFFFFFFF ^ S_MODE_h);
						break;
					case 'v':
						tmp->modeUser &= (0xFFFFFFFF ^ S_MODE_v);
						break;
					case 'q':
						tmp->modeUser &= (0xFFFFFFFF ^ S_MODE_q);
						break;
				}
			}
			return;
		}
		tmp = tmp->suivant;
	}
}

void set_Mode_Chan(Channel *channel , char mode , int on_off)
{
	if(on_off == 1)
	{
		switch(mode)
		{
			case 'A':channel->Mode |= C_MODE_A;break;
			case 'a':channel->Mode |= C_MODE_a;break;
			case 'b':channel->Mode |= C_MODE_b;break;
			case 'c':channel->Mode |= C_MODE_c;break;
			case 'C':channel->Mode |= C_MODE_C;break;
			case 'e':channel->Mode |= C_MODE_e;break;
			case 'f':channel->Mode |= C_MODE_f;break;
			case 'G':channel->Mode |= C_MODE_G;break;
			case 'i':channel->Mode |= C_MODE_i;break;
			case 'K':channel->Mode |= C_MODE_K;break;
			case 'k':channel->Mode |= C_MODE_k;break;
			case 'L':channel->Mode |= C_MODE_L;break;
			case 'l':channel->Mode |= C_MODE_l;break;
			case 'M':channel->Mode |= C_MODE_M;break;
			case 'm':channel->Mode |= C_MODE_m;break;
			case 'n':channel->Mode |= C_MODE_n;break;
			case 'N':channel->Mode |= C_MODE_N;break;
			case 'O':channel->Mode |= C_MODE_O;break;
			case 'p':channel->Mode |= C_MODE_p;break;
			case 'Q':channel->Mode |= C_MODE_Q;break;
			case 'r':channel->Mode |= C_MODE_r;break;
			case 'R':channel->Mode |= C_MODE_R;break;
			case 'S':channel->Mode |= C_MODE_S;break;
			case 's':channel->Mode |= C_MODE_s;break;
			case 'T':channel->Mode |= C_MODE_T;break;
			case 't':channel->Mode |= C_MODE_t;break;
			case 'u':channel->Mode |= C_MODE_u;break;
			case 'V':channel->Mode |= C_MODE_V;break;
			case 'z':channel->Mode |= C_MODE_z;break;
		}
	}
	else
	{
		switch(mode)
		{
			case 'A':channel->Mode &= (0xFFFFFFFF ^ C_MODE_A);break;
			case 'a':channel->Mode &= (0xFFFFFFFF ^ C_MODE_a);break;
			case 'b':channel->Mode &= (0xFFFFFFFF ^ C_MODE_b);break;
			case 'c':channel->Mode &= (0xFFFFFFFF ^ C_MODE_c);break;
			case 'C':channel->Mode &= (0xFFFFFFFF ^ C_MODE_C);break;
			case 'e':channel->Mode &= (0xFFFFFFFF ^ C_MODE_e);break;
			case 'f':channel->Mode &= (0xFFFFFFFF ^ C_MODE_f);break;
			case 'G':channel->Mode &= (0xFFFFFFFF ^ C_MODE_G);break;
			case 'i':channel->Mode &= (0xFFFFFFFF ^ C_MODE_i);break;
			case 'K':channel->Mode &= (0xFFFFFFFF ^ C_MODE_K);break;
			case 'k':channel->Mode &= (0xFFFFFFFF ^ C_MODE_k);break;
			case 'L':channel->Mode &= (0xFFFFFFFF ^ C_MODE_L);break;
			case 'l':channel->Mode &= (0xFFFFFFFF ^ C_MODE_l);break;
			case 'M':channel->Mode &= (0xFFFFFFFF ^ C_MODE_M);break;
			case 'm':channel->Mode &= (0xFFFFFFFF ^ C_MODE_m);break;
			case 'n':channel->Mode &= (0xFFFFFFFF ^ C_MODE_n);break;
			case 'N':channel->Mode &= (0xFFFFFFFF ^ C_MODE_N);break;
			case 'O':channel->Mode &= (0xFFFFFFFF ^ C_MODE_O);break;
			case 'p':channel->Mode &= (0xFFFFFFFF ^ C_MODE_p);break;
			case 'Q':channel->Mode &= (0xFFFFFFFF ^ C_MODE_Q);break;
			case 'r':channel->Mode &= (0xFFFFFFFF ^ C_MODE_r);break;
			case 'R':channel->Mode &= (0xFFFFFFFF ^ C_MODE_R);break;
			case 'S':channel->Mode &= (0xFFFFFFFF ^ C_MODE_S);break;
			case 's':channel->Mode &= (0xFFFFFFFF ^ C_MODE_s);break;
			case 'T':channel->Mode &= (0xFFFFFFFF ^ C_MODE_T);break;
			case 't':channel->Mode &= (0xFFFFFFFF ^ C_MODE_t);break;
			case 'u':channel->Mode &= (0xFFFFFFFF ^ C_MODE_u);break;
			case 'V':channel->Mode &= (0xFFFFFFFF ^ C_MODE_V);break;
			case 'z':channel->Mode &= (0xFFFFFFFF ^ C_MODE_z);break;
		}
	}
}

char *list_Mode_Chan(Channel *channel)
{
	int x = 0;
	char *mode = (char *)calloc(MAXLEN,1);

	if(channel->Mode & C_MODE_a) mode[x++] = 'a';
	if(channel->Mode & C_MODE_b) mode[x++] = 'b';
	if(channel->Mode & C_MODE_c) mode[x++] = 'c';
	if(channel->Mode & C_MODE_e) mode[x++] = 'e';
	if(channel->Mode & C_MODE_f) mode[x++] = 'f';
	if(channel->Mode & C_MODE_i) mode[x++] = 'i';
	if(channel->Mode & C_MODE_k) mode[x++] = 'k';
	if(channel->Mode & C_MODE_L) mode[x++] = 'L';
	if(channel->Mode & C_MODE_l) mode[x++] = 'l';
	if(channel->Mode & C_MODE_m) mode[x++] = 'm';
	if(channel->Mode & C_MODE_n) mode[x++] = 'n';
	if(channel->Mode & C_MODE_r) mode[x++] = 'r';
	if(channel->Mode & C_MODE_s) mode[x++] = 's';
	if(channel->Mode & C_MODE_t) mode[x++] = 't';
	if(channel->Mode & C_MODE_u) mode[x++] = 'u';
	if(channel->Mode & C_MODE_z) mode[x++] = 'z';
	if(channel->Mode & C_MODE_A) mode[x++] = 'A';
	if(channel->Mode & C_MODE_C) mode[x++] = 'C';
	if(channel->Mode & C_MODE_G) mode[x++] = 'G';
	if(channel->Mode & C_MODE_K) mode[x++] = 'K';
	if(channel->Mode & C_MODE_M) mode[x++] = 'M';
	if(channel->Mode & C_MODE_N) mode[x++] = 'N';
	if(channel->Mode & C_MODE_O) mode[x++] = 'O';
	if(channel->Mode & C_MODE_p) mode[x++] = 'p';
	if(channel->Mode & C_MODE_Q) mode[x++] = 'Q';
	if(channel->Mode & C_MODE_R) mode[x++] = 'R';
	if(channel->Mode & C_MODE_S) mode[x++] = 'S';
	if(channel->Mode & C_MODE_T) mode[x++] = 'T';
	if(channel->Mode & C_MODE_V) mode[x++] = 'V';
	mode[x] = '\0';
	return mode;
}

void new_ban(Channel *channel,char *mask,long time_t)
{
	BanList *ban;

	if(!*mask)
		return;

	ban = (BanList*)malloc(sizeof(BanList));
	if(!ban)
		return;
	STRDUP(ban->mask,mask);
	ban->timestamp = time_t;
	ban->precedent = NULL;
	ban->suivant = channel->bancourant;

	if (channel->bancourant)
    	channel->bancourant->precedent = ban;
	channel->bancourant = ban;

	return;
}

void del_ban(Channel *channel,char *mask,long time_t)
{
	BanList *ban;
	ban = channel->bancourant;
	while(ban)
	{
		if(strcasecmp(ban->mask,mask) == 0)
		{
			if(ban->suivant)
				ban->suivant->precedent = ban->precedent;

			if(ban->precedent)
				ban->precedent->suivant = ban->suivant;

			if(ban == channel->bancourant)
				channel->bancourant = ban->suivant;

			FREE(ban->mask);
			FREE(ban);

			return;

		}
		ban = ban->suivant;
	}
	return;
}

void clear_ban(Channel *channel)
{
	BanList *ban;
	while (channel->bancourant)
	{
		ban = channel->bancourant;
		channel->bancourant = channel->bancourant->suivant;

		FREE(ban->mask);
		FREE(ban);
		ban = NULL;
	}
	channel->bancourant = NULL;
	return;
}


